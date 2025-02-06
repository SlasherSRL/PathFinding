#pragma once
#include <chrono>
class Timer
{
public:
	

	std::chrono::time_point<std::chrono::system_clock> clockEnd;
	std::chrono::time_point<std::chrono::system_clock> clockStart;

	float time;
	bool timerStarted;
	bool timerStopped;
	Timer();
	void StartTime();
	void StopTime();

};

