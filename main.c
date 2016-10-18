#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#include "grid.h"
#include "filter.h"
#include "reduce.h"
#include "neighbors.h"
#include "read_write.h"
#include "my_functions.h"
#include "send_receive.h"

int  coord[2];

int main(int argc, char** argv) {

    /*VARS*/
    int i,j;
    int my_rank =0;
    int processes =0;
    int inner_i =0;
    int inner_j =0;
    int array_elements=0;
    int check_value; 
    int return_value;
    unsigned char * temp = NULL ;
    unsigned char * local_array_in = NULL ;
    unsigned char * local_array_out = NULL ;
    int grid_dimensions ,dims[2], period[2], reorder;
    MPI_Comm new_comm;
    int Neighbors[8];
    MPI_Datatype row,column;
    MPI_Request send[8],receive[8];
    Filter filter ;
    
    double time_in;
    double time_out;
    
    /*FILTER*/
    init_filter(&filter);
    create_s_filter(&filter,1);
    value_filter(&filter);
    
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&processes);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank); 
    
    
    /*LOCAL ARRAY*/
    inner_i=    IMAGE_I / sqrt(processes);
    inner_j =   IMAGE_J / sqrt(processes);
    array_elements = (inner_i+2)*(inner_j+2) ;
    local_array_in = (unsigned char *)my_malloc(array_elements*sizeof(unsigned char)); 
    memset(local_array_in,255,array_elements*sizeof(unsigned char));
    
    local_array_out = (unsigned char *)my_malloc(array_elements*sizeof(unsigned char)); 
    memset(local_array_out,0,array_elements*sizeof(unsigned char));
    
    /*GRID*/
    set_grid(&grid_dimensions,dims ,processes,period,&reorder);
    MPI_Cart_create(MPI_COMM_WORLD, grid_dimensions,dims, period, reorder, &new_comm);
    
    /*FIND NEIGHBORS AND MY COORDS*/
    for(i=0;i<8;i++)
        find_my_neighbor(my_rank,i ,2,dims,new_comm,(Neighbors+i));
    
    /*PARALLEL READ*/
    read_all("../Photo/waterfall_grey_1920_2520.raw",new_comm,inner_i,inner_j,local_array_in); 
    
    /*DATATYPES*/
    MPI_Type_contiguous( inner_j, MPI_UNSIGNED_CHAR, &row );
    MPI_Type_commit(&row);
    
    MPI_Type_vector( inner_i,1,inner_j+2,MPI_UNSIGNED_CHAR, &column);
    MPI_Type_commit(&column);
    
    time_in = MPI_Wtime();
    /*SEND RECEIVE + FILTER*/
    
    for(i=0;i<1000;i++)
    {
        i_send_all(local_array_in,inner_i,inner_j,row,column,Neighbors,new_comm,send);
        i_receive_all(local_array_in,inner_i,inner_j,row,column,Neighbors,new_comm,receive); 

        
        filterise(&filter,inner_i,inner_j,local_array_in,local_array_out,INNER);
        
        wait_receive(receive);
        
        filterise(&filter,inner_i,inner_j,local_array_in,local_array_out,OUTER);
        
        temp = local_array_in;
        local_array_in = local_array_out;
        local_array_out = temp;
        check_value=check_convergence(inner_i,inner_j,local_array_in,local_array_out);
        MPI_Allreduce( &check_value,&return_value, 1, MPI_INT, MPI_SUM, new_comm );
        if(!return_value){
            if(my_rank ==0)
                printf("Epanalipseis = %d \n",i);
            break;
        }
        
        wait_send(send);
    }
    time_out = MPI_Wtime();
    
    if(my_rank ==0)
    {
        printf("Time taken: %1.5f seconds\n", time_out-time_in);
    }
    
    /*PARALLEL WRITE*/
    
    compose_pic("../Photo/out.raw",new_comm,inner_i,inner_j,local_array_in);    
    
    
    MPI_Finalize();
    
    /*FREE FOR ALL*/
    free(local_array_in);
    free(local_array_out);
    
    return (EXIT_SUCCESS);
}