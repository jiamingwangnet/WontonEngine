#pragma once

#include <random>

namespace won
{
	class Random
	{
	public:
		template<class T>
		static T RandomRange(T min, T max) { return (T)-1; }

		template<>
		static int RandomRange<int>(int min, int max);

		template<>
		static long long RandomRange<long long>(long long min, long long max);

		template<>
		static float RandomRange<float>(float min, float max);

		template<>
		static double RandomRange<double>(double min, double max);

	private:
		static std::random_device rd;
		static std::mt19937 rng;
	};
	template<>
	inline int Random::RandomRange<int>(int min, int max)
	{
		std::uniform_int_distribution<int> dist{min, max};
		return dist(rng);
	}
	template<>
	inline long long Random::RandomRange<long long>(long long min, long long max)
	{
		std::uniform_int_distribution<long long> dist{ min, max };
		return dist(rng);
	}
	template<>
	inline float Random::RandomRange<float>(float min, float max)
	{
		std::uniform_real_distribution<float> dist{ min, max };
		return dist(rng);
	}
	template<>
	inline double Random::RandomRange<double>(double min, double max)
	{
		std::uniform_real_distribution<double> dist{ min, max };
		return dist(rng);
	}
}