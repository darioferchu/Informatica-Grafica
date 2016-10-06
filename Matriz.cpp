/*
 * Matriz.cpp
 *
 *  Created on: 3 oct. 2016
 *      Author: Jorge
 */

#include "Matriz.h"

Matriz::Matriz() {}

Matriz::Matriz(int hor, int vert) {
	numVect = vert;
	tamVect = hor;
}

Matriz::Matriz(Vector vectores[],int vects) {
	numVect = vects;
	tamVect = vectores[0].getLon();
	matriz = vectores;
}

Matriz::~Matriz() {}

void Matriz::suma(Matriz m1, Matriz m2) {
	if(m1.getVert() == m2.getVert()) {
		Vector* sum1 = m1.getMatriz();
		Vector* sum2 = m2.getMatriz();

		for (int i=0;i<m1.getVert();i++) {
			matriz[i].suma(sum1[i],sum2[i]);
		}
	}
}

void Matriz::resta(Matriz m1, Matriz m2) {
	if(m1.getVert() == m2.getVert()) {
		Vector* re1 = m1.getMatriz();
		Vector* re2 = m2.getMatriz();

		for (int i=0;i<m1.getVert();i++) {
			matriz[i].resta(re1[i],re2[i]);
		}
	}
}

void Matriz::mult(Matriz m1, float n) {
	Vector* vector = m1.getMatriz();

	for (int i=0;i<m1.getVert();i++) {
		matriz[i].mult(vector[i],n);
	}
}

void Matriz::div(Matriz m1, float n) {
	Vector* vector = m1.getMatriz();

	for (int i=0;i<m1.getVert();i++) {
		matriz[i].div(vector[i],n);
	}
}


void Matriz::mult(Matriz m1, Matriz m2) {
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
}


Vector* Matriz::getMatriz() {
	return matriz;
}

int Matriz::getHor() {
	return tamVect;
}

int Matriz::getVert() {
	return numVect;
}
