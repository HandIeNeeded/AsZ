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
    static int Init(const std::string& input, const std::string& output) {
        Close();
        mFileInStream.open(input.c_str());
        mFileOutStream.open(output.c_str());
        return ASZ_SUCC;
    }

    static int InitInput(const std::string& input) {
        mFileInStream.close();
        std::cerr << "Open input file: " << input << std::endl;
        mFileInStream.open(input.c_str());
        return ASZ_SUCC;
    }

    static int InitOutput(const std::string& output) {
        mFileOutStream.close();
        std::cerr << "Open output file: " << output << std::endl;
        mFileOutStream.open(output.c_str());
        return ASZ_SUCC;
    }
    
    static int Close() {
        mFileInStream.close();
        mFileOutStream.close();
        return ASZ_SUCC;
    }

    static bool IsReachEoF() {
        return mFileInStream.eof();
    }

    static inline char ReadOneChar() {
        char c;
        mFileInStream >> c;
        return c;
    }

    static inline int ReadOneInteger() {
        int x = 0;
        mFileInStream >> x;
        mFileInStream.ignore(1, '\n');
        std::cerr << x << std::endl;
        return x;
    }

    static inline void WriteOneString(const std::string& str) {
        mFileOutStream << str;
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

std::ifstream DataIOHelper::mFileInStream;
std::ofstream DataIOHelper::mFileOutStream;
#endif /* _DATA_IO_HELPER_H_ */
