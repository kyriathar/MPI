#ifndef NEIGHBORS_H
#define	NEIGHBORS_H

typedef enum {NORTH,NORTH_EAST,EAST,SOUTH_EAST,SOUTH,SOUTH_WEST,WEST,NORTH_WEST} position_t;

int find_my_neighbor(int rank,position_t position ,int grid_dimensions,int * dims,MPI_Comm comm,int * neighbor_rank);

#endif	/* NEIGHBORS_H */

