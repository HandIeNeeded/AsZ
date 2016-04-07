/*************************************************************************
	> File Name: puzzle_solver_asz.cc
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 11:26:25 AM CST
*************************************************************************/

#include "puzzle_solver.h"
#include "error_code.h"
#include "time_utility.h"
#include "solution_checker.h"

int main(int argc, char **argv) {
    int rtn = ASZ_SUCC;

    PuzzleSolver asz;
    TimeHelper::Init();
    TimeHelper::CumulateStart("asz");
     if (argc > 0) {
         rtn = asz.Init(argv[1], argv[2]);
         CHECK_RTN_LOGE(rtn);
         rtn = asz.Solve(false);
         CHECK_RTN_LOGE(rtn);
         rtn = asz.Save(argv[3]);
         CHECK_RTN_LOGE(rtn);
         LOG << "Puzzle solved!!!" << std::endl;
     }
    else {
        rtn = asz.RunTests(5);
        CHECK_RTN_LOGE(rtn);
    }
    TimeHelper::CumulateStop("asz");
    TimeHelper::ShowAllMonitorIncidentsInfo();

    return ASZ_SUCC;
}
