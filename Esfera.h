
#include "VectorT.h"

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
