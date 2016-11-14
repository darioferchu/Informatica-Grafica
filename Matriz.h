
#include "VectorT.h"

/*
 * Clase Matriz con construcores, destructor y métodos
 * para trabajar con ellas.
 */
class Matriz {
	public:
		Matriz();
		Matriz(VectorT[],int);
		~Matriz();

		Matriz mult(Matriz);
		Matriz trasponer();

		int getNumFilas();
		int getNumColumnas();
		VectorT getFila(int);

	private:
		int tamFilas;
		int tamColumnas;
		VectorT *matriz;
};

/*
 * Sobrecarga de operadores para matriz.
 */
Matriz operator +(Matriz, Matriz);
Matriz operator -(Matriz, Matriz);
Matriz operator *(Matriz, float);
Matriz operator /(Matriz, float);
