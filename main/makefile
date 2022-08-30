all: prog

CC = g++

main.o: main.cpp
	$(CC) -c main.cpp
queue.o: queue.cpp
	$(CC) -c queue.cpp
priority_queue_min.o: priority_queue_min.cpp
	$(CC) -c priority_queue_min.cpp
prog: main.o queue.o priority_queue_min.o
	$(CC) main.o queue.o priority_queue_min.o -o prog
clean:
	rm *.o prog
