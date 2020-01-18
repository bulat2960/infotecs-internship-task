CC=g++
CFLAGS=-c -Wall
EXEC=output


all: $(EXEC)

$(EXEC): main.o primes.o
	 $(CC) main.o primes.o -o $(EXEC)

clean:
	rm -rf $(EXEC) *.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

primes.o: primes.cpp
	$(CC) $(CFLAGS) primes.cpp
