
#include "VectorT.h"

/*
 * Clase Fuente con construcores, destructor y métodos
 * para trabajar con ellas.
 */
class Fuente {
	public:
		Fuente();		// Constructor sin parámetros.
		Fuente(VectorT, float);	// Constructor con parámetros.
		virtual ~Fuente();	// Destructor.

		// Métodos getter.
		VectorT getPunto();
		float getPotencia();

	private:
		VectorT punto;		// Punto de la fuente.
		float potencia;		// Potencia de la fuente.
};
