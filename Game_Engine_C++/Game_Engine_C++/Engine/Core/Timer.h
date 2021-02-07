#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

constexpr float MILLI_TO_SEC = 1000.0f; //converts milliseconds to seconds

class Timer
{
public:
	Timer(const Timer&) = delete; //ensure that timer cannot be copied
	Timer(Timer&&) = delete; //ensure that timer cannot be copied
	Timer& operator=(const Timer&) = delete; //ensure that timer cannot be copied
	Timer& operator=(Timer&&) = delete; //ensure that timer cannot be copied

	Timer();
	~Timer();

	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTickMilli() const;
	float GetCurrentTickSec() const;

private:
	unsigned int prevTicks;
	unsigned int currentTicks; 
};

#endif

