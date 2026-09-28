#include "Timer.h"

void Timer::update() {
    if (mGo) {
        updateTimer();
        updateState();
    }
}

void Timer::updateTimer() {
    mCurrent = steady_clock::now();
    mCounter += (mCurrent - mPrevious);
    mPrevious = mCurrent;
}
void Timer::updateState() {
    seconds currentSeconds{ this->getCurrentTime() };
    if (mCounter >= currentSeconds) 
        skip();
}

void Timer::setState(const State state) { mState = state; }
void Timer::start() { 
    recordPrevTime();
    mGo = true; 
}
void Timer::stop() { mGo = false; }
void Timer::skip() {
    reset();
    goToNextState();
}
void Timer::reset() {
    stop();
    mCounter = duration<double>::zero();
}

void Timer::recordPrevTime() { mPrevious = steady_clock::now(); }

void Timer::goToNextState() {
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
}

void Timer::setTimeToWork(const seconds& timeToWork) { 
    if (timeToWork.count() >= maxNumberOfSecondsUserInputsForValue)
    {
        mTimeToWork = seconds(maxNumberOfSecondsUserInputsForValue);
        return;
    }
    mTimeToWork = timeToWork; 
}
void Timer::setMinTimeToRelax(const seconds& minTimeToRelax) { 
    if (minTimeToRelax.count() >= maxNumberOfSecondsUserInputsForValue)
    {
        mMinTimeToRelax = seconds(maxNumberOfSecondsUserInputsForValue);
        return;
    }
    mMinTimeToRelax = minTimeToRelax; 
}
void Timer::setMaxTimeToRelax(const seconds& maxTimeToRelax) { 
    if (maxTimeToRelax.count() >= maxNumberOfSecondsUserInputsForValue)
    {
        mMaxTimeToRelax = seconds(maxNumberOfSecondsUserInputsForValue);
        return;
    }
    mMaxTimeToRelax = maxTimeToRelax; 
}

seconds Timer::showCountdown() const { return seconds{ static_cast<long long>(getCurrentTime().count() - static_cast<long long>(mCounter.count())) }; }

seconds Timer::getCurrentTime() const {
    switch (mState) {
    case State::Work: return mTimeToWork;
    case State::minRelax: return mMinTimeToRelax;
    case State::maxRelax: return mMaxTimeToRelax;
    }
    return mTimeToWork; // DEFAULT
}

State Timer::getState() const { return mState; }
seconds Timer::getTimeToWork() const { return mTimeToWork; }
seconds Timer::getMinTimeToRelax() const { return mMinTimeToRelax; }
seconds Timer::getMaxTimeToRelax() const { return mMaxTimeToRelax; }

bool Timer::isGo() const { return mGo; }

// AI
std::string getCurrentDateAndTimeToString() {
    system_clock::time_point now = std::chrono::system_clock::now();

    return std::format("{:%d.%m.%Y|%H:%M:%S}", std::chrono::zoned_time{ std::chrono::current_zone(), now });
}

void to_json(json& j, const Timer& timer) {
    long long minutesTimeToWork{ timer.mTimeToWork.count() / maxSecondsInMinute };
    long long minutesMinTimeTiRelax{ timer.mMinTimeToRelax.count() / maxSecondsInMinute };
    long long minutesMaxTimeToRelax{ timer.mMaxTimeToRelax.count() / maxSecondsInMinute };
    j = json{
        { 
            "Timer", 
            { 
                { "TimeToWork", minutesTimeToWork },
                { "MinTimeToRelax", minutesMinTimeTiRelax },
                { "MaxTimeToRelax", minutesMaxTimeToRelax }
            }
        }
    };
}
void from_json(const json& j, Timer& timer) {
    try {
        int minutesTimeToWork{};
        int minutesMinTimeTiRelax{};
        int minutesMaxTimeToRelax{};

        j.at("TimeToWork").get_to(minutesTimeToWork);
        timer.setTimeToWork(seconds(static_cast<long long>(minutesTimeToWork * maxSecondsInMinute)));
        j.at("MinTimeToRelax").get_to(minutesMinTimeTiRelax);
        timer.setMinTimeToRelax(seconds(static_cast<long long>(minutesMinTimeTiRelax * maxSecondsInMinute)));
        j.at("MaxTimeToRelax").get_to(minutesMaxTimeToRelax);
        timer.setMaxTimeToRelax(seconds(static_cast<long long>(minutesMaxTimeToRelax * maxSecondsInMinute)));
    }
    catch (const json::exception& e) {
        Error error{
            getCurrentDateAndTimeToString(),
            "file: Timer.cpp, func: from_json",
            e.what()
        };
        writeErrorReport(error);
    }
}

