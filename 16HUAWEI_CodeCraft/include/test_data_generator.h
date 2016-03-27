/*************************************************************************
	> File Name: test_data_generator.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 11:25:28 AM CST
*************************************************************************/

#ifndef _TEST_DATA_GENERATOR_H_
#define _TEST_DATA_GENERATOR_H_

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "error_code.h"
#include "data_io_helper.h"

#define INDEX_RANGE 1000

class Edge {
    Edge() {}
    Edge(int index, int begin, int end, int length) : index(index), begin(begin), end(end), length(length) {}
public:
    int index, begin, end, length;
};

class TestDataGenerator {
public:
    //node number, edge number
    int mNode, mEdge;
    //source id , sink id
    int mSource, mSink;
    //whether connected
    bool mConnected;
    //count node outdegree
    std::vector<int> mOutDegree;
    //edge generated
    std::vector<std::vector<Edge>> mEdges;
public:
    inline int Init();

    inline void SetNodeNumber(int nodeNumber);

    inline void SetEdgeNumber(int edgeNumber);

    inline void SetConnected();

    inline void ResetConnected();

    int GenEdgeInSet(std::bitset<mNode>& connectNode, int edgeNumber);

    int GenOneDataSet(const std::string& fileName);

    static inline int GenDataSets(const std::vector<std::string>& fileNames);
};

int TestDataGenerator::Init() {
    mEdges.clear();
    mEdges.resize(mNode);
    mOutDegree.clear();
    mOutDegree.resize(mNode, 0);
    mSource = 0, mSink = mNode - 1;
    return ASZ_SUCC;
}

void TestDataGenerator::SetNodeNumber(int nodeNumber) {
    mNode = nodeNumber;
}

void TestDataGenerator::SetEdgeNumber(int edgeNumber) {
    mEdge = edgeNumber;
}

void TestDataGenerator::SetConnected() {
    mConnected = true;
}

void TestDataGenerator::ResetConnected() {
    mConnected = false;
}

int TestDataGenerator::GenEdgeInSet(std::bitset<mNode>& connectNode, int edgeNumber) {
    std::vector<int> inSetNode;
    for (int i = 0; i < mNode; i++) {
        if (connectNode.test(i)) {
            inSetNode.push_back(i);
        }
    }
    while (edgeNumber--) {
        int index = rand() % INDEX_RANGE;
        int start = rand() % inSetNode.size();
        int end = (start + rand() % (inSetNode.size() - 1) + 1) % inSetNode.size();
        start = inSetNode[start], end = inSetNode[end];
        int length = rand() % 20 + 1;
        mEdges[start].push_back(Edge(index, start, end, length));
    }
    return ASZ_SUCC;
}

int TestDataGenerator::GenOneDataSet(const std::string& fileName) {
    //generator graph
    //use data_io_helper
    if (mNode > 1 && mEdge > 1); else
    return ASZ_DATA_GENERATOR_PARAMETER_MISSING_ERROR;
    srand(time(0));
    int rtn;
    rtn = Init();
    CHECK_RTN_LOGE(rtn);
    if (mConnected) {
        if (mEdge < mNode - 1) return ASZ_DATA_GENERATOR_LACK_OF_EDGE_ERROR;
        std::vector<int> notVisitedNode;
        for (int i = 0; i < mNode; i++)
            if (i != mSource && i != mSink)
                notVisitedNode.push_back(i);
        int currentNode = mSource;
        for (int i = 0; i < mNode - 2; i++) {
            swap(notVisitedNode[rand() % notVisitedNode.size()], notVisitedNode[notVisitedNode.size() - 1]);
            int nextNode = notVisitedNode.back();
            notVisitedNode.pop_back();
            mEdges[currentNode].push_back(Edge(rand() % INDEX_RANGE, currentNode, nextNode, rand() % 20 + 1));
            currentNode = nextNode;
        }
        mEdges[currentNode].push_back(Edge(rand() % INDEX_RANGE, currentNode, mSink, rand() % 20 + 1));
        int countEdge = mNode - 1;
        while (countEdge++ < mEdge) {
            int index = rand() % INDEX_RANGE;
            int start = rand() % mNode;
            int end = rand() % mNode;
            int length = rand() % 20 + 1;
            mEdges[start].push_back(Edge(index, start, end, length));
        }
    } else {
        if (mNode == 2) return ASZ_DATA_GENERATOR_LACK_OF_NODE_ERROR;
        std::bitset<mNode> connectNode;
        //mSource component
        for (int i = 0; i < mNode; i++) {
            if (i == mSource) {
                connectNode.set(i);
            } else
            if (i == mSink) {
                connectNode.reset(i);
            } else
            if (rand() & 1) {
                connectNode.set(i);
            } else {
                connectNode.reset(i);
            }
        }
        int countEdge = 0;
        int assignEdge = mEdge / 2;
        if (inSetNode.size() == 1) {
            assignEdge = 0;
        } else
        if (inSetNode.size() == mNode - 1) {
            assignEdge = mEdge;
        }
        rtn = GenEdgeInSet(connectNode, assignEdge);
        CHECK_RTN_LOGE(rtn);
        countEdge += assignEdge;
        for (int i = 0; i < mNode; i++) {
            if (connectNode.test(i)) {
                connectNode.reset(i);
            }
        }
        assignEdge = mEdge - countEdge;
        rtn = GenEdgeInSet(connectNode, assignEdge);
        CHECK_RTN_LOGE(rtn);
        countEdge += assignEdge;
    }
    return ASZ_SUCC;
}

int TestDataGenerator::GenDataSets(const std::vector<std::string>& fileNames) {
    int rtn = ASZ_SUCC;
    for (auto &str: fileNames) {
        rtn = GenOneDataSet(str);
        CHECK_RTN_LOGE(rtn);
    }
    return ASZ_SUCC;
}

#endif /* _TEST_DATA_GENERATOR_H_ */
