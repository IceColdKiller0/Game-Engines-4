#include "Timer.h"

Timer::Timer()
{
	//sets default values for the ticks

	prevTicks = 0;
	currentTicks = 0;
}

Timer::~Timer()
{
}

void Timer::Start()
{
	//set previous and current tick value to be equal to the sdl tick function

	prevTicks = currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks()
{
	//update ticks per frame, update previous before current

	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const
{
	//get the time from the previous frame to current frame
	//specifically in seconds
	return (currentTicks - prevTicks) / MILLI_TO_SEC;
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	//ensures that the engine is always running at 60fps

	unsigned int milliSecPerFrame = MILLI_TO_SEC / fps_;
	if (milliSecPerFrame == 0)
	{
		return 0;
	}
	unsigned int sleepTime = milliSecPerFrame - (SDL_GetTicks() - currentTicks);
	if (sleepTime > milliSecPerFrame)
	{
		return milliSecPerFrame;
	}

	return sleepTime;
}

float Timer::GetCurrentTickMilli() const
{
	return static_cast<float>(currentTicks);
}

float Timer::GetCurrentTickSec() const
{
	return currentTicks / MILLI_TO_SEC;;
}
