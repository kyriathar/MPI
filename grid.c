#include <math.h>
#include "grid.h"


void set_grid(int * grid_dimensions,int * dim ,int number_of_processes,int * period,int * reorder)
{
    *grid_dimensions = 2 ;               //Panta didiastatos
    dim[0]=sqrt(number_of_processes);    //Panta tetragwniko pinaka diergasiwn thewroume  
    dim[1]=sqrt(number_of_processes);    
    period[0]=1; 
    period[1]=1;
    *reorder=1;
}