#include "Logger.h"
#include <time.h>
#include <iostream>

const std::string Logger::m_LogFileName = "Log.txt";
Logger* Logger::m_ptrLogger = nullptr;
std::ofstream Logger::m_Logfile;

void Logger::Log(const std::string& sMessage)
{
    if (m_Logfile.is_open())
    {
        m_Logfile << getCurrentDateTime() << ":\t";
        m_Logfile << sMessage << "\n";
    }
    else
    {
        std::cout << "Error opening log file: " << m_LogFileName << std::endl;
    }
}

Logger* Logger::GetLogger()
{
    if (m_ptrLogger == nullptr)
    {
        m_ptrLogger = new Logger();
        m_Logfile.open(m_LogFileName.c_str(), std::ios::out | std::ios::app);
    }
    return m_ptrLogger;
}

const std::string Logger::getCurrentDateTime()
{
    time_t now = time(nullptr);
    struct tm tstruct;
    char buf[80];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}