
#include "reduce.h"

int check_convergence(int inner_i,int inner_j,unsigned char * image_in ,unsigned char * image_out)
{
    int x,y ;
    for(x=1;x<inner_i+1;x++)
    {
        for(y=1; y<inner_j+1 ;y++)          //y < 1920
        {
            if(image_in[x*(inner_j+2) + y] != image_out[x*(inner_j+2) + y])
                return 1 ;
        }
    }
    return 0 ;
}
