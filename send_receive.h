#ifndef SEND_RECEIVE_H
#define	SEND_RECEIVE_H

void i_send_all(unsigned char * local_array,int inner_i,int inner_j,MPI_Datatype row,MPI_Datatype column,int * Neighbors,MPI_Comm new_comm,MPI_Request * send);
void i_receive_all(unsigned char * local_array,int inner_i,int inner_j,MPI_Datatype row,MPI_Datatype column,int * Neighbors,MPI_Comm new_comm,MPI_Request * receive); 

void wait_send(MPI_Request * send);
void wait_receive(MPI_Request * receive);


#endif	/* SEND_RECEIVE_H */

