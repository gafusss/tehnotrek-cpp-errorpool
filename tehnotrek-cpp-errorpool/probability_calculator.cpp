#include "probability_calculator.hpp"
#include "messenger_error.hpp"

#include <random>

void probability_calculator::operator()(int probability) const
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 99);
	std::error_code er = messenger_error::make_error_code(messenger_error::messenger_error_t::ok);

	int n = dist(rd);

	if (probability > n)
	{
		std::uniform_int_distribution<int> err_range(0, 7);
		er = messenger_error::make_error_code(static_cast <messenger_error::messenger_error_t>(err_range(rd)));
	}

	handler(er);
}
