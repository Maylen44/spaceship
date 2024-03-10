#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

#define LOGGER Logger::getLogger()

class Logger
{
public:
    void Log(const std::string& sMessage);
    static Logger* getLogger();

private:
    Logger() {};
    const std::string getCurrentDateTime();

    static const std::string m_LogFileName;
    static Logger* m_ptrLogger;
    static std::ofstream m_Logfile;
};
#endif //LOGGER_H