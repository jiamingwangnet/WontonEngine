#include "include/WontonEngine/UpdateLimiter.h"
#include <SDL3/SDL.h>

unsigned int won::priv::UpdateLimiter::startTicks = 0;
float won::priv::UpdateLimiter::updateps = 0.0f;
float won::priv::UpdateLimiter::renderps = 0.0f;

void won::priv::UpdateLimiter::Begin()
{
	startTicks = SDL_GetTicks();
}

void won::priv::UpdateLimiter::End(float target)
{
	if (target == 0.0f) return;
	float frameTicks = (float)(SDL_GetTicks() - startTicks);
	if (1000.0f / target > frameTicks)
	{
		SDL_Delay(1000.0f / target - frameTicks);
	}
}

void won::priv::UpdateLimiter::CalcUpdatesPerSecond()
{
	static constexpr int SAMPLES = 10;
	static float buffer[SAMPLES];
	static int frame = 0;

	static float prevTicks = (float)SDL_GetTicks();

	float currentTicks = (float)SDL_GetTicks();

	float frameTime = currentTicks - prevTicks;
	buffer[frame % SAMPLES] = frameTime;

	prevTicks = currentTicks;
	frame++;

	int count = SAMPLES;
	if (frame < SAMPLES)
	{
		count = frame;
	}

	float average = 0.0f;
	for (int i = 0; i < count; i++)
	{
		average += buffer[i];
	}
	average /= (float)count;

	if (average > 0)
		updateps = 1000.0f / average;
	else
		updateps = 0.0f;
}

void won::priv::UpdateLimiter::CalcRendersPerSecond()
{
	static constexpr int SAMPLES = 10;
	static float buffer[SAMPLES];
	static int frame = 0;

	static float prevTicks = (float)SDL_GetTicks();

	float currentTicks = (float)SDL_GetTicks();

	float frameTime = currentTicks - prevTicks;
	buffer[frame % SAMPLES] = frameTime;

	prevTicks = currentTicks;
	frame++;

	int count = SAMPLES;
	if (frame < SAMPLES)
	{
		count = frame;
	}

	float average = 0.0f;
	for (int i = 0; i < count; i++)
	{
		average += buffer[i];
	}
	average /= (float)count;

	if (average > 0)
		renderps = 1000.0f / average;
	else
		renderps = 0.0f;
}

float won::priv::UpdateLimiter::GetUpdatesPerSecond()
{
	return updateps;
}

float won::priv::UpdateLimiter::GetRendersPerSecond()
{
	return renderps;
}
