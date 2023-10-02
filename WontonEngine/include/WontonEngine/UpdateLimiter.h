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

			static float UpdatesPerSecond();

		private:
			static unsigned int startTicks;
		};
	}
}