#include "reporter.hpp"


Reporter::Reporter()
{
}

void Reporter::initReport(const ConnType& type)
{
    report = "";

    if (ConnType::client == type)
    {
        report = "Localhost:";
        this->append("<br>");
    }

    this->append(getSysInfo());
    this->append("<br>");
    this->append(getProcLoadAvg());
}

void Reporter::setHTMLHeaders()
{
    std::__cxx11::string headers = "HTTP/1.1 200 OK\n"
                          "Content-Type: text/html\n"
                          "Content-Length: " + std::to_string(report.length()) + "\n"
                          "Connection: close\n\n";

    report = headers + report;
}

void Reporter::append(const std::__cxx11::string &str)
{
    report += str;
}

const std::__cxx11::string& Reporter::getReport() const
{
    return report;
}

std::__cxx11::string Reporter::getSysInfo()
{
    struct sysinfo sysInfo;
    std::__cxx11::string str;

    if(0 == sysinfo(&sysInfo))
    {
        auto thCount = std::thread::hardware_concurrency();
        double _1min, _5min, _15min;

        _1min = (sysInfo.loads[0]/1000.0) / thCount;
        _5min = (sysInfo.loads[1]/1000.0) / thCount;
        _15min = (sysInfo.loads[2]/1000.0) / thCount;

        str = buildCPULine("Sys Info", _1min, _5min, _15min);
    }
    else
    {
        // TODO: log error
        str = "Error: sysinfo(&sysInfo)";
    }

    return str;
}

std::__cxx11::string Reporter::getProcLoadAvg()
{
    std::__cxx11::string procLoadavg ("/proc/loadavg"), line, str;
    std::ifstream file (procLoadavg);

    if (file.is_open())
    {
        std::getline(file, line);
        file.close();

        std::istringstream iss (line);
        float _1min, _5min, _15min;

        iss >> _1min;
        iss >> _5min;
        iss >> _15min;

        str = buildCPULine("Proc LoadAvg", _1min, _5min, _15min);
    }
    else
    {
        // TODO: log error
        str = "Error: cannot open file " + procLoadavg;
    }

    return str;
}

template<typename T>
std::__cxx11::string Reporter::buildCPULine(std::__cxx11::string descrp, T _1min, T _5min, T _15min)
{
    std::stringstream ss;
    ss << descrp;
    ss << " data: ";
    ss << "1 min( " << _1min << "% ) ";
    ss << "5 min( " << _5min << "% ) ";
    ss << "15 min( " << _15min << "% )";

    return ss.str();
}
