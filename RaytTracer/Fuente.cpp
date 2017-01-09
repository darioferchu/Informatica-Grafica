
#include "Fuente.h"

/*
 * Constructor de un objeto fuente vacío.
 */
Fuente::Fuente(){
	potencia = 0.0;
}

/*
 * Constructor de un objeto fuente con punto y potencia.
 */
Fuente::Fuente(VectorT punto, float potencia) {
	this->punto = punto;
	this->potencia = potencia;
}

/*
 * Destructor de un objeto fuente.
 */
Fuente::~Fuente() {
	// TODO Auto-generated destructor stub
}

/*
 * Método que devuelve la potencia de la fuente.
 */
float Fuente::getPotencia() {

	return potencia;
}

/*
 * Método que devuelve el punto de la fuente.
 */
VectorT Fuente::getPunto() {

	return punto;
}
