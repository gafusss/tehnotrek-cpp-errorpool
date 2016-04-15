#include "thread_pool.hpp"

thread_pool::thread_pool(int size)
{
	for (int i = 0; i < ((size > 0) ? size : 4); i++)
	{
		threads.push_back(std::thread(&thread_pool::thread_main, this));
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
	while (true)
	{
		cv.wait(lock, [this]() {return !queue.empty();});
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
