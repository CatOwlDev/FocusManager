#pragma once

#include <chrono>
#include <string>
#include <string_view>
#include <format>

#include "JsonSerializer.h"
#include "Error.h"
#include "MyTransformers.h"

class JsonSerializer;

using namespace std::chrono;
using json = nlohmann::json;

constexpr int maxSecondsInMinute{ 60 };
constexpr int maxSecondsInHour{ 3600 };
constexpr long long maxNumberOfSecondsUserInputsForValue{ maxNumberOfMinutesUserInputsForValue * maxSecondsInMinute };

class Timer {
public:
	friend void to_json(json& j, const Timer& timer);
	friend void from_json(const json& j, Timer& timer);

	Timer() = default;
	~Timer() = default;

	void update();

	void updateTimer();
	void updateState();

	void setState(const State state);
	void setTimeToWork(const seconds& seconds);
	void setMinTimeToRelax(const seconds& seconds);
	void setMaxTimeToRelax(const seconds& seconds);
	
	void start();
	void stop();
	void reset();
	void skip();
	void recordPrevTime();

	State getState() const;
	seconds getCurrentTime() const;
	seconds getTimeToWork() const;
	seconds getMinTimeToRelax() const;
	seconds getMaxTimeToRelax() const;
	bool isGo() const;

	seconds showCountdown() const;

private:
	void goToNextState();

private:
	steady_clock::time_point mPrevious{};
	steady_clock::time_point mCurrent{};
	duration<double> mCounter{ 0.0 };

	seconds mTimeToWork{ 25 * maxSecondsInMinute };
	seconds mMinTimeToRelax{ 5 * maxSecondsInMinute };
	seconds mMaxTimeToRelax{ 15 * maxSecondsInMinute };

	State mState{ State::Work };
	size_t mCycleCounterOfWork{};

	bool mGo{};
};

std::string getCurrentDateAndTimeToString();

void to_json(json& j, const Timer& timer);
void from_json(const json& j, Timer& timer);

Timer initTimer(const JsonSerializer& jsonSerializer);
void saveTimer(JsonSerializer& jsonSerializer, const Timer& timer);

std::string countdownToASCII(const seconds seconds);