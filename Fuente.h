/*
 * Fuente.h
 *
 *  Created on: 26 oct. 2016
 *      Author: Jorge
 */

#include "VectorT.h"

class Fuente {
public:
	Fuente();
	Fuente(VectorT, float);
	virtual ~Fuente();

	VectorT getPunto();
	float getPotencia();

private:
	VectorT punto;
	float potencia;
};
