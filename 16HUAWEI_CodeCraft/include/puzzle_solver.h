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
    //PuzzleSolver();
    //~PuzzleSolver();
    
    int Init();

    int Init(const std::string& graphFile, const std::string& nodeFile);

    int RunOneTest();

    int RunTests(int n);

    int Solve(bool& isSolutionExist);

    int Save(const std::string& fileName);

private:
    Graph<int, int, int, int> mGraph;
};

int PuzzleSolver::Init() {
    mGraph.Init();
    return ASZ_SUCC;
}

int PuzzleSolver::Init(const std::string& graphFile, const std::string& nodeFile) {
    int rtn = ASZ_SUCC;
    Init();
    rtn = mGraph.ReadGraphInfo(graphFile);
    CHECK_RTN_LOGE(rtn);
    rtn = mGraph.ReadKeyNodesInfo(nodeFile);
    CHECK_RTN_LOGE(rtn);
    return ASZ_SUCC;
}

int PuzzleSolver::RunOneTest() {

    return ASZ_SUCC;
}

int PuzzleSolver::RunTests(int n) {

    return ASZ_SUCC;
}

int PuzzleSolver::Solve(bool& isSolutionExist) {
    
    return ASZ_SUCC;
}

int PuzzleSolver::Save(const std::string& outputFile) {
    mGraph.SavePathsInfo(outputFile);
    return ASZ_SUCC;
}

#endif /* _PUZZLE_SOLVER_H_ */

