
#include "VectorT.h"

class Esfera {
	public:
		Esfera();
		Esfera(VectorT, float);
		virtual ~Esfera();

		float getRadio();
		VectorT getCentro();

	private:
		float radio;
		VectorT centro;
};
