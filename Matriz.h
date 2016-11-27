
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

		// Métodos getter.
		int getNumFilas();
		int getNumColumnas();
		VectorT getFila(int);

	private:
		int tamFilas;	// Número de filas.
		int tamColumnas;	// Número de columnas.
		VectorT *matriz;	// Puntero a la matriz.
};

/*
 * Sobrecarga de operadores para matriz.
 */
Matriz operator +(Matriz, Matriz);
Matriz operator -(Matriz, Matriz);
Matriz operator *(Matriz, float);
Matriz operator /(Matriz, float);
