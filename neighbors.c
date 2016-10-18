#include <mpi.h>
#include <stdio.h>

#include "neighbors.h"

extern int coord[2];

int find_my_neighbor(int rank,position_t position ,int grid_dimensions,int * dims,MPI_Comm comm,int * neighbor_rank)
{
    int returnValue =101;
    
    int temp[2];
    MPI_Cart_coords(comm, rank,grid_dimensions, temp);
    
    coord[0]=temp[0];
    coord[1]=temp[1];
    
    switch(position)
    {
        case NORTH      :   //printf("NORTH\n");
                            if( temp[0]-1 <0 )
                                temp[0] = dims[0] -1 ;
                            else
                                temp[0]--;
                            break;
                                
        case NORTH_EAST :   //printf("NORTH_EAST\n");
                            if( temp[0]-1 <0 )
                                temp[0] = dims[0] -1 ;
                            else
                                temp[0]--;
                            if( temp[1]+1 >dims[0] -1 )
                                temp[1] = 0 ;
                            else
                                temp[1]++;
                            break;
        
        case EAST       :   //printf("EAST\n");
                            if( temp[1]+1 >dims[0] -1 )
                                temp[1] = 0 ;
                            else
                                temp[1]++;
                            break;    
        
        case SOUTH_EAST :   //printf("SOUTH_EAST\n");
                            if( temp[0]+1 >dims[0] -1 )
                                temp[0] = 0 ;
                            else
                                temp[0]++;
                            if( temp[1]+1 >dims[0] -1 )
                                temp[1] = 0 ;
                            else
                                temp[1]++;
                            break;
                                
        case SOUTH      :   //printf("SOUTH\n");
                            if( temp[0]+1 >dims[0] -1 )
                                temp[0] = 0 ;
                            else
                                temp[0]++;
                            break;
                            
        case SOUTH_WEST :   //printf("SOUTH_WEST\n");
                            if( temp[0]+1 >dims[0] -1 )
                                temp[0] = 0 ;
                            else
                                temp[0]++;
                            if( temp[1]-1 <0 )
                                temp[1] = dims[0] -1 ;
                            else
                                temp[1]--;
                            break;
                
        case WEST       :   //printf("WEST\n");
                            if( temp[1]-1 <0 )
                                temp[1] = dims[0] -1 ;
                            else
                                temp[1]--;
                            break;
        
        case NORTH_WEST :   //printf("NORTH_WEST\n");
                            if( temp[0]-1 <0 )
                                temp[0] = dims[0] -1 ;
                            else
                                temp[0]--;
                            if( temp[1]-1 <0 )
                                temp[1] = dims[0] -1 ;
                            else
                                temp[1]--;
                            break;   
            
        default         :   printf("switch : Wrong position\n");
                            break;
    }
    
    MPI_Cart_rank(comm, temp, neighbor_rank);

}
