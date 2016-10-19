
#include "Matriz.h"

/*
 * Clase Rayo con construcores, destructor y métodos
 * para trabajar con ellos.
 */
class Rayo {
	public:
		Rayo(VectorT[],VectorT[]);
		~Rayo();

		VectorT getDireccion();
		VectorT getPunto();

	private:
		VectorT *punto;
		VectorT *direccion;
};
