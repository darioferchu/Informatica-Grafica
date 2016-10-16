
#include "Rayo.h"

/*
 * Constructor de un objeto Rayo vacío.
 */
Rayo::Rayo() {}

/*
 * Constructor de un objeto Rayo.
 */
Rayo::Rayo(Vector puntoR[], Vector direccionR[]) {

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
Vector Rayo::getDireccion(){

	return direccion;
}

/*
 * Función que devuelve el punto del rayo.
 */
Vector Rayo::getPunto() {

	return punto;
}
