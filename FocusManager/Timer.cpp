#include "Timer.h"

void Timer::updateTimer() {
    mCurrent = steady_clock::now();
    mCounter += (mCurrent - mPrevious);
    mPrevious = mCurrent;
}
bool Timer::updateState() {
    doubleMinutes currentMinutes{ this->getCurrentTime() };
    if (mCounter >= currentMinutes) {
        mCounter -= currentMinutes;

        if (mState == State::Work) {
            if (mCycleCounterOfWork == 3) { 
                mState = State::maxRelax; 
                mCycleCounterOfWork = 0;
            }
            else { 
                mState = State::minRelax;
                ++mCycleCounterOfWork;
            }
        }
        else { mState = State::Work; }
        return true;
    }
    return false;
}

void Timer::setState(const State state) { mState = state; }
void Timer::setPreviousTime(const steady_clock::time_point& previous) { mPrevious = previous; }

State Timer::getState() { return mState; }
doubleMinutes Timer::getCurrentTime() { return *(mTime[static_cast<size_t>(mState)]); }
size_t Timer::getCounter() { return mCycleCounterOfWork; }

std::string getCurrentTimeToString() {
    auto now{ std::chrono::system_clock::now() };
    std::time_t currentTime{ std::chrono::system_clock::to_time_t(now) };
    std::tm localTime{};

    localtime_s(&localTime, &currentTime);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%d.%m.%Y|%H:%M:%S");

    return oss.str();
}

void to_json(json& j, const Timer& timer) {
    j = json{
        { 
            "Timer", 
            { 
                { "TimeToWork", timer.mTimeToWork.count() },
                { "MinTimeToRelax", timer.mMinTimeToRelax.count() },
                { "MaxTimeToRelax", timer.mMaxTimeToRelax.count() }
            }
        }
    };
}
void from_json(const json& j, Timer& timer) {
    double num{};
    try {
        j.at("TimeToWork").get_to(num);
        timer.mTimeToWork = doubleMinutes{ num };
        j.at("MinTimeToRelax").get_to(num);
        timer.mMinTimeToRelax = doubleMinutes{ num };
        j.at("MaxTimeToRelax").get_to(num);
        timer.mMaxTimeToRelax = doubleMinutes{ num };
    }
    catch (const json::exception& e) {
        Error error{
            getCurrentTimeToString(),
            "file: Timer.cpp, func: from_json",
            e.what()
        };
        writeErrorReport(error);
    }
}

Timer initTimer(const JsonSerializer& jsonSerializer) {
    Timer timer{};
    const json& data{ jsonSerializer.getData() };

    try {
        data.at("Timer").get_to(timer);
    }
    catch (const json::exception& e) {
        Error error{
            getCurrentTimeToString(),
            "class: Timer, func: initTimer",
            e.what()
        };
        writeErrorReport(error);
    }

    return timer;
}
void saveTimer(JsonSerializer& jsonSerializer, const Timer& timer) {
    json j{};
    to_json(j, timer);
    jsonSerializer.setData(j);
}