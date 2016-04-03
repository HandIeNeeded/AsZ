CC = gcc -g -w -lstdc++ -std=c++11
CFLAGS = -I include

all: bin/puzzle_solver_asz
	cp bin/puzzle_solver_asz future_net
#bin/puzzle_solver_asz: bin/puzzle_solver_asz.o
#	@mkdir -p bin
#	$(CC) $(CFLAGS) -o $@ $^

bin/puzzle_solver_asz: src/puzzle_solver_asz.cc include/puzzle_solver.h include/error_code.h include/time_utility.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f bin/*.o
	rm -f bin/puzzle_solver_asz
