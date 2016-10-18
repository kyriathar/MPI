#include <mpi.h>

#include "send_receive.h"
#include "neighbors.h"


void i_send_all(unsigned char * local_array,int inner_i,int inner_j,MPI_Datatype row,MPI_Datatype column,int * Neighbors,MPI_Comm new_comm,MPI_Request * send)
{
    //COLUMNS
    MPI_Isend(&(local_array[inner_j+3]),1,column, Neighbors[WEST], 123, new_comm,&(send[0]));   //NA ALLAKSOUME inner_i me inner_j
    MPI_Isend(&(local_array[2*inner_j+2]),1,column, Neighbors[EAST], 123, new_comm,&(send[1]));
    //ROWS
    MPI_Isend(&(local_array[inner_j+3]),1,row, Neighbors[NORTH], 123, new_comm,&(send[2]));
    MPI_Isend(&(local_array[(inner_i)*(inner_j+2)+1]),1,row, Neighbors[SOUTH], 123, new_comm,&(send[3]));
    //CORNER
    MPI_Isend(&(local_array[inner_j+3]),1,MPI_UNSIGNED_CHAR, Neighbors[NORTH_WEST], 123, new_comm,&(send[4]));
    MPI_Isend(&(local_array[2*inner_j+2]),1,MPI_UNSIGNED_CHAR, Neighbors[NORTH_EAST], 123, new_comm,&(send[5]));
    MPI_Isend(&(local_array[(inner_i)*(inner_j+2)+1]),1,MPI_UNSIGNED_CHAR, Neighbors[SOUTH_WEST], 123, new_comm,&(send[6]));
    MPI_Isend(&(local_array[(inner_i)*(inner_j+2)+inner_j]),1,MPI_UNSIGNED_CHAR, Neighbors[SOUTH_EAST], 123, new_comm,&(send[7]));
}

void i_receive_all(unsigned char * local_array,int inner_i,int inner_j,MPI_Datatype row,MPI_Datatype column,int * Neighbors,MPI_Comm new_comm,MPI_Request * receive)
{
    //COLUMNS
    MPI_Irecv(&(local_array[2*inner_j+3]),1,column, Neighbors[WEST], 123, new_comm,&(receive[0]));
    MPI_Irecv(&(local_array[inner_j+2]),1,column, Neighbors[EAST], 123, new_comm,&(receive[1]));
    //ROWS
    MPI_Irecv(&(local_array[(inner_i+1)*(inner_j+2)+1]),1,row, Neighbors[NORTH], 123, new_comm,&(receive[2]));
    MPI_Irecv(&(local_array[1]),1,row, Neighbors[SOUTH], 123, new_comm,&(receive[3]));
    //CORNER
    MPI_Irecv(&(local_array[(inner_i+1)*(inner_j+2)+1+inner_j]),1,MPI_UNSIGNED_CHAR, Neighbors[NORTH_WEST], 123, new_comm,&(receive[4]));
    MPI_Irecv(&(local_array[(inner_i+1)*(inner_j+2)]),1,MPI_UNSIGNED_CHAR, Neighbors[NORTH_EAST], 123, new_comm,&(receive[5]));
    MPI_Irecv(&(local_array[inner_j+1]),1,MPI_UNSIGNED_CHAR, Neighbors[SOUTH_WEST], 123, new_comm,&(receive[6]));
    MPI_Irecv(&(local_array[0]),1,MPI_UNSIGNED_CHAR, Neighbors[SOUTH_EAST], 123, new_comm,&(receive[7]));
}


void wait_send(MPI_Request * send)
{
    MPI_Waitall(8,send,MPI_STATUSES_IGNORE);
}
void wait_receive(MPI_Request * receive)
{
    MPI_Waitall(8,receive,MPI_STATUSES_IGNORE);
}