GTEST_LIB=gtest
GTEST_INCLUDE=/usr/local/include

CC=g++
CFLAGS=-c -Wall -I $(GTEST_INCLUDE)
LD_FLAGS=-L /usr/local/lib -l $(GTEST_LIB) -l pthread

EXEC=output

all: $(EXEC)

$(EXEC): main.o primes.o paramstorage.o
	$(CC) main.o primes.o paramstorage.o -o $(EXEC) $(LD_FLAGS)

clean:
	rm -rf $(EXEC) *.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

primes.o: primes.cpp
	$(CC) $(CFLAGS) primes.cpp

paramstorage.o: paramstorage.cpp
	$(CC) $(CFLAGS) paramstorage.cpp

