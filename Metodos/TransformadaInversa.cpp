#include "TransformadaInversa.h"

namespace sim {

    /*
        NOTAS:
        namespace viene siendo el package en Java

        Cada metodo esta declarado de la siguiente manera:
            NombreDeLaClase::nombreDelMetodo

        En Java no se escribe el nombre de la clase, solamente el nombre del metodo
    */

    /*
        distribucionUniforme
        Esta distribucion retorna una matriz de tipo double (esta matriz representa la tabla que hacemos con el enunciado)

        a: Constante menor dada por el enunciado
        b: Constante mayor dada por el enunciado
        r: Lista de numeros aleatorios dado por el enunciado
        n: El tamano de la lista de numeros aleatorios

        NOTAS:
        r es un arreglo de tipo double, lo que significa que puedes omitir n, ya que en Java existe arreglo.length
        El tipo de este metodo es double** pero en Java se escribe double[][]
    */
    double** TransformadaInversa::distribucionUniforme(double a, double b, double r[], int n) {
		/*
            tabla: Matriz de tipo double

            En Java se declara como
                double[][] tabla = new double[n][3]
		*/
		double** tabla = new double*[n];

		for (int i = 0; i < n; i++) {

			// Inicializar renglon
			tabla[i] = new double[3]; // Esto no es necesario en Java

			// Llenar datos
			tabla[i][0] = i + 1;
			tabla[i][1] = r[i];
			tabla[i][2] = xi_Uniforme(a, b, r[i]); // Metodo utilizado para calcular xi. NOTA: Puedes eliminar el metodo y hacer el procedimiento aqui para que no se vea muy obvio
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
        xi_Uniforme
        Este metodo se usa para sacar la variable xi de la distribucion uniforme

        a: Constante menor dada por el problema (es la misma utilizada en la distribucion uniforme)
        b: Constante mayor dada por el problema (es la misma utilizada en la distribucion uniforme)
        ri: Numero aleatorio (este proviene de la lista de numeros aleatorios utilizada en la distribucion uniforme)
	*/
	double TransformadaInversa::xi_Uniforme(double a, double b, double ri) {
		return a + ( (b - a) * ri );
	}

	/*
        distribucionExponencial
        Esta distribucion retorna una matriz de tipo double (esta matriz representa la tabla que hacemos con el enunciado)

        media: La media dada por el enunciado
        r: Lista de numeros aleatorios dado por el enunciado
        n: El tamano de la lista de numeros aleatorios

        NOTAS:
        r es un arreglo de tipo double, lo que significa que puedes omitir n, ya que en Java existe arreglo.length
        El tipo de este metodo es double** pero en Java se escribe double[][]
	*/
    double** TransformadaInversa::distribucionExponencial(double media, double r[], int n) {
		/*
            tabla: Matriz de tipo double

            En Java se declara como
                double[][] tabla = new double[n][3]
		*/
		double** tabla = new double*[n];

		for (int i = 0; i < n;  i++) {

			// Inicializar renglon
			tabla[i] = new double[3]; // Esto no es necesario en Java

			// Llenar datos
			tabla[i][0] = i + 1;
			tabla[i][1] = r[i];
			tabla[i][2] = xi_Exponencial(media, r[i]); // Metodo utilizado para calcular xi. NOTA: Puedes eliminar el metodo y hacer el procedimiento aqui para que no se vea muy obvio
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
        xi_Exponencial
        Este metodo se usa para sacar la variable xi de la distribucion exponencial

        media: La media dada por el enunciado (es la misma utilizada en la distribucion exponencial)
        ri: Numero aleatorio (este proviene de la lista de numeros aleatorios utilizada en la distribucion exponencial)
	*/
    double TransformadaInversa::xi_Exponencial(double media, double ri) {
		return -media * log(1 - ri);
	}

}

