/*************************************************************************
	> File Name: solution_checker.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 11:27:49 AM CST
*************************************************************************/

#ifndef _SOLUTION_CHECKER_H_
#define _SOLUTION_CHECKER_H_

#include <bitset>
#include "error_code.h"
#include "time_utility.h"
#include "data_type.h"

using namespace graph;

class SolutionChecker {
public:
    static inline int Init(Graph<int, int, int, int>* pGraph);

    static inline int IsCorrect(const std::vector<Edge<int, int>>& answer, bool& isCorrect);

private:
    static const Graph<int, int, int, int>* mpGraph;
    static std::bitset<graph::MAX_NODE> mMarkMap;
};

int SolutionChecker::Init(Graph<int, int, int, int>* pGraph) {
    if (pGraph == NULL) return ASZ_NULL_POINTER_ERROR;
    mpGraph = pGraph;
    mMarkMap.reset();
    return ASZ_SUCC;
}

int SolutionChecker::IsCorrect(const std::vector<Edge<int, int>>& answer, bool& isCorrect) {
    int rtn = ASZ_SUCC;
    //no edge error
    if (answer.size() == 0) {
        isCorrect = false;
        return ASZ_SOLUTION_CHECKER_NO_EDGE_ERROR;
    }
    if (answer.front().start != mpGraph->source) {
        isCorrect = false;
        return ASZ_SOLUTION_CHECKER_INVALID_START_POINT_ERROR;
    }
    if (answer.back().end != mpGraph->sink) {
        isCorrect = false;
        return ASZ_SOLUTION_CHECKER_INVALID_END_POINT_ERROR;
    }
    mMarkMap[mpGraph->source] = 1;
    int previousNode = mpGraph->source;
    for (int i = 0; i < int(answer.size()); i++) {
        if (answer[i].start != previousNode) {
            isCorrect = false;
            return ASZ_SOLUTION_CHECKER_PATH_NOT_CONNECTED_ERROR;
        }
        if (mMarkMap.test(answer[i].end)) {
            isCorrect = false;
            return ASZ_SOLUTION_CHECKER_REPEAT_NODES_ERROR;
        }
        previousNode = answer[i].end;
        mMarkMap.set(answer[i].end);
    }
    for (auto& node: mpGraph->mKeyNodes) {
        if (!mMarkMap.test(node)) {
            isCorrect = false;
            return ASZ_SOLUTION_CHECKER_NOT_COVER_ALL_KEY_POINTS_ERROR;
        }
    }
    isCorrect = true;
    return ASZ_SUCC;
}
#endif /* _SOLUTION_CHECKER_H_ */
