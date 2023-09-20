#pragma once

#include "Game.h"

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
		static unsigned int GetTime();

	private:
		friend class priv::TimeUpd;

		static int updFrames;
		static int rdrFrames;
	};

	namespace priv
	{
		class TimeUpd
		{
		private:
			friend class Game;

			static void IncUpdFrames() { Time::updFrames++; }
			static void IncRdrFrames() { Time::rdrFrames++; }
		};
	}
}