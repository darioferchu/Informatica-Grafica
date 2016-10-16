
#include "Esfera.h"

Esfera::Esfera(){}

Esfera::Esfera(Vector centro, float radio) {
	this->centro = centro;
	this->radio = radio;
}

Esfera::~Esfera() {
	// TODO Auto-generated destructor stub
}

float Esfera::getRadio() {
	return radio;
}

Vector Esfera::getCentro() {
	return centro;
}
