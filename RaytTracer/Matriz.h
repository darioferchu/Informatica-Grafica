
#include "VectorT.h"

/*
 * Clase Matriz con construcores, destructor y métodos
 * para trabajar con ellas.
 */
class Matriz {
	public:
		Matriz();		// Constructor sin parámetros.
		Matriz(VectorT[],int);	// Constructor con parámetros.
		~Matriz();	// Destructor.

		Matriz mult(Matriz);	// Método para multiplicar dos matrices.
		Matriz trasponer();		// Método para transponer una matriz.
		Matriz inversa();	// Método para calcular la inversa de una matríz.

		// Métodos getter.
		int getNumFilas();
		int getNumColumnas();
		VectorT getFila(int);

	private:
		int tamFilas;	// Número de filas.
		int tamColumnas;	// Número de columnas.
		VectorT *matriz;	// Puntero a la matriz.

		// Variables para el calculo de la inversa.
		VectorT *inver;
		float b[4][4];

		// Métodos para el cálculo de la inversa.
		void fila_pivote(int,float);
		void col_pivote(int,float);
		void otros(int,int,float);
};

/*
 * Sobrecarga de operadores para matriz.
 */
Matriz operator +(Matriz, Matriz);
Matriz operator -(Matriz, Matriz);
Matriz operator *(Matriz, float);
Matriz operator /(Matriz, float);
