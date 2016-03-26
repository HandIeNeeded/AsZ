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

class TestDataGenerator {
public:
    TestDataGenerator();
    ~TestDataGenerator();

    static inline int GenOneDataSet(const std::string& fileName);

    static inline int GenDataSets(const std::vector<std::string>& fileNames);
};

int TestDataGenerator::GenOneDataSet(const std::string& fileName) {
    //generator graph
    //use data_io_helper


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
