
#include "Vector.h"
#include "Objeto.h"

class Esfera {
public:
	Esfera();
	Esfera(Vector, float);
	virtual ~Esfera();

	float getRadio();
	Vector getCentro();

private:
	float radio;
	Vector centro;
};
