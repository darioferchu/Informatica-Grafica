/*
 * Vector.cpp
 *
 *  Created on: 1 oct. 2016
 *      Author: Jorge
 */

#include "Vector.h"

	Vector::Vector() {}

	Vector::Vector(float vectorN[],int n){
		lon = n;
		vector = vectorN ;
	}

	Vector::~Vector() {}

	float Vector::getValPos(int posicion) {
			return vector[posicion];
	}

	int Vector::getLon() {
		return lon;
	}

	void Vector::suma(Vector vector1, Vector vector2) {
		if(vector1.getLon() == vector2.getLon()) {
			lon = vector1.getLon();
			for(int i=0;i<lon;i++) {
				vector[i] = vector1.getValPos(i)+vector2.getValPos(i);
			}
		} else {

		}
	}

	void Vector::resta(Vector vector1, Vector vector2) {
		if(vector1.getLon() == vector2.getLon()) {
			lon = vector1.getLon();
			for(int i=0;i<lon;i++) {
				vector[i] = vector1.getValPos(i)-vector2.getValPos(i);
			}
		} else {

		}
	}

	void Vector::mult(Vector vectorPar, float escalar) {
		lon = vectorPar.getLon();
		for(int i=0;i<lon;i++) {
			vector[i] = vectorPar.getValPos(i)*escalar;
		}
	}

	void Vector::div(Vector vectorPar, float escalar) {
		lon = vectorPar.getLon();
		for(int i=0;i<lon;i++) {
			vector[i] = vectorPar.getValPos(i)/escalar;
		}
	}

	void Vector::prodVectorial(Vector vector1, Vector vector2) {
		if(vector1.getLon() == vector2.getLon()) {
			lon = vector1.getLon();
			for(int i=0;i<lon;i++) {
				vector[i] = vector1.getValPos(i)*vector2.getValPos(i);
			}
		} else {

		}
	}

	float Vector::prodEscalar(Vector vector1) {
		float escalar = 0.0;
		if(lon == vector1.getLon()) {
			for(int i=0;i<lon;i++) {
				escalar = escalar + vector[i]*vector1.getValPos(i);
			}
			return escalar;
		} else {
			return 0;
		}
	}
