#include <stdio.h>
#include <stdlib.h>

#include "my_functions.h"

void * my_malloc(size_t size)
{
    void * ptr ;
    
    ptr = NULL ;
    ptr = malloc(size);
    
    if(ptr == NULL)
    {
        perror("my_malloc");
        exit(1);
    }
    return ptr ;
}
