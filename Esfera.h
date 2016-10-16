/*
 * Esfera.h
 *
 *  Created on: 16 oct. 2016
 *      Author: Jorge
 */

#include "Vector.h"
#include "Objeto.h"

class Esfera {
public:
	Esfera(Vector, float);
	virtual ~Esfera();

	float getRadio();
	Vector getCentro();

private:
	float radio;
	Vector centro;
};
