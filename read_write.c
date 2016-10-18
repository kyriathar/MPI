#include <mpi.h>
#include <stdio.h>

#include "read_write.h"
#include "my_functions.h"


extern int coord[2]; 

void read_all(const char * file_name,MPI_Comm new_comm,int inner_i,int inner_j, unsigned char * local_array)
{      
        MPI_File MpiFile;
	int error;
	MPI_Datatype parallel_vector ,parallel_vector_block ;
	MPI_Status status;

	error = MPI_File_open( new_comm, file_name, MPI_MODE_RDONLY, MPI_INFO_NULL, &MpiFile );
    	if (error) {
        	printf( "Can't open file waterfall_grey_1920_2520.raw\n" );fflush(stdout);
        	MPI_Abort(MPI_COMM_WORLD,-1);
    	}
	MPI_Type_vector(inner_i,inner_j,IMAGE_J,MPI_UNSIGNED_CHAR, &parallel_vector);
	MPI_Type_commit(&parallel_vector);
	error = MPI_File_set_view( MpiFile, coord[0]*inner_i*IMAGE_J+coord[1]*inner_j, MPI_UNSIGNED_CHAR, parallel_vector, "native", MPI_INFO_NULL );
	MPI_Type_vector(inner_i,inner_j,inner_j+2,MPI_UNSIGNED_CHAR, &parallel_vector_block);
	MPI_Type_commit(&parallel_vector_block);
    MPI_File_read_at_all(MpiFile,0,&local_array[inner_j+3],1,parallel_vector_block,&status);
	
	
	MPI_File_close( &MpiFile );
}

void compose_pic(const char * file_name,MPI_Comm new_comm,int inner_i,int inner_j, unsigned char * local_array)
{
	
	MPI_File MpiFile;
	int error;
	MPI_Datatype parallel_vector ,parallel_vector_block;
	MPI_Status status;
	MPI_Type_vector(inner_i,inner_j,IMAGE_J,MPI_UNSIGNED_CHAR, &parallel_vector);
	MPI_Type_commit(&parallel_vector);

	error = MPI_File_open( new_comm, file_name, MPI_MODE_RDWR|MPI_MODE_CREATE, MPI_INFO_NULL, &MpiFile );
	if (error) {
        	printf( "Can't open file out.txt\n" );fflush(stdout);
        	MPI_Abort(MPI_COMM_WORLD,-1);
    	}
        error = MPI_File_set_view( MpiFile, coord[0]*inner_i*IMAGE_J+coord[1]*inner_j, MPI_UNSIGNED_CHAR, parallel_vector, "native", MPI_INFO_NULL );
        MPI_Type_vector(inner_i,inner_j,inner_j+2,MPI_UNSIGNED_CHAR, &parallel_vector_block);
	MPI_Type_commit(&parallel_vector_block);
	MPI_File_write_at_all(MpiFile,0,&local_array[inner_j+3],1,parallel_vector_block,&status);
	MPI_File_close( &MpiFile );
}