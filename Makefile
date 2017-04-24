CC=g++
DEPS = Net.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Perceptron: Net.o proj4Main.o
	g++ -o $@ $^

clean:
	rm *.o Perceptron
