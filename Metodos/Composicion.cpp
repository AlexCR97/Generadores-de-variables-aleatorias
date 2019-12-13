#include "Composicion.h"

#include <iostream>

namespace sim {

    /*
        NOTAS:
        namespace viene siendo el package en Java

        Cada metodo esta declarado de la siguiente manera:
            NombreDeLaClase::nombreDelMetodo

        En Java no se escribe el nombre de la clase, solamente el nombre del metodo
    */

    /*
        distribucionTriangular
        Esta distribucion retorna una matriz de tipo double (esta matriz representa la tabla que hacemos con el enunciado)

        a: Constante menor dada por el enunciado
        b: Constante mayor dada por el enunciado
        moda: Moda dada por el enunciado
        ri: Primera lista de numeros aleatorios dado por el enunciado
        rj: Segunda lista de numeros aleatorios dado por el enunciado
        n: El tamano de las listas de numeros aleatorios

        NOTAS:
        ri y rj son arreglos de tipo double, lo que significa que puedes omitir n, ya que en Java existe arreglo.length
        El tipo de este metodo es double** pero en Java se escribe double[][]
    */
    double** Composicion::distribucionTriangular(double a, double b, double moda, double ri[], double rj[], int n) {
        /*
            tabla: Matriz de tipo double

            En Java se declara como
                double[][] tabla = new double[n][5]
		*/
		double** tabla = new double*[n];

		for (int i = 0; i < n; i++) {

			// Inicializar renglon
			tabla[i] = new double[5]; // Esto no es necesario en Java

			// Llenar datos
			tabla[i][0] = i + 1;
			tabla[i][1] = rj[i];
			tabla[i][2] = ri[i];

			if (rj[i] <= (double) (moda - a) / (double) (b - a)) {
				tabla[i][3] = xi_Triangular_Menor(a, moda, ri[i]); // Metodo utilizado para calcular xi menor. NOTA: Puedes eliminar el metodo y hacer el procedimiento aqui para que no se vea muy obvio
				tabla[i][4] = 0;
			}
			else {
				tabla[i][3] = 0;
				tabla[i][4] = xi_Triangular_Mayor(b, moda, ri[i]); // Metodo utilizado para calcular xi mayor. NOTA: Puedes eliminar el metodo y hacer el procedimiento aqui para que no se vea muy obvio
			}
		}

		/*
            Aqui retornamos la tabla para imprimirla en el main, pero lo que puedes hacer para que se vea diferente es:
                1. Cambiar el tipo de este metodo a void
                2. Quitar el return tabla
                3. Imprimir la tabla aqui mismo
		*/
		return tabla;
	}

	/*
        xi_Triangular_Menor
        Este metodo se usa para sacar la variable xi menor de la distribucion triangular

        a: Constante menor dada por el enunciado (es la misma utilizada en la distribucion triangular)
        moda: Moda dada por el enunciado (es la misma utilizada en la distribucion triangular)
        ri: Numero aleatorio (este proviene de la lista de numeros aleatorios utilizada en la distribucion triangular)
	*/
	double Composicion::xi_Triangular_Menor(double a, double moda, double ri) {
		return a + ( (moda - a) * (sqrt(ri)) );
	}

	/*
        xi_Triangular_Mayor
        Este metodo se usa para sacar la variable xi mayor de la distribucion triangular

        b: Constante mayor dada por el enunciado (es la misma utilizada en la distribucion triangular)
        moda: Moda dada por el enunciado (es la misma utilizada en la distribucion triangular)
        ri: Numero aleatorio (este proviene de la lista de numeros aleatorios utilizada en la distribucion triangular)
	*/
	double Composicion::xi_Triangular_Mayor(double b, double moda, double ri) {
		return b - ((b - moda) * (sqrt(1 - ri)));
	}

}
