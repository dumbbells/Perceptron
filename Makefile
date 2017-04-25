OBJS = Net.o Proj5Main.o
CC = g++
FLAGS = -Wall -g

Perceptron: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o Perceptron

%.o : %.cpp
	$(CC) -c $< -o $@

Net.o: Net.cpp Net.h
	$(CC) -c Net.cpp

Proj4Main.o: Proj5Main.cpp Net.h
	$(CC) -c Proj4Main.cpp

clean:
	rm *.o Perceptron
