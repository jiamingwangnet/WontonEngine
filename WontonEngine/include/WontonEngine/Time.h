#pragma once

#include "Game.h"
#include <cstdint>

namespace won
{
	namespace priv
	{
		class TimeUpd;
	}

	class Time
	{
	public:
		static float DeltaTime();
		static uint64_t GetTime();

		static unsigned int GetRenderFrames();
		static unsigned int GetUpdateFrames();

	private:
		friend class priv::TimeUpd;

		static int updFrames;
		static int rdrFrames;

		static uint64_t lastFrameTime;

		static float deltaTime;
	};

	namespace priv
	{
		class TimeUpd
		{
		private:
			friend class Game;

			static void IncUpdFrames() { Time::updFrames++; }
			static void IncRdrFrames() { Time::rdrFrames++; }

			static void UpdateDelta();
		};
	}
}