#include "include/WontonEngine/Time.h"
#include <SDL3/SDL.h>

int won::Time::rdrFrames = 0;
int won::Time::updFrames = 0;
float won::Time::deltaTime = .0f;
float won::Time::rdeltaTime = .0f;
uint64_t won::Time::lastFrameTime = 0;
uint64_t won::Time::rlastFrameTime = 0;

float won::Time::DeltaTime()
{
	return deltaTime;
}

float won::Time::RDeltaTime()
{
	return rdeltaTime;
}

uint64_t won::Time::GetTime()
{
	return SDL_GetTicks();
}

unsigned int won::Time::GetRenderFrames()
{
	return rdrFrames;
}

unsigned int won::Time::GetUpdateFrames()
{
	return updFrames;
}

void won::priv::TimeUpd::UpdateDelta()
{
	uint64_t currentTime = SDL_GetTicks();
	uint64_t deltaMillisec = currentTime - Time::lastFrameTime;
	Time::lastFrameTime = currentTime;

	Time::deltaTime = (float)deltaMillisec / 1000.0f;
}

void won::priv::TimeUpd::UpdateRDelta()
{
	uint64_t currentTime = SDL_GetTicks();
	uint64_t deltaMillisec = currentTime - Time::rlastFrameTime;
	Time::rlastFrameTime = currentTime;

	Time::rdeltaTime = (float)deltaMillisec / 1000.0f;
}