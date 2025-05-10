#include "pch.h"
#include "logging.h"
#include <string>
#include <fstream>

void Logging::del() {
    const std::string logFilePath = "Plugins/Logs/tygmem2.log";
    std::remove(logFilePath.c_str());
}

void Logging::log(const std::string& message) {
    const std::string logFilePath = "Plugins/Logs/tygmem2.log";
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}