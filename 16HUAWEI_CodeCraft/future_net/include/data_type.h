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
    const double MAGIC_COEF = 2.0;
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
            mCurrentPaths.clear();
            mPaths.clear();
            mNode = mEdge = 0;
            mSource = mSink = 0;
            mCounter = (int)1e7;
            mMarkMap.reset();
            mKeyNodesMap.reset();
            mPathLength = MAX_NODE * 20;
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

            //greedy
            for (TypeEdge1 node = 0; node < mNode; node++) {
            	for (unsigned int i = 0; i < mEdges[node].size(); i++)
            		for (unsigned int j = i + 1; j < mEdges[node].size(); j++)
            			if (mEdges[node][i].length > mEdges[node][j].length)
            				std::swap(mEdges[node][i], mEdges[node][j]);
            }

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
            pathLength = mPathLength;
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
        //shortest path length
        int mPathLength;
        //counter restrict dfs time
        int mCounter;
        std::vector<Node<TypeNode1, TypeNode2>> mNodes;
        std::vector<std::vector<Edge<TypeEdge1, TypeEdge2>>> mEdges;
        //key nodes, have to cover
        std::vector<int> mKeyNodes;
        //current path
        std::vector<Edge<TypeEdge1, TypeEdge2>> mCurrentPaths;
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
            if (mCounter == 0)
                return ASZ_SUCC;
            mCounter--;
            mMarkMap.set(currentNode);
            if (currentNode == mSink) {
                if ((mMarkMap & mKeyNodesMap) == mKeyNodesMap) {
                    mIsSolutionExist = true;
                	mPaths.assign(mCurrentPaths.begin(), mCurrentPaths.end());
                    mPathLength = pathLength;
                }
                mMarkMap.reset(currentNode);
                return ASZ_SUCC;
            }
            for (auto& edge: mEdges[currentNode]) {
                TypeEdge1 nextNode = edge.end;
                TypeEdge2 length = edge.length;
                if (mMarkMap.test(nextNode) || pathLength + length >= mPathLength)
                	continue;
                pathLength += length;
                mCurrentPaths.push_back(edge);
                FindPath(nextNode, pathLength);
                mCurrentPaths.pop_back();
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
            LOG << "Start: " << start << std::endl;
            for (int i = 0; i < 5; i++) {
                std::cerr << mMarkMap.test(i) << ' ';
            }
            std::cerr << std::endl;
            distanceFromStart.clear();
            distanceFromStart.assign(MAX_NODE, Infinity);
            previousPaths.clear();
            previousPaths.assign(MAX_NODE, Edge<TypeEdge1, TypeEdge2>());
            distanceFromStart[start] = 0;
            for (int i = 0; i < 5; i++) {
                std::cerr << distanceFromStart[i] << ' ';
            }
            std::cerr << std::endl;
            std::bitset<MAX_NODE> visited;
            std::priority_queue<std::pair<TypeEdge2, TypeEdge1>, std::vector<std::pair<TypeEdge2, TypeEdge1>>, greater<TypeEdge2>> que;
            que.push({0, start});
            while (que.size()) {
                TypeEdge1 node = que.top().second; que.pop();
                if (visited.test(node)) continue;
                visited.set(node);
                LOG << "Node: " << node << std::endl;
                for (auto& edge: mEdges[node]) {
                    TypeEdge1 nextNode = edge.end;
                    LOG << "Next node: " << nextNode << ' ' << mMarkMap.test(nextNode) << std::endl;
                    if (mMarkMap.test(nextNode)) continue;
                    if (distanceFromStart[nextNode] > edge.length + distanceFromStart[node]) {
                        distanceFromStart[nextNode] = edge.length + distanceFromStart[node];
                        que.push({distanceFromStart[nextNode], nextNode});
                        previousPaths[nextNode] = edge;
                    }
                }
            }
            for (int i = 0; i < 5; i++) {
                std::cerr << distanceFromStart[i] << ' ';
            }
            std::cerr << std::endl;
            return ASZ_SUCC;
        }

        struct comp {
            bool operator () (const std::pair<double, Edge<TypeEdge1, TypeEdge2>>& a, const std::pair<double, Edge<TypeEdge1, TypeEdge2>>& b) const {
                return a.first < b.first || (a.first == b.first && a.second.end < b.second.end);
            }
        } myComp;

        int UpdateCandidateNodes(const Edge<TypeEdge1, TypeEdge2>& currentEdge, const std::vector<TypeEdge2>& distanceFromStart, const std::vector<Edge<TypeEdge1, TypeEdge2>>& previousPaths, std::vector<std::pair<double, Edge<TypeEdge1, TypeEdge2>>>& candidateNodes) {
            double score = 0.0;
            double edgeLengthAverage = 0.0;
            double edgeLengthSum = currentEdge.length;
            int keyNodeCount = 0;
            int totalEdgeCount = 1;
            for (int i = 0; i < MAX_NODE; i++) if (mKeyNodesMap.test(i) && !mMarkMap.test(i) && distanceFromStart[i] != Infinity) {
                LOG << i << ' ' << distanceFromStart[i] << std::endl;
                keyNodeCount++;
                int lastNode = i;
                while (lastNode != currentEdge.end) {
                    LOG << "Last node: " << lastNode << std::endl;
                    edgeLengthSum += previousPaths[lastNode].length;
                    lastNode = previousPaths[lastNode].start;
                    totalEdgeCount++;
                }
            }
            edgeLengthAverage = edgeLengthSum / totalEdgeCount;
            score -= MAGIC_COEF * edgeLengthAverage * keyNodeCount;
            score += edgeLengthSum;
            candidateNodes.push_back({score, currentEdge});
            return ASZ_SUCC;
        }

        int FindPathByAstar(TypeEdge1 node, TypeEdge2& pathLength, bool isReadyToFindSink) {
            LOG << "Now node: " << node << ", path length: " << pathLength << std::endl;
            mMarkMap.set(node);
            if (!isReadyToFindSink) isReadyToFindSink = (mMarkMap & mKeyNodesMap).count() == mKeyNodesMap.count();
            if (isReadyToFindSink) {
                std::vector<TypeEdge2> distanceFromStart;
                std::vector<Edge<TypeEdge1, TypeEdge2>> previousPaths;
                LOG << "Before dijk" << std::endl;
                Dijkstra(node, distanceFromStart, previousPaths);
                LOG << "After dijk" << std::endl;
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
                LOG << "hehe" << std::endl;
                for (auto& edge: mEdges[node]) {
                    TypeEdge1 nextNode = edge.end;
                    if (mMarkMap.test(nextNode)) continue;
                    else {
                        std::vector<TypeEdge2> distanceFromStart;
                        std::vector<Edge<TypeEdge1, TypeEdge2>> previousPaths;
                        LOG << "Before dijk" << std::endl;
                        Dijkstra(nextNode, distanceFromStart, previousPaths);
                        LOG << "After dijk" << std::endl;
                        UpdateCandidateNodes(edge, distanceFromStart, previousPaths, candidateNodes);
                    }
                }
                LOG << "xixi" << ' ' << candidateNodes.size() << std::endl;
                std::sort(candidateNodes.begin(), candidateNodes.end(), myComp);
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
