#set ( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
CC = g++ -g -Wall -O3 -std=c++11
CFLAGS = -I include

all: bin/puzzle_solver_asz

bin/puzzle_solver_asz: bin/puzzle_solver_asz.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

bin/puzzle_solver_asz.o: src/puzzle_solver_asz.cc include/puzzle_solver.h include/error_code.h include/time_utility.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf bin/*.o
