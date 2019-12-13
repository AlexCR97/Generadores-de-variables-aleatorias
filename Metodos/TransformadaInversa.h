#pragma once

#include <cmath>

namespace sim {

	class TransformadaInversa {
	public:
        static double** distribucionUniforme(double a, double b, double r[], int n);
        static double** distribucionExponencial(double media, double r[], int n);

	private:
        static double xi_Uniforme(double a, double b, double ri);
        static double xi_Exponencial(double media, double ri);
	};

}