Timer initTimer(const JsonSerializer& jsonSerializer) {
    Timer timer{};
    const json& data{ jsonSerializer.getData() };

    if (!data.empty()) {
        try {
            data.at("Timer").get_to(timer);
        }
        catch (const json::exception& e) {
            Error error{
                getCurrentDateAndTimeToString(),
                "file: Timer.cpp, func: initTimer",
                e.what()
            };
            writeErrorReport(error);
            return Timer{};
        }
    }

    return timer;
}
void saveTimer(JsonSerializer& jsonSerializer, const Timer& timer) {
    json j{};
    to_json(j, timer);
    jsonSerializer.setData(j);
}

// AI
std::string countdownToASCII(std::chrono::seconds countdownSeconds) {
    const hours hrs = floor<hours>(countdownSeconds);
    countdownSeconds -= hrs;
    const minutes mins = floor<minutes>(countdownSeconds);
    countdownSeconds -= mins;
    const seconds secs = countdownSeconds;

    const int h = hrs.count();
    const int m = mins.count();
    const long long s = secs.count();

    const std::array<size_t, 8> digits = {
        static_cast<size_t>(h / 10),
        static_cast<size_t>(h % 10),
        10,
        static_cast<size_t>(m / 10),
        static_cast<size_t>(m % 10),
        10,
        static_cast<size_t>(s / 10),
        static_cast<size_t>(s % 10)
    };

    static const std::array<std::array<std::string, 5>, 11> numbers{
        std::array<std::string, 5>{
            " ███ ",
            "█  ██",
            "█ █ █",
            "██  █",
            " ███ "
        },
        std::array<std::string, 5>{
            "  █  ",
            " ██  ",
            "  █  ",
            "  █  ",
            " ███ "
        },
        std::array<std::string, 5>{
            " ███ ",
            "   █ ",
            " ███ ",
            " █   ",
            " ███ "
        },
        std::array<std::string, 5>{
            " ███ ",
            "   █ ",
            " ███ ",
            "   █ ",
            " ███ "
        },
        std::array<std::string, 5>{
            " █ █ ",
            " █ █ ",
            " ███ ",
            "   █ ",
            "   █ "
        },
        std::array<std::string, 5>{
            " ███ ",
            " █   ",
            " ███ ",
            "   █ ",
            " ███ "
        },
        std::array<std::string, 5>{
            " ███ ",
            " █   ",
            " ███ ",
            " █ █ ",
            " ███ "
        },
        std::array<std::string, 5>{
            " ███ ",
            " █ █ ",
            "   █ ",
            "   █ ",
            "   █ "
        },
        std::array<std::string, 5>{
            " ███ ",
            " █ █ ",
            " ███ ",
            " █ █ ",
            " ███ "
        },
        std::array<std::string, 5>{
            " ███ ",
            " █ █ ",
            " ███ ",
            "   █ ",
            " ███ "
        },
        std::array<std::string, 5>{
            " ███ ",
            " ███ ",
            "     ",
            " ███ ",
            " ███ "
        }
    };

    std::string result;
    result.reserve(245);

    for (size_t line = 0; line < 5; ++line) {
        for (size_t idx = 0; idx < digits.size(); ++idx) {
            result += numbers[digits[idx]][line];
            if (idx + 1 < digits.size()) result += ' ';
        }
        result += '\n';
    }

    return result;
}