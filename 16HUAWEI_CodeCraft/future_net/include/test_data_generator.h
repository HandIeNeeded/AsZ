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
#include <bitset>
#include "error_code.h"
#include "data_io_helper.h"
#include "data_type.h"

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
    //record used index
    std::vector<int> remainIndex;
public:
    inline int Init();

    inline void SetNodeNumber(int nodeNumber);

    inline void SetEdgeNumber(int edgeNumber);

    inline void SetConnected();

    inline void ResetConnected();

    inline int GenerateIndex();

    inline int Random(int lowerBound, int upperBound);

    int GenEdgeInSet(std::bitset<graph::MAX_NODE>& connectNode, int edgeNumber);

    int GenOneDataSet(const std::string& fileName);

    int GenDataSets(const std::vector<std::string>& fileNames);
};

int TestDataGenerator::Init() {
    if (!triggerRand) {
        triggerRand = true;
        srand(time(0) % clock());
    }
    mEdges.clear();
    mEdges.resize(mNode);
    mOutDegree.clear();
    mOutDegree.resize(mNode, 0);
    //default source and sink
    mSource = 0, mSink = mNode - 1;
    remainIndex.clear();
    for (int index = 0; index < graph::MAX_EDGE; index++) {
        remainIndex.push_back(index);
        std::swap(remainIndex[remainIndex.size() - 1], remainIndex[rand() % remainIndex.size()]);
    }
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

int TestDataGenerator::GenerateIndex() {
    int res = remainIndex.back();
    remainIndex.pop_back();
    return res;
}

int TestDataGenerator::Random(int lowerBound, int upperBound) {
    return lowerBound + rand() % (upperBound - lowerBound + 1);
}

int TestDataGenerator::GenEdgeInSet(std::bitset<graph::MAX_NODE>& connectNode, int edgeNumber) {
    std::vector<int> inSetNode;
    for (int i = 0; i < mNode; i++) {
        if (connectNode.test(i)) {
            inSetNode.push_back(i);
        }
    }
    while (edgeNumber--) {
        int index = GenerateIndex();
        int start = Random(0, inSetNode.size() - 1);
        int end = (start + Random(1, inSetNode.size() - 1)) % inSetNode.size();
        start = inSetNode[start], end = inSetNode[end];
        int length = Random(1, 20);
        mEdges[start].push_back(TestEdge(index, start, end, length));
    }
    return ASZ_SUCC;
}

int TestDataGenerator::GenOneDataSet(const std::string& fileName) {
    //generator graph
    //use data_io_helper
    if (mNode > 1 && mEdge > 1); else
    return ASZ_DATA_GENERATOR_PARAMETER_MISSING_ERROR;
    int rtn;
    rtn = Init();
    CHECK_RTN_LOGE(rtn);
    std::string command = "mkdir -p " + fileName;
    std::system(command.c_str());
    LOG << "Success to create the test case " << fileName << "'s folder." << std::endl;

    if (mConnected) {
        // Generate a map always have a solution
        // First: Find a path consists of (n - 1) edge from Source to Sink
        // Second: Randomly generate the rest (Edge - n + 1) edges connect any two nodes

        //no enough edges to construct a solution
        if (mEdge < mNode - 1) return ASZ_DATA_GENERATOR_LACK_OF_EDGE_ERROR;

        //Randomly decide the source and the sink
        mSource = Random(0, mNode - 1);
        mSink = (mSource + Random(1, mNode - 1)) % mNode;

        //consisting nodes not yet in path
        std::vector<int> notVisitedNode;
        for (int i = 0; i < mNode; i++)
            if (i != mSource && i != mSink)
                notVisitedNode.push_back(i);

        //Find a path from source to sink
        int currentNode = mSource;
        for (int i = 0; i < mNode - 2; i++) {
            std::swap(notVisitedNode[Random(0, notVisitedNode.size() - 1)], notVisitedNode[notVisitedNode.size() - 1]);
            int nextNode = notVisitedNode.back();
            notVisitedNode.pop_back();
            mEdges[currentNode].push_back(TestEdge(GenerateIndex(), currentNode, nextNode, Random(11, 20)));
            currentNode = nextNode;
        }
        mEdges[currentNode].push_back(TestEdge(GenerateIndex(), currentNode, mSink, Random(11, 20)));

        //generate the rest edge Randomly
        int countEdge = mNode - 1;
        while (countEdge++ < mEdge) {
            int index = GenerateIndex();
            int start = Random(0, mNode - 1);
            int end = Random(0, mNode - 1);
            int length = Random(1, 10);
            mEdges[start].push_back(TestEdge(index, start, end, length));
        }
    } else {
        // Generate a map with no solution
        // A map not connected will definitely have no solution
        // Divide the nodes into two set and generator edges seperately in two sets

        //tricky test, can only have edges from sink to source
        if (mNode == 2) return ASZ_DATA_GENERATOR_LACK_OF_NODE_ERROR;

        //mark the nodes in the same set
        std::bitset<graph::MAX_NODE> connectNode;

        //mSource component
        for (int i = 0; i < mNode; i++) {
            if (i == mSource) {                     //must have source
                connectNode.set(i);
            } else
            if (i == mSink) {                       //mustn't have sink
                connectNode.reset(i);
            } else
            if (Random(0, 1)) {                       //Randomly have other nodes
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
    int excludeNode = Random(0, mNode - 2);
    std::vector<int> includeNode;
    for (int i = 1; i < mNode - 1; i++) {
        includeNode.push_back(i);
    }
    includeNode.push_back(0);
    includeNode.push_back(mNode - 1);
    for (int i = 0; i < excludeNode; i++) {
        int x = Random(0, includeNode.size() - 1);
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
    LOG << "Success to generate one test case " << fileName << "." << std::endl;

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
