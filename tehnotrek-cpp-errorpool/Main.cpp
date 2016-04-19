#include <iostream>
#include <string>
#include <functional>

#include "thread_pool.hpp"
#include "probability_calculator.hpp"

int main() {
	thread_pool pool;

	while (true) {
		int probability;
		std::cin >> probability;
		if (probability == -1)
		{
			return 0;
		}
		probability_calculator calculator([](const std::error_code &error) {
			std::cout << error.message() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		});
		pool.push(std::bind(calculator, probability));
	}
}