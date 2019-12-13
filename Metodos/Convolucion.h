#pragma once

#include <cmath>

namespace sim {

	class Convolucion {
	public:
		static double** distribucionBinomial(double p, double** r, int n, int m);
        static double** distribucionErlang(int k, double media, double** r, int n);
        static double** distribucionNormal(double media, double desviacionEstandar, double sumatoria[], int n);
		

	private:
		static double Y(double k, double media, double xi);
		static int BEi(double ri, double p);
	};

}
