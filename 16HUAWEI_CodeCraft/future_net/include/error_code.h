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
#define ASZ_SOLUTION_CHECKER_NO_EDGE_ERROR -2000
#define ASZ_SOLUTION_CHECKER_NO_EDGE_WARNING 2000
#define ASZ_SOLUTION_CHECKER_INVALID_START_POINT_ERROR -2001
#define ASZ_SOLUTION_CHECKER_INVALID_START_POINT_WARNING 2001
#define ASZ_SOLUTION_CHECKER_INVALID_END_POINT_ERROR -2002
#define ASZ_SOLUTION_CHECKER_INVALID_END_POINT_WARNING 2002
#define ASZ_SOLUTION_CHECKER_PATH_NOT_CONNECTED_ERROR -2003
#define ASZ_SOLUTION_CHECKER_PATH_NOT_CONNECTED_WARNING 2003
#define ASZ_SOLUTION_CHECKER_NOT_COVER_ALL_KEY_POINTS_ERROR -2004
#define ASZ_SOLUTION_CHECKER_NOT_COVER_ALL_KEY_POINTS_WARNING 2004
#define ASZ_SOLUTION_CHECKER_REPEAT_NODES_ERROR -2005
#define ASZ_SOLUTION_CHECKER_REPEAT_NODES_WARNING 2005

//[3000-4000) data generator
#define ASZ_DATA_GENERATOR_PARAMETER_MISSING_ERROR -3000
#define ASZ_DATA_GENERATOR_PARAMETER_MISSING_WARNING 3000
#define ASZ_DATA_GENERATOR_LACK_OF_EDGE_ERROR -3001
#define ASZ_DATA_GENERATOR_LACK_OF_EDGE_WARNING 3001
#define ASZ_DATA_GENERATOR_LACK_OF_NODE_ERROR -3002
#define ASZ_DATA_GENERATOR_LACK_OF_NODE_WARNING 3002

#define STRINGIFY(x) #x
#define CHECK_RTN_LOGE(x) if(x == ASZ_SUCC); else {std::cerr << "[" << __FILE__ << "] Line: " << __LINE__ << ": return error code " << x << " " << PRINTREADABLEINFO(x) << std::endl; return x;}
#define CHECK_RTN_LOGW(x) if(x == ASZ_SUCC); else {std::cerr << "[" << __FILE__ << "] Line: " << __LINE__ << ": return warning code " << x << " " << PRINTREADABLEINFO(x) << std::endl;} 

static inline std::string PRINTREADABLEINFO(int x) {
    switch (x) {
    //Error
    case ASZ_DEVIDE_BY_ZERO_ERROR:
        return STRINGIFY(ASZ_DEVIDE_BY_ZERO_ERROR);
    case ASZ_NULL_POINTER_ERROR:
        return STRINGIFY(ASZ_NULL_POINTER_ERROR);
    case ASZ_NO_TIME_STAMP_SET_ERROR:
        return STRINGIFY(ASZ_NO_TIME_STAMP_SET_ERROR);
    case ASZ_TIME_NO_MONITOR_INCIDENT_ERROR:
        return STRINGIFY(ASZ_TIME_NO_MONITOR_INCIDENT_ERROR);
    case ASZ_SOLUTION_CHECKER_NO_EDGE_ERROR:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_NO_EDGE_ERROR);
    case ASZ_SOLUTION_CHECKER_INVALID_START_POINT_ERROR:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_INVALID_START_POINT_ERROR);
    case ASZ_SOLUTION_CHECKER_INVALID_END_POINT_ERROR:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_INVALID_END_POINT_ERROR);
    case ASZ_SOLUTION_CHECKER_NOT_COVER_ALL_KEY_POINTS_ERROR:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_NOT_COVER_ALL_KEY_POINTS_ERROR);
    case ASZ_SOLUTION_CHECKER_REPEAT_NODES_ERROR:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_REPEAT_NODES_ERROR);
    case ASZ_DATA_GENERATOR_PARAMETER_MISSING_ERROR:
        return STRINGIFY(ASZ_DATA_GENERATOR_PARAMETER_MISSING_ERROR);
    case ASZ_DATA_GENERATOR_LACK_OF_EDGE_ERROR:
        return STRINGIFY(ASZ_DATA_GENERATOR_LACK_OF_EDGE_ERROR);
    case ASZ_DATA_GENERATOR_LACK_OF_NODE_ERROR:
        return STRINGIFY(ASZ_DATA_GENERATOR_LACK_OF_NODE_ERROR);

    //Warning
    case ASZ_DEVIDE_BY_ZERO_WARNING:
        return STRINGIFY(ASZ_DEVIDE_BY_ZERO_WARNING);
    case ASZ_NO_TIME_STAMP_SET_WARNING:
        return STRINGIFY(ASZ_NO_TIME_STAMP_SET_WARNING);
    case ASZ_TIME_NO_MONITOR_INCIDENT_WARNING:
        return STRINGIFY(ASZ_TIME_NO_MONITOR_INCIDENT_WARNING);
    case ASZ_NULL_POINTER_WARNING:
        return STRINGIFY(ASZ_NULL_POINTER_WARNING);
    case ASZ_SOLUTION_CHECKER_NO_EDGE_WARNING:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_NO_EDGE_WARNING);
    case ASZ_SOLUTION_CHECKER_INVALID_START_POINT_WARNING:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_INVALID_START_POINT_WARNING);
    case ASZ_SOLUTION_CHECKER_INVALID_END_POINT_WARNING:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_INVALID_END_POINT_WARNING);
    case ASZ_SOLUTION_CHECKER_NOT_COVER_ALL_KEY_POINTS_WARNING:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_NOT_COVER_ALL_KEY_POINTS_WARNING);
    case ASZ_SOLUTION_CHECKER_REPEAT_NODES_WARNING:
        return STRINGIFY(ASZ_SOLUTION_CHECKER_REPEAT_NODES_WARNING);
    case ASZ_DATA_GENERATOR_PARAMETER_MISSING_WARNING:
        return STRINGIFY(ASZ_DATA_GENERATOR_PARAMETER_MISSING_WARNING);
    case ASZ_DATA_GENERATOR_LACK_OF_EDGE_WARNING:
        return STRINGIFY(ASZ_DATA_GENERATOR_LACK_OF_EDGE_WARNING);
    case ASZ_DATA_GENERATOR_LACK_OF_NODE_WARNING:
        return STRINGIFY(ASZ_DATA_GENERATOR_LACK_OF_NODE_WARNING);
    }
    return "UNKNOWN_ERROR";
}

#endif /* _ERROR_CODE_H_ */