/*************************************************************************
	> File Name: data_type.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 03:04:02 AM CST
*************************************************************************/

#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include "data_io_helper.h"

namespace graph {
    const int MAX_NODE = 700;
    const int MAX_EDGE = 5000;
    template<class Type1, class Type2>
    struct Edge {
        Type1 start, end, index;
        Type2 length;
        Edge(Type1 start, Type1 end, Type1 index, Type2 length): start(start), end(end), index(index), length(length) {}
    };

    template<class Type1, class Type2>
    struct Node {
        Type1 inDegree, outDegree;
        Type2 priority;
        Node (Type2 priority): inDegree(0), outDegree(0), priority(priority) {}
        Node (Type1 in, Type1 out, Type2 priority): inDegree(in), outDegree(out), priority(priority) {}
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
            return ASZ_SUCC;
        }

        int ReadGraphInfo(const std::string& graphFile) {
            DataIOHelper::InitInput(graphFile);
            while (!DataIOHelper::IsReachEoF()) {
                int index = DataIOHelper::ReadOneInteger();
                int start = DataIOHelper::ReadOneInteger();
                int end = DataIOHelper::ReadOneInteger();
                int length = DataIOHelper::ReadOneInteger();
                mEdges[start].push_back(Edge<TypeEdge1, TypeEdge2>(start, end, index, length));
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
            }
            else {
                DataIOHelper::WriteOneString("NA");
            }
            DataIOHelper::Close();
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
    };
}

#endif /* _DATA_TYPE_H_ */
