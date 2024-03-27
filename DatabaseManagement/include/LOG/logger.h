#ifndef LOG
#define LOG

#include<memory>
#include "Log.h"
#include <fstream>
using logging::Log;
namespace logging {


    inline auto mylogger = std::make_shared<Log>("Deep");

    inline std::shared_ptr<Log> default_logger() {
        return mylogger;
    }

    inline void setDefaultLogger(std::shared_ptr<Log> l) {
        mylogger = l;
    }

    inline void flushBuffer(std::string fn, std::string buffer) {
        std::ofstream of(fn, std::ios::app);
        of << buffer;
    }

    template<typename... T>
    void Log::log(Log::Level l, T... arg) {
        if (m_LogLevel >= l) {
            std::string tmp = cacheTime();
        /*    std::cout << cacheTime() << " ";
            std::cout << "[" << Log::logger << "]" << " ";*/
            tmp.append(" [");
            tmp.append(std::string(Log::logger));
            tmp.append("] ");
            //std::cout << default_logger()->getlevelwithColor(l) << " ";
            tmp.append((default_logger()->getlevel(l)));
            tmp.append(" ");
            //Log::print(arg...);
            if (this->fileDump) {
                this->logBuffer.append(tmp);
                default_logger()->setupBuffer(arg...);
                this->m_cnt++;
                logBuffer.append("\n");
                if (this->m_cnt == 5) {
                    flushBuffer(Log::fileName, logBuffer);
                    this->logBuffer = "";
                    this->m_cnt = 0;
                }
            }
        }
    }

    inline Log::~Log() {
        if (this->logBuffer.length() > 0)
            flushBuffer(fileName, logBuffer);

        this->logBuffer = "";
    }

    template<typename m, typename... arg>
    void Warn(const m message, arg... others) {
        default_logger()->Log::log(Log::Level::LevelWarning, message, others...);
    }

    template<typename m, typename... arg>
    void Error(const m message, arg... others) {
        default_logger()->Log::log(Log::Level::LevelError, message, others...);
    }

    template<typename m, typename... arg>
    void Info(const m message, arg... others) {
        default_logger()->Log::log(Log::Level::LevelInfo, message, others...);
    }
}
#endif