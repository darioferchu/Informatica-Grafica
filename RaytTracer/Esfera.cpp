
#include "Esfera.h"

/*
 * Constructor de un objeto esfera vacío.
 */
Esfera::Esfera(){
	radio = 0;
	material = 0;
	ior = -1;
	alpha = 0;
	Ks = 0;
}

/*
 * Constructor de un objeto esfera con centro, radio y coeficiente de difusion.
 */
Esfera::Esfera(VectorT centro, float radio, VectorT color, int material, float ior) {
	this->centro = centro;
	this->radio = radio;
	Kd = color;
	this->material = material;
	this->ior = ior;
	alpha = 0;
	Ks = 0;
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

/*
 * Método que devuelve el material de la esfera.
 */
int Esfera::getMaterial() {

	return material;
}

/*
 * Método que devuelve el coeficiente de refracción de la esfera.
 */
float Esfera::getIor() {

	return ior;
}

/*
 * Método que fija el coeficiente especular.
 */
void Esfera::setKs(float ks) {

	this->Ks = ks;
}

/*
 * Método que fija el coeficiente alpha.
 */
void Esfera::setAlpha(float alpha) {

	this->alpha = alpha;
}
