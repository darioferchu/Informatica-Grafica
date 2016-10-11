/*
 * Matriz.cpp
 *
 *  Created on: 3 oct. 2016
 *      Author: Jorge
 */

#include "Matriz.h"

Matriz::Matriz() {}

Matriz::Matriz(int hor, int vert) {
	tamFilas = vert;
	tamColumnas = hor;
}

Matriz::Matriz(Vector vectores[],int vects) {
	tamFilas = vects;
	tamColumnas = vectores[0].getLon();
	matriz = vectores;
}

Matriz::~Matriz() {}

Matriz operator +(Matriz m1, Matriz m2) {
	Vector suma [] = {};
	for(int i=0; i<m1.getNumFilas(); i++){
		suma[i] = m1.getFila(i) + m2.getFila(i);
	}

	return Matriz(suma,m1.getNumFilas());
}

Matriz operator -(Matriz m1, Matriz m2) {
	Vector *resta = NULL;
	for(int i=0; i<m1.getNumFilas(); i++){
		resta[i] = m1.getFila(i) - m2.getFila(i);
	}
	return Matriz(resta,m1.getNumFilas());
}

Matriz operator *(Matriz m1, float escalar) {
	Vector *mulEscalar = NULL;
	for(int i=0; i<m1.getNumFilas(); i++){
		mulEscalar[i] = m1.getFila(i) * escalar;
	}
	return Matriz(mulEscalar,m1.getNumFilas());
}

Matriz operator /(Matriz m1, float escalar) {
	Vector *divEscalar = NULL;
	for(int i=0; i<m1.getNumFilas(); i++){
		divEscalar[i] = m1.getFila(i) / escalar;
	}
	return Matriz(divEscalar,m1.getNumFilas());
}


/*void Matriz::mult(Matriz m1, Matriz m2) {
	if(m1.getHor() == m2.getVert()) {
		Vector* f1 = m1.getMatriz();
		tamVect = m2.getHor();
		numVect = m1.getVert();
		m2.trasponer();
		Vector* f2 = m2.getMatriz();


		for(int i = 0; i<numVect; i++) {
			float vector[m2.getVert()];
			for(int j = 0; j < tamVect; j++) {
				vector[j] = f1[i].prodEscalar(f2[j]);
			}
			matriz[i] = Vector(vector,m2.getVert());
		}

	}
}

void Matriz::trasponer() {

	Vector *traspuesto = new Vector[tamVect];
	float vector[tamVect][numVect];
	for (int i = 0; i< tamVect; i++) {
		for(int j = 0; j < numVect; j++) {
			vector[i][j] = matriz[j].getValPos(i);
		}
		traspuesto[i] = Vector(vector[i],numVect);
	}
	int aux = numVect;
	numVect = tamVect;
	tamVect = aux;
	matriz = traspuesto;
}*/


Vector* Matriz::getMatriz() {
	return matriz;
}

int Matriz::getNumFilas() {
	return tamFilas;
}

Vector Matriz::getFila(int fila){
	return matriz[fila];
}

int Matriz::getNumColumnas() {
	return tamColumnas;
}
