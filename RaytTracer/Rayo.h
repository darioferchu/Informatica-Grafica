
#include "Matriz.h"

/*
 * Clase Rayo con construcores, destructor y métodos
 * para trabajar con ellos.
 */
class Rayo {
	public:
		Rayo(VectorT,VectorT);	// Constructor con parámetros.
		~Rayo();	// Destructor.

		// Métodos getter.
		VectorT getDireccion();
		VectorT getPunto();

	private:
		VectorT punto;	// Punto del rayo.
		VectorT direccion;	// Dirección del rayo.
};
