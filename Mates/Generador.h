#pragma once

#include <iostream>
#include <string>

namespace sim {

	class Generador {
	public:
		static double CuadradosMedios(int x0, int n);
		static double ProductosMedios(int x0, int x1, int n);
		static double MultiplicarConstante(int x0, int c, int n);
		static double AlgoritmoLineal(int x, int a, int c, int m, int n);
		static double AlgoritmoCongruencialMultiplicativo(int xi, int k, int g, int m, int n);
		static double AlgoritmoCongruencialAditivo(int x[], int n, int m, int xi);

	private:
		static int getMedios(int x);
		static double calcularRi(int x, int m);
	};

}
