#include "Generador.h"

namespace sim {

	double Generador::CuadradosMedios(int x, int n) {
		int xi;
		double ri = 0;

		for (int i = 0; i < n; i++) {
			xi = x * x;
			x = getMedios(xi);
			ri = x / 10000.0;
		}
		return ri;
	}

	double Generador::ProductosMedios(int xi, int xj, int n) {
		int x, yi;
		double ri = 0;

		for (int i = 0; i < n; i++) {
			yi = xi * xj;
			x = getMedios(yi);
			ri = x / 10000.0;

			xi = xj;
			xj = x;
		}

		return ri;
	}

	double Generador::MultiplicarConstante(int xi, int c, int n) {
		int yi;

		for (int i = 0; i < n; i++) {
			yi = c * xi;
			xi = getMedios(yi);
		}

		return xi / 10000.0;
	}

	double Generador::AlgoritmoLineal(int xi, int a, int c, int m, int n) {
		double ri = 0;
		for (int i = 0; i < n; i++) {
			xi = ((a * xi) + c) % m;
			ri = calcularRi(xi, m);
		}
		return ri;
	}

	double Generador::AlgoritmoCongruencialMultiplicativo(int xi, int k, int g, int m, int n) {
		int a = 5 + (8 * k);
		double ri;

		for (int i = 0; i < n; i++) {
			xi = (a * xi) % m;
			ri = calcularRi(xi, m);
		}
		return ri;
	}

	double Generador::AlgoritmoCongruencialAditivo(int x[], int n, int m, int xi) {
		int tam = xi;
		int* y = new int[tam];

		for (int i = 0; i < n; i++)
			y[i] = x[i];

		for (int i = n; i < tam; i++)
			y[i] = (y[i - 1] + y[i - n]) % m;

		return calcularRi(y[tam - 1], m);
	}

	int Generador::getMedios(int x) {
		std::string s = std::to_string(x);

		if (s.size() % 2 != 0)
			s = "0" + std::to_string(x);

		while (s.size() != 4)
			s = s.substr(1, s.size() - 2);

		return std::stoi(s);
	}

	double Generador::calcularRi(int x, int m) {
		return x / (m - 1.0);
	}

}