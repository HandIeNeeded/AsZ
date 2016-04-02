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
#define TEST_NODE_SIZE 600

#ifndef _RANDOM_TRIGGER_
#define _RANDOM_TRIGGER_
static bool triggerRand = false;
#endif

struct TestEdge {
    int index, start, end, length;
    TestEdge() {}
    TestEdge(int index, int start, int end, int length) : index(index), start(start), end(end), length(length) {}
};

class TestDataGenerator {
private:
    //node number, edge number
    int mNode, mEdge;
    //source id , sink id
    int mSource, mSink;
    //whether connected
    bool mConnected;
    //count node outdegree
    std::vector<int> mOutDegree;
    //edge generated
    std::vector<std::vector<TestEdge>> mEdges;
public:
    inline int Init();

    inline void SetNodeNumber(int nodeNumber);

    inline void SetEdgeNumber(int edgeNumber);

    inline void SetConnected();

    inline void ResetConnected();

    inline int GenEdgeInSet(std::bitset<TEST_NODE_SIZE>& connectNode, int edgeNumber);

    inline int GenOneDataSet(const std::string& fileName);

    inline int GenDataSets(const std::vector<std::string>& fileNames);
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

int TestDataGenerator::GenEdgeInSet(std::bitset<TEST_NODE_SIZE>& connectNode, int edgeNumber) {
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
        mEdges[start].push_back(TestEdge(index, start, end, length));
    }
    return ASZ_SUCC;
}

int TestDataGenerator::GenOneDataSet(const std::string& fileName) {
    if (!triggerRand) {
        triggerRand = true;
        srand(time(0));
    }
    //generator graph
    //use data_io_helper
    if (mNode > 1 && mEdge > 1); else
    return ASZ_DATA_GENERATOR_PARAMETER_MISSING_ERROR;
    int rtn;
    rtn = Init();
    CHECK_RTN_LOGE(rtn);
    if (mConnected) {

        std::cerr << "Start generate." << std::endl;

        // Generate a map always have a solution
        // First: Find a path consists of (n - 1) edge from Source to Sink
        // Second: randomly generate the rest (Edge - n + 1) edges connect any two nodes

        //no enough edges to construct a solution
        if (mEdge < mNode - 1) return ASZ_DATA_GENERATOR_LACK_OF_EDGE_ERROR;

        //consisting nodes not yet in path
        std::vector<int> notVisitedNode;
        for (int i = 0; i < mNode; i++)
            if (i != mSource && i != mSink)
                notVisitedNode.push_back(i);

        //Find a path from source to sink
        int currentNode = mSource;
        for (int i = 0; i < mNode - 2; i++) {
            std::swap(notVisitedNode[rand() % notVisitedNode.size()], notVisitedNode[notVisitedNode.size() - 1]);
            int nextNode = notVisitedNode.back();
            notVisitedNode.pop_back();
            mEdges[currentNode].push_back(TestEdge(rand() % INDEX_RANGE, currentNode, nextNode, rand() % 20 + 1));
            currentNode = nextNode;
        }
        mEdges[currentNode].push_back(TestEdge(rand() % INDEX_RANGE, currentNode, mSink, rand() % 20 + 1));

        //generate the rest edge randomly
        int countEdge = mNode - 1;
        while (countEdge++ < mEdge) {
            int index = rand() % INDEX_RANGE;
            int start = rand() % mNode;
            int end = rand() % mNode;
            int length = rand() % 20 + 1;
            mEdges[start].push_back(TestEdge(index, start, end, length));
        }

        std::cerr << mEdges.size() << std::endl;

        std::cerr << "Finish generate." << std::endl;
    } else {
        // Generate a map with no solution
        // A map not connected will definitely have no solution
        // Divide the nodes into two set and generator edges seperately in two sets

        //tricky test, can only have edges from sink to source
        if (mNode == 2) return ASZ_DATA_GENERATOR_LACK_OF_NODE_ERROR;

        //mark the nodes in the same set
        std::bitset<TEST_NODE_SIZE> connectNode;

        //mSource component
        for (int i = 0; i < mNode; i++) {
            if (i == mSource) {                     //must have source
                connectNode.set(i);
            } else
            if (i == mSink) {                       //mustn't have sink
                connectNode.reset(i);
            } else
            if (rand() & 1) {                       //randomly have other nodes
                connectNode.set(i);
            } else {
                connectNode.reset(i);
            }
        }

        //try to equally distribute the edge into two sets
        int assignEdge = mEdge / 2, countEdge = 0;
        if ((int)connectNode.count() == 1) {             //set with only 1 node can not have any edges
            assignEdge = 0;
        } else
        if (connectNode.count() == (unsigned int)mNode - 1) {     //if the other set have one edge, this set must hava all the edges
            assignEdge = mEdge;
        }

        rtn = GenEdgeInSet(connectNode, assignEdge);
        CHECK_RTN_LOGE(rtn);
        countEdge += assignEdge;

        //generate the edges in another set
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

    //print the edges
    DataIOHelper::InitOutput(fileName + "/topo.csv");
    for (int i = 0; i < mNode; i++) {
        for (auto &edge: mEdges[i]) {
            DataIOHelper::WriteOneInterger(edge.index);
            DataIOHelper::WriteOneChar(',');
            DataIOHelper::WriteOneInterger(edge.start);
            DataIOHelper::WriteOneChar(',');
            DataIOHelper::WriteOneInterger(edge.end);
            DataIOHelper::WriteOneChar(',');
            DataIOHelper::WriteOneInterger(edge.length);
            DataIOHelper::WriteOneChar('\n');
        }
    }
    DataIOHelper::Close();

    //generate the including node set
    int excludeNode = rand() % (mNode - 1);
    std::vector<int> includeNode;
    for (int i = 1; i < mNode - 1; i++) {
        includeNode.push_back(i);
    }
    includeNode.push_back(0);
    includeNode.push_back(mNode - 1);
    for (int i = 0; i < excludeNode; i++) {
        int x = rand() % includeNode.size();
        includeNode[x] = includeNode.back();
        includeNode.pop_back();
    }

    //print the edge number, node number and including node set
    DataIOHelper::InitOutput(fileName + "/demand.csv");
    DataIOHelper::WriteOneInterger(0);
    DataIOHelper::WriteOneChar(',');
    DataIOHelper::WriteOneInterger(mNode - 1);
    DataIOHelper::WriteOneChar(',');
    for (unsigned int i = 0; i < includeNode.size(); i++) {
        DataIOHelper::WriteOneInterger(includeNode[i]);
        if (i == includeNode.size() - 1) {
            DataIOHelper::WriteOneChar('\n');
        } else {
            DataIOHelper::WriteOneChar('|');
        }
    }
    DataIOHelper::Close();

    return ASZ_SUCC;
}

int TestDataGenerator::GenDataSets(const std::vector<std::string>& fileNames) {
    if (!triggerRand) {
        triggerRand = true;
        srand(time(0));
    }
    int rtn = ASZ_SUCC;
    for (auto &str: fileNames) {
        rtn = GenOneDataSet(str);
        CHECK_RTN_LOGE(rtn);
    }
    return ASZ_SUCC;
}

#endif /* _TEST_DATA_GENERATOR_H_ */
