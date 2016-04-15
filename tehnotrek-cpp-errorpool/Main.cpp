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
		probability_calculator calculator([](const std::error_code &error) {
			std::cout << error.message() << std::endl;
		});
		pool.push(std::bind(calculator, probability));
	}
}