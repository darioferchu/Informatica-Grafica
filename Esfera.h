
#include "VectorT.h"

/*
 * Clase Esfera con construcores, destructor y métodos
 * para trabajar con ellas.
 */
class Esfera {
	public:
		Esfera();
		Esfera(VectorT, float, VectorT);
		virtual ~Esfera();

		float getRadio();
		VectorT getCentro();
		VectorT getColor();

	private:
		float radio;
		VectorT centro;
		VectorT color;
};
