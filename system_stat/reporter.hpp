#pragma once

// TODO: inject parser - XML, JSON, etc...

#include <string>
#include <sstream>
#include <fstream>
#include <sys/sysinfo.h>
#include <thread>

#include "connection_types.hpp"

class Reporter
{
private:
    std::__cxx11::string report;

    std::__cxx11::string getSysInfo();
    std::__cxx11::string getProcLoadAvg();

    template<typename T>
    std::__cxx11::string buildCPULine(std::__cxx11::string descrp, T _1min, T _5min, T _15min);

public:
    explicit Reporter();

    void initReport(const ConnType& type);
    void setHTMLHeaders();
    void append(const std::__cxx11::string& str);

    const std::__cxx11::string& getReport() const;
};
