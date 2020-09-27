CC=g++
CFLAGS=-std=c++11 -I.

DEPS = braceExpand.h
OBJ =  braceExpand.o


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: brace.out test.out
	
brace.out: brace.m.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test.out: braceExpand.t.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run runtest

clean:
	rm -f *.o *.out

run:
	./brace.out

runtest:
	./test.out