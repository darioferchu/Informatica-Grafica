
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
		VectorT getKd();
		float getKs();
		float getAlpha();

	private:
		float radio;
		VectorT centro;
		VectorT color;
		VectorT Kd;
		float Ks = 255;
		float alpha = 10;
};
