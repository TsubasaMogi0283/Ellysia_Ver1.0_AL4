#include "Easing.h"
#include <corecrt_math.h>
#include <numbers>
#include <cmath>
//定義
double easeInSine(double x) {
	return 1.0 - std::cosf((x * std::numbers::pi) / 2.0);
}

double easeOutSine(double x) {
	return std::sinf((x * std::numbers::pi) / 2.0);
}

double easeInOutSine(double x) {
	return -(std::cosf(std::numbers::pi * x) - 1.0) / 2.0;
}

double easeInBack(double x) {
	const double c1 = 1.70158;
	const double c3 = c1 + 1.0;

	return c3 * x * x * x - c1 * x * x;
}

double easeOutBack(double x) {
	const double c1 = 1.70158;
	const double c3 = c1 + 1.0;

	return 1.0 + c3 * std::pow(x - 1.0, 3.0) + c1 * std::pow(x - 1.0, 2.0);
}

double easeOutBounce(double x) {
	const double n1 = 7.5625;
	const double d1 = 2.75;

	if (x < 1.0 / d1) {
		return n1 * x * x;
	}
	else if (x < 2.0 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}
