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

    int RunOneTest(const std::string& testName);

    int RunTests(int n);

    int Solve();

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

int PuzzleSolver::RunOneTest(const std::string& testName) {
    int rtn = TestDataGenerator::GenOneDataSet(testName);
    CHECK_RTN_LOGE(rtn);
    std::string commandLine = "mkdir -p " + testName;
    system(commandLine.c_str());
    rtn = mGraph.ReadGraphInfo(testName + "/topo.csv");
    CHECK_RTN_LOGE(rtn);
    rtn = mGraph.ReadKeyNodesInfo(testName + "/demand.csv");
    CHECK_RTN_LOGE(rtn);
    Solve();
    CHECK_RTN_LOGE(rtn);
    Save(testName + "/asz_result.csv");
    CHECK_RTN_LOGE(rtn);
    return ASZ_SUCC;
}

int PuzzleSolver::RunTests(int n) {
    int rtn = ASZ_SUCC;
    for (int i = 0; i < n; i++) {
        std::string testName = "./batch_test_" + std::to_string(i);
        Init();
        rtn = RunOneTest(testName);
        CHECK_RTN_LOGE(rtn);
    }
    return ASZ_SUCC;
}

int PuzzleSolver::Solve() {
    
    return ASZ_SUCC;
}

int PuzzleSolver::Save(const std::string& outputFile) {
    mGraph.SavePathsInfo(outputFile);
    return ASZ_SUCC;
}

#endif /* _PUZZLE_SOLVER_H_ */

