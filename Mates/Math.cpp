#include "Math.h"

namespace sim {

	const double Math::Euler = 2.7182;

	int Math::factorial(int x) {
		for (int i = x - 1; i > 1; i--)
			x *= i;
		return x;
	}

}
