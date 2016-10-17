
#include "Esfera.h"

Esfera::Esfera(){}

Esfera::Esfera(VectorT centro, float radio) {
	this->centro = centro;
	this->radio = radio;
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
