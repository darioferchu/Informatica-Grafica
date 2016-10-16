/*
 * Esfera.cpp
 *
 *  Created on: 16 oct. 2016
 *      Author: Jorge
 */

#include "Esfera.h"

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
