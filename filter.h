#ifndef FILTER_H
#define	FILTER_H

#define INNER 0
#define OUTER 1

typedef struct Filter Filter ;

struct Filter{
    int ** array ;
    int sum ;
    int s;
};

int init_filter(Filter * filter);               //init the struct
int create_s_filter(Filter * filter,int s);     //create and init the array( size = (s +2)*(s+2) )
int value_filter(Filter * filter);              //values to filter via scanf
int normalize_filter(Filter * filter);          //just normalize the filter
int print_filter(Filter * filter); 
int free_filter(Filter * filter);

/*FILTERISE*/
int filterise(Filter * filter,int inner_i,int inner_j,unsigned char * image_in ,unsigned char * image_out,const int option);

#endif	/* FILTER_H */

