CC = mpicc 
OBJS = filter.o grid.o main.o my_functions.o neighbors.o read_write.o reduce.o send_receive.o
CFLAGS = -c 
LFLAGS = -o 


all : $(OBJS)
		$(CC) $(OBJS) $(LFLAGS) mpi -lm

filter.o : filter.c
			$(CC) $(CFLAGS) filter.c 

grid.o : grid.c
			$(CC) $(CFLAGS) grid.c

main.o : main.c
			$(CC) $(CFLAGS) main.c

my_functions.o : my_functions.c
					$(CC) $(CFLAGS) my_functions.c

neighbors.o : neighbors.c
					$(CC) $(CFLAGS) neighbors.c

read_write.o : read_write.c
					$(CC) $(CFLAGS) read_write.c

reduce.o : reduce.c
			$(CC) $(CFLAGS) reduce.c

send_receive.o : send_receive.c
					$(CC) $(CFLAGS) send_receive.c


clean :
		rm -rf *.o mpi ../Photo/out.raw
