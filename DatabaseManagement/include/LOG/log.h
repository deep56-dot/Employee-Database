#ifndef _LOG_
#define _LOG_

#include<iostream>
#include<string>
#include<chrono>
#include<ctime>



namespace logging {
    class Log {
    public:
        enum class Level {
            LevelCritical = 0, LevelError, LevelWarning, LevelInfo, LevelDebug
        };

        Log(std::string name, std::string fn = "defaultlog.txt") : m_LogLevel{ Level::LevelInfo }, logger{ name }, fileName{ fn } {}

        Log(std::string name, Level level, std::string fn = "defaultlog.txt") : m_LogLevel{ level }, logger{ name }, fileName{ fn } {}

        ~Log();

        void SetLogLevel(Level level) {
            m_LogLevel = level;
        }

        template<typename... T>
        void log(Level l, T... arg);

        inline static std::string cacheTime() {
            auto now = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(now); // to_time_t is a method for converting chrono::time in to time_t(ctime)

            //Now time_t is in non readable formate so we have to conver it into redable formate 
            std::tm tmLocal; // tm is a structure which stores the values in its variables 
            localtime_s(&tmLocal, &time); //now we store time_t into tm

            char buffer[20];
            std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &tmLocal); //formatting tm and stores it into buffer

            return std::string(buffer);
        }

        void setupBuffer() {}
        template<typename m, typename... T>
        void setupBuffer(m s1, T... others) {
            logBuffer.append(s1);        
            logBuffer.append(" ");
            setupBuffer(others...); 
        }
        void setFileDump(bool val) {
            fileDump = val;
        }
    private:
         std::string getlevelwithColor(Level l) const {
            switch (l) {
            case Level::LevelError:
                return "\033[31m""[Error]""\033[0m";

            case Level::LevelWarning:
                return "\033[33m""[Warning]""\033[0m";

            case Level::LevelInfo:
                return "\033[32m""[Info]""\033[0m";

            case Level::LevelDebug:
                return "Debug";

            case Level::LevelCritical:
                return "\033[41;37m""[Critical]""\033[0m";
            }
            return "";
        }

        std::string getlevel(Level l) const {
            switch (l) {
            case Level::LevelError:
                return "[Error]";

            case Level::LevelWarning:
                return "[Warning]";

            case Level::LevelInfo:
                return "[Info]";

            case Level::LevelDebug:
                return "Debug";

            case Level::LevelCritical:
                return "[Critical]";
            }
            return "";
        }


        std::string logBuffer;
        Level m_LogLevel;
        int m_cnt{ 0 };
        bool fileDump = true;
        std::string logger;
        std::string fileName;
        void print() const {
            std::cout << "\n";
        }

        template<typename m, typename... arg>
        void print(const m message, arg... others) const {
            std::cout << message << " ";
            print(others...);
        }

    };
}



#endif