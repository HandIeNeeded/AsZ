/*************************************************************************
	> File Name: time_utility.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 02:38:29 AM CST
*************************************************************************/

#ifndef _TIME_UTILITY_H_
#define _TIME_UTILITY_H_
#include <ctime>
#include <map>
#include <string>
#include <iostream>
#include "error_code.h"

class TimeHelper {
public:
    TimeHelper();
    ~TimeHelper();

    static inline int Init();

    static inline void CumulateStart(const std::string& incidentName);

    static inline void CumulateStop(const std::string& incidentName);

    static inline void SetUpTimeStamp(const std::string& timeStamp);

    static inline int GetTimeSinceStamp(const std::string& timeStamp, std::uint64_t& time);

    static inline int GetTimeSinceStampInSec(const std::string& timeStamp, double& time);

    static inline int ShowAllMonitorIncidentsInfo();

private:
    static std::map<std::string, std::uint64_t> mMonitorIncidentsStart;
    static std::map<std::string, std::uint64_t> mMonitorIncidentsStop;
    static std::map<std::string, std::uint64_t> mTimeStamps;
};

//without this, undefined reference
std::map<std::string, std::uint64_t> TimeHelper::mMonitorIncidentsStart;
std::map<std::string, std::uint64_t> TimeHelper::mMonitorIncidentsStop;
std::map<std::string, std::uint64_t> TimeHelper::mTimeStamps;

int TimeHelper::Init() {
    mMonitorIncidentsStart.clear();
    mMonitorIncidentsStop.clear();
    mTimeStamps.clear();
    return ASZ_SUCC;
}

int TimeHelper::ShowAllMonitorIncidentsInfo() {
    if (mMonitorIncidentsStart.size() == 0) {
        return ASZ_TIME_NO_MONITOR_INCIDENT_WARNING;
    }
    for (auto &incident: mMonitorIncidentsStart) {
        std::string name;
        std::uint64_t stampStart, stampEnd;
        std::tie(name, stampStart) = incident;
        if (!mMonitorIncidentsStop.count(name)) continue;
        stampEnd = mMonitorIncidentsStop[name];
        LOG << "Time Monitor: [" << name << "] use " << std::fixed << std::setprecision(6) << 1.0 * (stampEnd - stampStart) / CLOCKS_PER_SEC << "sec." << std::endl;
    }
    return ASZ_SUCC;
}

void TimeHelper::SetUpTimeStamp(const std::string& timeStamp) {
    mTimeStamps[timeStamp] = clock();
}

void TimeHelper::CumulateStart(const std::string& incidentName) {
    mMonitorIncidentsStart[incidentName] = clock();
}

void TimeHelper::CumulateStop(const std::string& incidentName) {
    mMonitorIncidentsStop[incidentName] = clock();
}

int TimeHelper::GetTimeSinceStamp(const std::string& timeStamp, std::uint64_t& time) {
    if (mTimeStamps.count(timeStamp)) {
        time = clock() - mTimeStamps[timeStamp];
        return ASZ_SUCC;
    }
    else {
        return ASZ_NO_TIME_STAMP_SET_ERROR;
    }
}

int TimeHelper::GetTimeSinceStampInSec(const std::string& timeStamp, double& time) {
    std::uint64_t cost = 0;
    int rtn = GetTimeSinceStamp(timeStamp, cost);
    CHECK_RTN_LOGE(rtn);
    time = 1.0 * cost / CLOCKS_PER_SEC;
    return ASZ_SUCC;
}

#endif /* _TIME_UTILITY_H_ */
