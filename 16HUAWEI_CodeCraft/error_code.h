/*************************************************************************
	> File Name: error_code.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 03:01:24 AM CST
*************************************************************************/

#ifndef _ERROR_CODE_H_
#define _ERROR_CODE_H_

#include <iostream>
#include <iomanip>
#include <cstdio>

#define ASZ_SUCC 0

//[0-1000) common error
#define ASZ_DEVIDE_BY_ZERO_ERROR -1
#define ASZ_DEVIDE_BY_ZERO_WARNING 1
#define ASZ_NULL_POINTER_ERROR -2
#define ASZ_NULL_POINTER_WARNING 2

//[1000-2000) time utility
#define ASZ_NO_TIME_STAMP_SET_ERROR -1000
#define ASZ_NO_TIME_STAMP_SET_WARNING 1000
#define ASZ_TIME_NO_MONITOR_INCIDENT_ERROR -1001
#define ASZ_TIME_NO_MONITOR_INCIDENT_WARNING 1001

//[2000-3000) solution checker
#define 

#define STRINGIFY(x) #x
#define CHECK_RTN_LOGE(x) if(x == ASZ_SUCC); else {std::cerr << "[" << __FILE__ << "] Line: " << __LINE__ << ": return error code " << x << " " << PRINTREADABLEINFO(x) << std::endl; return x;}
#define CHECK_RTN_LOGW(x) if(x == ASZ_SUCC); else {std::cerr << "[" << __FILE__ << "] Line: " << __LINE__ << ": return warning code " << x << " " << PRINTREADABLEINFO(x) << std::endl;} 

static inline std::string PRINTREADABLEINFO(int x) {
    switch (x) {
    //Error
    case ASZ_DEVIDE_BY_ZERO_ERROR:
        return STRINGIFY(ASZ_DEVIDE_BY_ZERO_ERROR);
    case ASZ_NO_TIME_STAMP_SET_ERROR:
        return STRINGIFY(ASZ_NO_TIME_STAMP_SET_ERROR);
    case ASZ_TIME_NO_MONITOR_INCIDENT_ERROR:
        return STRINGIFY(ASZ_TIME_NO_MONITOR_INCIDENT_ERROR);
    case ASZ_NULL_POINTER_ERROR:
        return STRINGIFY(ASZ_NULL_POINTER_ERROR);





    //Warning
    case ASZ_DEVIDE_BY_ZERO_WARNING:
        return STRINGIFY(ASZ_DEVIDE_BY_ZERO_WARNING);
    case ASZ_NO_TIME_STAMP_SET_WARNING:
        return STRINGIFY(ASZ_NO_TIME_STAMP_SET_WARNING);
    case ASZ_TIME_NO_MONITOR_INCIDENT_WARNING:
        return STRINGIFY(ASZ_TIME_NO_MONITOR_INCIDENT_WARNING);
    case ASZ_NULL_POINTER_WARNING:
        return STRINGIFY(ASZ_NULL_POINTER_WARNING);
    }
    return "UNKNOWN_ERROR";
}

#endif /* _ERROR_CODE_H_ */
