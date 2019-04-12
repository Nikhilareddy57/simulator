CC=g++
CFLAGS=-g -Wall
RM=/bin/rm -f

all: main
functions.o:  functions.cpp
	${CC} ${CFLAGS} -c functions.cpp 
graphics.o:   graphics.cpp
	${CC} ${CFLAGS} -c graphics.cpp 
vehicle.o: vehicle.cpp
	${CC} ${CFLAGS} -c vehicle.cpp
main.o: vehicle.h functions.h  main.cpp
	${CC} ${CFLAGS} -c main.cpp -lglut -lGLU -lGL
main: main.o vehicle.o graphics.o functions.o
	${CC} ${CFLAGS} -o main main.o vehicle.o graphics.o functions.o -lglut -lGLU -lGL
clean:
	${RM} *.o main