#include "include/WontonEngine/ThreadPool.h"

won::priv::ThreadPool::ThreadPool(std::size_t nThreads)
	: nThreads{ nThreads }
{
	//if (nThreads > std::thread::hardware_concurrency()) throw std::runtime_error{ "Too many threads." };
}

won::priv::ThreadPool::ThreadPool()
{
	nThreads = std::thread::hardware_concurrency();
}

won::priv::ThreadPool::~ThreadPool()
{
	Stop();
}

void won::priv::ThreadPool::Start()
{
	for (std::size_t i = 0; i < nThreads; i++)
	{
		workers.emplace_back(&ThreadPool::ThreadLoop, this);
	}
}

void won::priv::ThreadPool::QueueJob(std::function<void()> job)
{
	{
		std::unique_lock<std::mutex> lock{ queueMutex };
		jobs.push(job);
	}
	updater.notify_one();
}

void won::priv::ThreadPool::Stop()
{
	{
		std::unique_lock<std::mutex> lock{ queueMutex };
		terminate = true;
	}
	updater.notify_all();
	for (std::size_t i = 0; i < nThreads; i++) workers[i].join();
	workers.clear();
}

bool won::priv::ThreadPool::IsBusy()
{
	bool busy;
	{
		std::unique_lock<std::mutex> lock{ queueMutex };
		busy = !jobs.empty();
	}
	return busy;
}

bool won::priv::ThreadPool::AllJobsDone()
{
	bool done;
	{
		std::unique_lock<std::mutex> lock{ activeMutex };
		done = active == 0;
	}
	return done;
}

void won::priv::ThreadPool::WaitTillDone()
{
	std::unique_lock<std::mutex> lock{ activeMutex };
	blocker.wait(lock, [this]() {return active == 0; });
}

void won::priv::ThreadPool::ThreadLoop()
{
	while (true)
	{
		std::function<void()> job;

		// wait for job
		{
			std::unique_lock<std::mutex> lock{ queueMutex };
			updater.wait(lock, [this] {return terminate || !jobs.empty(); }); // block thread until either terminate is true or a new job appears
			if (terminate) return;
			job = jobs.front();
			jobs.pop();
		}
		{
			std::unique_lock<std::mutex> lock{ activeMutex };
			active++;
		}
		job();
		{
			std::unique_lock<std::mutex> lock{ activeMutex };
			active--;
			blocker.notify_all();
		}
	}
}
