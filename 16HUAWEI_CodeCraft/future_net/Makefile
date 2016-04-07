CC = g++ -g -w -std=c++11
CFLAGS = -I include

all: bin/puzzle_solver_asz

bin/puzzle_solver_asz: bin/puzzle_solver_asz.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

bin/puzzle_solver_asz.o: src/puzzle_solver_asz.cc include/*.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f bin/*.o
	rm -f bin/puzzle_solver_asz
