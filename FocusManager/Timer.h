#pragma once

#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>


#include "JsonSerializer.h"
#include "Error.h"

class JsonSerializer;

using namespace std::chrono;
using json = nlohmann::json;
using doubleMinutes = duration<double, std::ratio<60>>;

enum class State : unsigned int {
	Work,
	minRelax,
	maxRelax
};


class Timer {
public:
	friend void to_json(json& j, const Timer& timer);
	friend void from_json(const json& j, Timer& timer);

	Timer() = default;
	~Timer() = default;

	void updateTimer();
	bool updateState();

	void setState(const State state);


	State getState();
	doubleMinutes getCurrentTime();
	size_t getCounter();

	void test();
	void setPreviousTime(const steady_clock::time_point& previous);

private:
	steady_clock::time_point mPrevious{};
	steady_clock::time_point mCurrent{};
	duration<double> mCounter{};

	doubleMinutes mTimeToWork{ 25.0 };
	doubleMinutes mMinTimeToRelax{ 5.0 };
	doubleMinutes mMaxTimeToRelax{ 15.0 };

	std::array<doubleMinutes*, 3> mTime{
		&mTimeToWork,
		&mMinTimeToRelax,
		&mMaxTimeToRelax
	};

	State mState{};
	size_t mCycleCounterOfWork{};
};

std::string getCurrentTimeToString();

void to_json(json& j, const Timer& timer);
void from_json(const json& j, Timer& timer);

Timer initTimer(const JsonSerializer& jsonSerializer);
void saveTimer(JsonSerializer& jsonSerializer, const Timer& timer);