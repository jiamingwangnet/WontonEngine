#pragma once

#include <queue>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>

namespace won
{
	namespace priv
	{
		class ThreadPool
		{
		public:
			ThreadPool(std::size_t nThreads);
			ThreadPool();
			~ThreadPool();

			void Start();
			void QueueJob(std::function<void()> job);
			void Stop();
			bool IsBusy();
			bool AllJobsDone();
			void WaitTillDone();

		private:
			void ThreadLoop();

		private:
			bool terminate = false;
			std::size_t active = 0;
			std::mutex activeMutex;
			std::size_t nThreads;
			std::vector<std::thread> workers;
			std::condition_variable updater;
			std::mutex queueMutex;
			std::queue<std::function<void()>> jobs; // https://stackoverflow.com/questions/15752659/thread-pooling-in-c11
			std::condition_variable blocker;
		};
	}
}