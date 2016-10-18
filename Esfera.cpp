
#include "Esfera.h"

Esfera::Esfera(){}

Esfera::Esfera(VectorT centro, float radio, VectorT color) {
	this->centro = centro;
	this->radio = radio;
	this->color = color;
}

Esfera::~Esfera() {
	// TODO Auto-generated destructor stub
}

float Esfera::getRadio() {
	return radio;
}

VectorT Esfera::getCentro() {
	return centro;
}

VectorT Esfera::getColor() {
	return color;
}
