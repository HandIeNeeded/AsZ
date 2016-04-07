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
        std::cerr << "enter init" << std::endl;
        Close();
        // mFileInStream.open(input.c_str());
        // mFileOutStream.open(output.c_str());
        ifptr = fopen(input.c_str(), "r");
        ofptr = fopen(output.c_str(), "w");
        return ASZ_SUCC;
    }

    static int InitInput(const std::string& input) {
        // mFileInStream.close();
        // LOG << "Open input file: " << input << std::endl;
        // mFileInStream.open(input.c_str());
        if (ifptr != NULL) fclose(ifptr);
        LOG << "Open input file: " << input << std::endl;
        ifptr = fopen(input.c_str(), "r");
        return ASZ_SUCC;
    }

    static int InitOutput(const std::string& output) {
        // mFileOutStream.close();
        // LOG << "Open output file: " << output << std::endl;
        // mFileOutStream.open(output.c_str());
        if (ofptr != NULL) fclose(ofptr);
        LOG << "Open output file: " << output << std::endl;
        ofptr = fopen(output.c_str(), "w");
        return ASZ_SUCC;
    }

    static int Close() {
        // mFileInStream.close();
        // mFileOutStream.close();
        if (ifptr != NULL) fclose(ifptr);
        if (ofptr != NULL) fclose(ofptr);
        return ASZ_SUCC;
    }

    static bool IsReachEoF() {
    	char c;
    	if (fscanf(ifptr, "%c", &c) == EOF)
    		return true;
    	fseek(ifptr, -1, SEEK_CUR);
    	return false;
        // return mFileInStream.eof();
    }

    static inline char ReadOneChar() {
        char c;
        // mFileInStream >> c;
        fscanf(ifptr, "%c", &c);
        return c;
    }

    static inline int ReadOneInteger() {
        int x = 0;
        // mFileInStream >> x;
        // mFileInStream.ignore(1, '\n');
        fscanf(ifptr, "%d%*c", &x);
        return x;
    }

    static inline void WriteOneString(const std::string& str) {
        // mFileOutStream << str;
        fprintf(ofptr, "%s", str.c_str());
    }

    static inline void WriteOneChar(char c) {
        // mFileOutStream << c;
        fprintf(ofptr, "%c", c);
    }

    static inline void WriteOneInterger(int x) {
        if (x == 0) WriteOneChar('0');
        else {
            if (x >= 10) {
                WriteOneInterger(x / 10);
            }
            WriteOneChar('0' + x % 10);
        }
    }

private:
    // static std::ifstream mFileInStream;
    // static std::ofstream mFileOutStream;
    static FILE* ifptr;
    static FILE* ofptr;
};

FILE* DataIOHelper::ifptr;
FILE* DataIOHelper::ofptr;

// std::ifstream DataIOHelper::mFileInStream;
// std::ofstream DataIOHelper::mFileOutStream;
#endif /* _DATA_IO_HELPER_H_ */
