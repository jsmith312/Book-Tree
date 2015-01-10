CC = gcc
CFLAGS = -Wall -g

# dependencies for catalog program, used in main
catalog: catalog.o  tree.o processOpts.o processFiles.o 
	$(CC) $(CFLAGS) -o catalog catalog.o  tree.o processOpts.o processFiles.o 

# dependencies for catalog.c 
catalog.o: catalog.c catalog.h 
	$(CC) $(CFLAGS) -c catalog.c

# dependencies for list.c 
list.o: tree.c catalog.h
	$(CC) $(CFLAGS) -c tree.c

# dependencies for processFiles.c 
processFiles.o: processFiles.c catalog.h
	$(CC) $(CFLAGS) -c processFiles.c

# dependencies for processOpts.c 
processOpts.o: processOpts.c catalog.h
	$(CC) $(CFLAGS) -c processOpts.c

# run clean command
clean:
	/bin/rm catalog.o processOpts.o processFiles.o tree.o  

