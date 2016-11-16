
#include "Esfera.h"

/*
 * Constructor de un objeto esfera vacío.
 */
Esfera::Esfera(){
	radio = 0;
}

/*
 * Constructor de un objeto esfera con centro, radio y coeficiente de difusion.
 */
Esfera::Esfera(VectorT centro, float radio, VectorT color) {
	this->centro = centro;
	this->radio = radio;
	Kd = color;
}

/*
 * Destructor de un objeto esfera.
 */
Esfera::~Esfera() {
	// TODO Auto-generated destructor stub
}

/*
 * Método que devuelve el radio de la esfera.
 */
float Esfera::getRadio() {
	return radio;
}

/*
 * Método que devuelve el centro de la esfera.
 */
VectorT Esfera::getCentro() {
	return centro;
}

/*
 * Método que devuelve el color de la esfera.
 */
VectorT Esfera::getColor() {
	return color;
}

/*
 * Devuelve el coeficiente difuso.
 */
VectorT Esfera::getKd() {
	return Kd;
}

/*
 * Devuelve el coeficiente especular.
 */
float Esfera::getKs() {
	return Ks;
}

/*
 * Devuelve el valor alpha.
 */
float Esfera::getAlpha() {
	return alpha;
}
