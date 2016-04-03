/*************************************************************************
	> File Name: data_type.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 03:04:02 AM CST
*************************************************************************/

#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#include <algorithm>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include "data_io_helper.h"
#include "max_flow_solver.h"
#include "time_utility.h"

#ifndef _RANDOM_TRIGGER_
#define _RANDOM_TRIGGER_
static bool triggerRand = false;
#endif

namespace graph {
    const int MAX_NODE = 700;
    const int MAX_EDGE = 5000;
    const int Infinity = 20000;
    const double MAGIC_NUMBER = 2.0;
    const double MAGIC_COEF = 1.0;
    template<class Type1, class Type2>
    struct Edge {
        Type1 start, end, index;
        Type2 length;
        Edge() {}
        Edge(Type1 start, Type1 end, Type1 index, Type2 length): start(start), end(end), index(index), length(length) {}
    };

    template<class Type1, class Type2>
    struct Node {
        Type1 index;
        Type2 priority;
        Node() {}
        Node (Type1 index, Type2 priority): index(index), priority(priority) {}
    };

    template<class TypeNode1, class TypeNode2, class TypeEdge1, class TypeEdge2>
    class Graph {
    public:
        int Init() {
            mIsSolutionExist = false;
            mEdges.clear();
            mNodes.clear();
            mKeyNodes.clear();
            mPaths.clear();
            mNode = mEdge = 0;
            mSource = mSink = 0;
            mMarkMap.reset();
            mKeyNodesMap.reset();
            return ASZ_SUCC;
        }

        int ReadGraphInfo(const std::string& graphFile) {
            DataIOHelper::InitInput(graphFile);
            mEdges.resize(MAX_NODE);
            while (!DataIOHelper::IsReachEoF()) {
                int index = DataIOHelper::ReadOneInteger();
                int start = DataIOHelper::ReadOneInteger();
                int end = DataIOHelper::ReadOneInteger();
                mMarkMap.set(start), mMarkMap.set(end);
                int length = DataIOHelper::ReadOneInteger();
                bool edgeExisted = false;
                for (auto &edge: mEdges[start]) {
                    if (edge.end == end) {
                        edgeExisted = true;
                        if (length < edge.length)
                            edge.length = length;
                    }
                }
                if (edgeExisted) continue;
                mEdges[start].push_back(Edge<TypeEdge1, TypeEdge2>(start, end, index, length));
                mEdge++;
            }
            mNode = mMarkMap.count();
            mMarkMap.reset();
            return ASZ_SUCC;
        }

        int ReadKeyNodesInfo(const std::string& nodeFile) {
            DataIOHelper::InitInput(nodeFile);
            mSource = DataIOHelper::ReadOneInteger();
            mSink = DataIOHelper::ReadOneInteger();
            while (!DataIOHelper::IsReachEoF()) {
                int x = DataIOHelper::ReadOneInteger();
                mKeyNodes.push_back(x);
                mKeyNodesMap.set(x);
            }
            return ASZ_SUCC;
        }

        int SavePathsInfo(const std::string& outputFile) {
            DataIOHelper::InitOutput(outputFile);
            if (mIsSolutionExist) {
                bool first = false;
                for(auto& edge: mPaths) {
                    if (first) DataIOHelper::WriteOneChar('|');
                    DataIOHelper::WriteOneInterger(edge.index);
                    first = true;
                }
                DataIOHelper::WriteOneChar('\n');
            }
            else {
                DataIOHelper::WriteOneString("NA\n");
            }
            DataIOHelper::Close();
            return ASZ_SUCC;
        }

        int PrintNodePath() {
            LOG << "Path of nodes: " << mSource;
            for (auto &edge: mPaths) {
                std::cerr << ", " << edge.end;
            }
            std::cerr << std::endl;
            return ASZ_SUCC;
        }

