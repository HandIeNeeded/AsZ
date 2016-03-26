CC = g++ -g -Wall -O3 -std=c++11
CFLAGS = -I include

all: bin/puzzle_solver_asz

bin/puzzle_solver_asz: src/puzzle_solver_asz.cc
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

bin/lib_asz_common.o: include/puzzle_solver.h include/error_code.h include/time_utility.h include/data_io_helper.h include/test_data_generator include/solution_checker.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf bin/*
