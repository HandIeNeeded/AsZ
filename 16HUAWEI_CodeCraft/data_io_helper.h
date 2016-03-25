/*************************************************************************
	> File Name: data_io_helper.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 11:23:38 AM CST
*************************************************************************/

#ifndef _DATA_IO_HELPER_H_
#define _DATA_IO_HELPER_H_
#include <iostream>
#include <fstream>
#include <vector>
#include "error_code.h"

class DataIOHelper {
public:
    int Init(const std::string& input, const std::string& output) {
        std::ios::sync_with_stdio(0);
        mFileInStream.open(input.c_str());
        mFileOutStream.open(output.c_str());
        return ASZ_SUCC;
    }
    
    int Close() {
        mFileInStream.close();
        mFileOutStream.close();
        return ASZ_SUCC;
    }

    static inline char ReadOneChar() {
        char c;
        mFileInStream >> c;
        return c;
    }

    static inline int ReadOneInteger() {
        int x = 0;
        char c;
        while (mFileInStream >> c) {
            if (std::isdigit(c)) {
                x = 10 * x + c - '0';
            }
            else break;
        }
        return x;
    }

    static inline void WriteOneChar(char c) {
        mFileOutStream << c;
    }

    static inline void WriteOneInterger(int x) {
        if (x == 0) WriteOneChar('0');
        else {
            while (x) {
                WriteOneChar('0' + x % 10);
                x /= 10;
            }
        }
    }

private:
    static std::ifstream mFileInStream;
    static std::ofstream mFileOutStream;
};
#endif /* _DATA_IO_HELPER_H_ */
