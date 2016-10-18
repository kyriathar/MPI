#ifndef READ_WRITE_H
#define	READ_WRITE_H

void read_all(const char * file_name,MPI_Comm new_comm,int inner_i,int inner_j, unsigned char * local_array);
void compose_pic(const char * file_name,MPI_Comm new_comm,int inner_i,int inner_j, unsigned char * local_array);

#endif	/* READ_WRITE_H */

