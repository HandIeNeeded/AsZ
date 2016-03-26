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

using namespace graph;

class PuzzleSolver {
public:
    PuzzleSolver();
    ~PuzzleSolver();

    int Init(const std::string& graphFile, const std::string& nodeFile);

    int RunOneTest();

    int RunTests(int n);

    int Solve();

    int Save(const std::string& fileName);

private:
    Graph<int, int, int, int> mGraph;
    TestDataGenerator mDataGenerator;
    SolutionChecker mSolutionChecker;
};
#endif /* _PUZZLE_SOLVER_H_ */
