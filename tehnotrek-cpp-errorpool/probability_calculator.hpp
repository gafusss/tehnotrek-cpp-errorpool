#pragma once

#include <iostream>
#include <functional>

class probability_calculator {

	std::function<void(std::error_code&)> handler;

public:

	probability_calculator(std::function<void(std::error_code&)> handler) :handler(handler) {};

	void operator()(int probability) const;
};