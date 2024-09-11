#pragma

namespace won
{
	namespace priv
	{
		class UpdateLimiter
		{
		public:
			static void Begin();
			static void End(float target);

			static void CalcUpdatesPerSecond();
			static void CalcRendersPerSecond();

			static float GetUpdatesPerSecond();
			static float GetRendersPerSecond();

		private:
			static unsigned int startTicks;

			static float updateps;
			static float renderps;
		};
	}
}