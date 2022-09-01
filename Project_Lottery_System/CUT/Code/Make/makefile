OBJS = main.o
O = -lpthread
HEAD = functions.h 
CL = *.o
G = gcc
T = test

test: $(OBJS)  
	$(G) -o test $(OBJS) $(O)

main.o: main.c  
	$(G) -c  main.c $(O)

clean:
	rm $(CL)
	rm $(T)
