CC = g++
CFLAGS = -Wall
#LDFLAGS = -lm
LIBTCODFLAGS = -Iinclude -L. -ltcod -ltcodxx -Wl,-rpath=.
#OBJS = Temperature.o main.o
ALLFILES = src/*.cpp

all : $(OBJS)
	$(CC) $(ALLFILES) $(LIBTCODFLAGS) -o tuto

clean :
	\rm *.o tuto
