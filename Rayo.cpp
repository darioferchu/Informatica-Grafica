
#include "Rayo.h"

/*
 * Constructor de un objeto Rayo.
 */
Rayo::Rayo(VectorT puntoR[], VectorT direccionR[]) {

	punto = puntoR;
	direccion = direccionR;
}

/*
 * Destructor de un objeto Rayo.
 */
Rayo::~Rayo() {}

/*
 * Función que devuelve la dirección del rayo.
 */
VectorT Rayo::getDireccion(){

	return *direccion;
}

/*
 * Función que devuelve el punto del rayo.
 */
VectorT Rayo::getPunto() {

	return *punto;
}
