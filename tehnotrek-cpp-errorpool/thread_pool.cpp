#include "thread_pool.hpp"

thread_pool::thread_pool(int size)
{
	for (int i = 0; i < ((size > 0) ? size : 4); i++)
	{
		threads.push_back(std::thread(&thread_pool::thread_main, this));
	}
}

thread_pool::~thread_pool()
{
	{
		std::lock_guard<std::mutex> lock(mutex);
		terminate_flag = true;
	}

	cv.notify_all();

	for (int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}
}

void thread_pool::push(std::function<void()> handler)
{
	std::unique_lock<std::mutex> lock(mutex);
	queue.push(handler);
	lock.unlock();
	cv.notify_one();
}

void thread_pool::thread_main()
{
	std::unique_lock<std::mutex> lock(mutex);
	while (!terminate_flag)
	{
		cv.wait(lock, [this]() {return (!queue.empty() || terminate_flag);});
		while (!queue.empty())
		{
			std::function<void()> task = queue.front();
			queue.pop();
			lock.unlock();
			task();
			lock.lock();
		}
	}
}
