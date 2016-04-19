#pragma once

#include <functional>
#include <random>
#include <thread>
#include <mutex>
#include <queue>

class thread_pool {

public:

	thread_pool(int size = std::thread::hardware_concurrency());
	~thread_pool();

	void push(std::function<void()> handler);

private:

	std::queue<std::function<void()>> queue;
	std::vector<std::thread> threads;
	std::mutex mutex;
	std::condition_variable cv;
	bool terminate_flag = false;

	void thread_main();
};