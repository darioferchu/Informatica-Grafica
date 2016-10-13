/*
 * Imagen.cpp
 *
 *  Created on: 13 oct. 2016
 *      Author: Jorge
 */

#include "Imagen.h"

Imagen::Imagen(int altura, int ancho) {
	this->altura = altura;
	this->ancho = ancho;
	numDatosFila = 3*ancho;
	datos = new int[altura][numDatosFila];
}

Imagen::Imagen(int altura, int ancho, int **datos) {
	this->altura = altura;
	this->ancho = ancho;
	numDatosFila = 3*ancho;
	this->datos = datos;
}

Imagen::~Imagen() {
	// TODO Auto-generated destructor stub
}

int Imagen::getAltura() {
	return altura;
}

int Imagen::getDatosFila() {
	return numDatosFila;
}

int Imagen::getAncho() {
	return ancho;
}

void Imagen::setValorPos(int fila,int columna, int color) {
	datos[fila][columna] = color;
}

void crearFichero(char* nombre);