        int BruteForce(int& pathLength) {
            InitAnswer();
            pathLength = 0;
            FindPath(mSource, pathLength);
            return ASZ_SUCC;
        }

        //not in use right now
        int CheckSolutionExistByMaxFlow() {
            MaxFlow<MAX_NODE, MAX_EDGE << 1, TypeNode1> flow;
            flow.init(mNode, mNode + 1);
            return ASZ_SUCC;
        }

        int AStarSearch(int &pathLength) {
            InitAnswer();
            pathLength = 0;
            FindPathByAstar(mSource, pathLength, false);
            return ASZ_SUCC;
        }

    public:

        bool mIsSolutionExist;
        //node count, edge count
        int mNode, mEdge;
        //start point, destination
        int mSource, mSink;
        std::vector<Node<TypeNode1, TypeNode2>> mNodes;
        std::vector<std::vector<Edge<TypeEdge1, TypeEdge2>>> mEdges;
        //key nodes, have to cover
        std::vector<int> mKeyNodes;
        //answer path
        std::vector<Edge<TypeEdge1, TypeEdge2>> mPaths;
        //is visited mark map
        std::bitset<MAX_NODE> mMarkMap;
        //is key point mark map
        std::bitset<MAX_NODE> mKeyNodesMap;

    private:

        int InitAnswer() {
            mMarkMap.reset();
            mPaths.clear();
            return ASZ_SUCC;
        }

        int FindPath(TypeEdge1 currentNode, TypeEdge2& pathLength) {
            if (mMarkMap.test(currentNode))
                return ASZ_SUCC;
            mMarkMap.set(currentNode);
            if (currentNode == mSink) {
                if ((mMarkMap & mKeyNodesMap) == mKeyNodesMap) {
                    mIsSolutionExist = true;
                    return ASZ_SUCC;
                } else {
                    mMarkMap.reset(currentNode);
                    return ASZ_SUCC;
                }
            }
            for (auto &edge: mEdges[currentNode]) {
                TypeEdge1 nextNode = edge.end;
                TypeEdge2 length = edge.length;
                pathLength += length;
                mPaths.push_back(edge);
                FindPath(nextNode, pathLength);
                if (mIsSolutionExist)
                    return ASZ_SUCC;
                mPaths.pop_back();
                pathLength -= length;
            }
            mMarkMap.reset(currentNode);
            return ASZ_SUCC;
        }

        template<class Type>
        struct greater {
            bool operator () (const std::pair<Type, TypeEdge1>& lhs, const std::pair<Type, TypeEdge1>& rhs) const {
                return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
            }
        };

        int Dijkstra(int start, std::vector<TypeEdge2>& distanceFromStart, std::vector<Edge<TypeEdge1, TypeEdge2>>& previousPaths) {
            distanceFromStart.clear();
            distanceFromStart.assign(MAX_NODE, Infinity);
            previousPaths.clear();
            previousPaths.assign(MAX_NODE, Edge<TypeEdge1, TypeEdge2>());
            distanceFromStart[start] = 0;
            std::bitset<MAX_NODE> visited;
            std::priority_queue<std::pair<TypeEdge2, int>, std::vector<std::pair<TypeEdge2, int>>, greater<TypeEdge2>> que;
            que.push({0, start});
            visited.set(start);
            while (que.size()) {
                TypeEdge1 node = que.top().second; que.pop();
                if (visited.test(node)) continue;
                visited.set(node);
                for (auto& edge: mEdges[node]) {
                    TypeEdge1 nextNode = edge.end;
                    if (mMarkMap.test(nextNode)) continue;
                    if (distanceFromStart[nextNode] > edge.length + distanceFromStart[node]) {
                        distanceFromStart[nextNode] = edge.length + distanceFromStart[node];
                        que.push({distanceFromStart[nextNode], nextNode});
                        previousPaths[nextNode] = edge;
                    }
                }
            }
            return ASZ_SUCC;
        }

