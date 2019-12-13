#include "Convolucion.h"

namespace sim {

    /*
        NOTAS:
        namespace viene siendo el package en Java

        Cada metodo esta declarado de la siguiente manera:
            NombreDeLaClase::nombreDelMetodo

        En Java no se escribe el nombre de la clase, solamente el nombre del metodo
    */

    /*
        distribucionBinomial
        Esta distribucion retorna una matriz de tipo double (esta matriz representa la tabla que hacemos con el enunciado)

        p: Constante dada por el enunciado
        ri: Matriz de numeros aleatorios dado por el enunciado
        n: Numero de filas de la matriz de numeros aleatorios
        m: Numero de columnas de la matriz de numeros aleatorios

        NOTAS:
        No es recomendable omitir n y m en este caso, a diferencia de los demas metodos donde si se pueden omitir
        El tipo de este metodo es double** pero en Java se escribe double[][]
    */
	double** Convolucion::distribucionBinomial(double p, double** r, int n, int m) {
	    /*
            tabla: Matriz de tipo double

            En Java se declara como
                double[][] tabla = new double[n][(m * 2) + 2]
		*/
		double** tabla = new double*[n];

		/*
            La sumatoria total de los resultados de cada renglon de la matriz declarada anteriormente (tabla)
		*/
		int total;

		for (int i = 0; i < n; i++) {

			// Inicializar renglon
			tabla[i] = new double[(m * 2) + 2]; // Esto no es necesario en Java
			total = 0; // IMPORTANTE: No omitir esto

			// Llenar datos
			tabla[i][0] = i + 1;

			for (int j = 1, k = 0; j <= m * 2; j += 2, k++) {
				tabla[i][j] = r[i][k];
				tabla[i][j + 1] = BEi(r[i][k], p); // Metodo utilizado para calcular BEi. NOTA: Puedes eliminar el metodo y hacer el procedimiento aqui para que no se vea muy obvio
				total += BEi(r[i][k], p); // Metodo utilizado para calcular BEi. NOTA: Puedes eliminar el metodo y hacer el procedimiento aqui para que no se vea muy obvio
			}

			tabla[i][(m * 2) + 1] = total;
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
        BEi
        Este metodo se usa para sacar la variable BEi de la distribucion binomial

        p: Constante dada por el enunciado (es la misma utilizada en la distribucion binomial)
        ri: Numero aleatorio (este proviene de la lista de numeros aleatorios utilizada en la distribucion binomial)
	*/
	int Convolucion::BEi(double p, double ri) {
		if ( (ri >= 0) && (ri < 1 - p) )
			return 0;
		if ( (ri >= 1 - p) && (ri <= 1) )
			return 1;
		return -1;
	}

	/*
        distribucionErlang
        Esta distribucion retorna una matriz de tipo double (esta matriz representa la tabla que hacemos con el enunciado)

        k: Constante dada por el enunciado (Viene representada por 2-Erlang, 3-Erlang, 4-Erlang, etc.)
        media: Media dada por el enunciado
        r: Matriz de numeros aleatorios dado por el enunciado
        n: Numero de filas de la matriz de numeros aleatorios

        NOTAS:
        No es recomendable omitir n en este caso, a diferencia de los demas metodos donde si se pueden omitir
        El tipo de este metodo es double** pero en Java se escribe double[][]
    */
    double** Convolucion::distribucionErlang(int k, double media, double** r, int n) {
		/*
            tabla: Matriz de tipo double

            En Java se declara como
                double[][] tabla = new double[n][k + 3]
		*/
		double** tabla = new double*[n];

		/*
            xi: La x calculada en cada renglon de la tabla
		*/
		double xi;

		for (int i = 0; i < n; i++) {

			// Inicializar renglon
			tabla[i] = new double[k + 3]; // Esto no es necesario en Java
			xi = 1; // IMPORTANTE: No omitir esto

			// Llenar datos
			tabla[i][0] = i + 1;

			for (int j = 1; j <= k; j++) {
                tabla[i][j] = r[i][j - 1];
				xi *= tabla[i][j];
			}

			tabla[i][k + 1] = xi;
			tabla[i][k + 2] = Y(k, media, xi); // Metodo utilizado para calcular Y. NOTA: Puedes eliminar el metodo y hacer el procedimiento aqui para que no se vea muy obvio
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
        Y
        Este metodo se usa para sacar la variable Y de la distribucion erlang

        k: Constante dada por el enunciado (es la misma utilizada en la distribucion erlang)
        media: Media dada por el enunciado
        xi: Variable calculada en la distribucion erlang
	*/
	double Convolucion::Y(double k, double media, double xi) {
		return -(media / k) * log(xi) ;
	}

	/*
        distribucionErlang
        Esta distribucion retorna una matriz de tipo double (esta matriz representa la tabla que hacemos con el enunciado)

        media: Media dada por el enunciado
        desviacionEstandar: Constante dada por el enunciado
        sumatoria: Lista de numeros dados por el enunciado
        n: Tamano de la lista de numeros (sumatoria)

        NOTAS:
        sumatoria es un arreglo de tipo double, lo que significa que puedes omitir n, ya que en Java existe arreglo.length
        El tipo de este metodo es double** pero en Java se escribe double[][]
    */
    double** Convolucion::distribucionNormal(double media, double desviacionEstandar, double sumatoria[], int n) {
        /*
            tabla: Matriz de tipo double

            En Java se declara como
                double[][] tabla = new double[n][4]
		*/
		double** tabla = new double*[n];

		for (int i = 0; i < n; i++) {

			// Inicializar renglon
			tabla[i] = new double[4]; // Esto no es necesario en Java

			// Llenar datos
			tabla[i][0] = i + 1;
			tabla[i][1] = sumatoria[i];
			tabla[i][2] = tabla[i][1] - 6;
			tabla[i][3] = (tabla[i][2] * desviacionEstandar) + media;
		}

		/*
            Aqui retornamos la tabla para imprimirla en el main, pero lo que puedes hacer para que se vea diferente es:
                1. Cambiar el tipo de este metodo a void
                2. Quitar el return tabla
                3. Imprimir la tabla aqui mismo
		*/
		return tabla;
	}
}
