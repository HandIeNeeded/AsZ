/*************************************************************************
	> File Name: puzzle_solver.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 11:28:46 AM CST
*************************************************************************/

#ifndef _PUZZLE_SOLVER_H_
#define _PUZZLE_SOLVER_H_
#include "data_type.h"
#include "data_io_helper.h"
#include "time_utility.h"
#include "test_data_generator.h"
#include "solution_checker.h"
#include "error_code.h"

class PuzzleSolver {
public:
    PuzzleSolver();
    ~PuzzleSolver();

    int Init();

    int RunTest(int n);

    int Solve();

private:
    DirectedGraph mGraph;
    DataIOHelper mDataIOHelper;
    TestDataGenerator mDataGenerator;
    SolutionChecker mSolutionChecker;
};
#endif /* _PUZZLE_SOLVER_H_ */