        struct comp {
            bool operator () (const std::pair<double, Edge<TypeEdge1, TypeEdge2>>& a, const std::pair<double, Edge<TypeEdge1, TypeEdge2>>& b) const {
                return a.first < b.first || (a.first == b.first && a.second.end < b.second.end);
            }
        };

        int UpdateCandidateNodes(int currentNode, const Edge<TypeEdge1, TypeEdge2>& currentEdge, const std::vector<TypeEdge2>& distanceFromStart, const std::vector<Edge<TypeEdge1, TypeEdge2>>& previousPaths, std::vector<std::pair<double, Edge<TypeEdge1, TypeEdge2>>>& candidateNodes) {
            double score = 0.0;
            double edgeLengthAverage = 0.0;
            int totalEdgeCount = 0;
            for (int i = 0; i < MAX_NODE; i++) if (mKeyNodesMap.test(i) && !mMarkMap.test(i)) {
                score -= MAGIC_NUMBER;
                int lastNode = i;
                while (lastNode != currentNode) {
                    edgeLengthAverage += previousPaths[lastNode].length;
                    lastNode = previousPaths[lastNode].start;
                    totalEdgeCount++;
                }
            }
            if (totalEdgeCount == 0) return ASZ_SUCC;
            edgeLengthAverage /= totalEdgeCount;
            score += MAGIC_COEF * edgeLengthAverage;
            candidateNodes.push_back({score, currentEdge});
            return ASZ_SUCC;
        }

        int FindPathByAstar(TypeEdge1 node, TypeEdge2& pathLength, bool isReadyToFindSink) {
            mMarkMap.set(node);
            if (!isReadyToFindSink) isReadyToFindSink = (mMarkMap & mKeyNodesMap).count() == mKeyNodesMap.count();
            if (isReadyToFindSink) {
                std::vector<TypeEdge2> distanceFromStart;
                std::vector<Edge<TypeEdge1, TypeEdge2>> previousPaths;
                Dijkstra(node, distanceFromStart, previousPaths);
                if (distanceFromStart[mSink] != Infinity) {
                    mIsSolutionExist = true;
                    std::vector<Edge<TypeEdge1, TypeEdge2>> tmpEdges;
                    TypeEdge1 lastNode = mSink;
                    while (lastNode != node) {
                        tmpEdges.push_back(previousPaths[lastNode]);
                        lastNode = previousPaths[lastNode].start;
                    }
                    mPaths.insert(mPaths.end(), tmpEdges.rbegin(), tmpEdges.rend());
                    return ASZ_SUCC;
                }
                mMarkMap.reset(node);
                return ASZ_SUCC;
            }
            else {
                std::vector<std::pair<double, Edge<TypeEdge1, TypeEdge2>>> candidateNodes;
                for (auto& edge: mEdges[node]) {
                    TypeEdge1 nextNode = edge.end;
                    if (mMarkMap.test(nextNode)) continue;
                    else {
                        std::vector<TypeEdge2> distanceFromStart;
                        std::vector<Edge<TypeEdge1, TypeEdge2>> previousPaths;
                        Dijkstra(nextNode, distanceFromStart, previousPaths);
                        UpdateCandidateNodes(node, edge, distanceFromStart, previousPaths, candidateNodes);
                    }
                }
                std::sort(candidateNodes.begin(), candidateNodes.end(), comp);
                for (auto& candidate: candidateNodes) {
                    TypeEdge1 nextNode = candidate.second.end;
                    mPaths.push_back(candidate.second);
                    pathLength += candidate.second.length;
                    FindPathByAstar(nextNode, pathLength, isReadyToFindSink);
                    if (mIsSolutionExist) {
                        return ASZ_SUCC;
                    }
                    pathLength -= candidate.second.length;
                    mPaths.pop_back();
                }
                mMarkMap.reset(node);
                return ASZ_SUCC;
            }
        }
    };
}

#endif /* _DATA_TYPE_H_ */
