#include "Timer.h"
void Timer::StartTime()
{
	

	clockStart = std::chrono::system_clock::now();
	clockEnd = clockStart;
	timerStarted = true;
}
void Timer::StopTime() 
{
	clockEnd= std::chrono::system_clock::now();
	time = std::chrono::duration_cast<std::chrono::microseconds>(clockEnd - clockStart).count();

	timerStopped = true;
}
Timer::Timer()
{
	time = 0.0f;
	timerStarted = false;
	timerStopped = false;
}