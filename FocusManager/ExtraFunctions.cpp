#include "ExtraFunctions.h"

std::string getCurrentTime() {
    auto now{ std::chrono::system_clock::now() };
    std::time_t currentTime{ std::chrono::system_clock::to_time_t(now) };
    std::tm localTime{};

    localtime_s(&localTime, &currentTime);
    
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%d.%m.%Y|%H:%M:%S");

    return oss.str();
}