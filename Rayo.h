
#include "Matriz.h"

/*
 * Clase Rayo con construcores, destructor y métodos
 * para trabajar con ellos.
 */
class Rayo {
	public:
		Rayo();
		Rayo(Vector[],Vector[]);
		~Rayo();

		Vector getDireccion();
		Vector getPunto();

	private:
		Vector *punto;
		Vector *direccion;
};
