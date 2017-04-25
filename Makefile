OBJS = Net.o Proj4Main.o
CC = g++
FLAGS = -Wall -g

Perceptron: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o Perceptron

%.o : %.cpp
	$(CC) -c $< -o $@

Net.o: Net.cpp Net.h
	$(CC) -c Net.cpp

Proj4Main.o: Proj4Main.cpp Net.h
	$(CC) -c Proj4Main.cpp

clean:
	rm *.o Perceptron
