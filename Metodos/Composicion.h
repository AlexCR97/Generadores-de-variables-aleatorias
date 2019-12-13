#pragma once

#include <cmath>

namespace sim {

	class Composicion {
	public:
        static double** distribucionTriangular(double a, double b, double moda, double ri[], double rj[], int n);

	private:
		static double xi_Triangular_Menor(double a, double c, double ri);
		static double xi_Triangular_Mayor(double b, double c, double ri);
	};

}


