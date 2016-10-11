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
		vector = new float[n];
		for (int i = 0; i < n;i++) {
			vector[i] = vectorN[i];
		}
	}

	Vector::~Vector() {}

	float Vector::getValPos(int posicion) {
			return vector[posicion];
	}

	void Vector::setValPos(float val, int posicion) {
				vector[posicion] = val;
	}

	int Vector::getLon() {
		return lon;
	}

	Vector operator +(Vector vector1, Vector vector2) {
		float suma [vector1.getLon()];
		for(int i=0; i<vector1.getLon(); i++){
			suma[i] = vector1.getValPos(i) + vector2.getValPos(i);
		}
		return Vector(suma,vector1.getLon());
	}

	Vector operator -(Vector vector1, Vector vector2) {
		float resta [vector1.getLon()];
		for(int i=0; i<vector1.getLon(); i++){
			resta[i] = vector1.getValPos(i) - vector2.getValPos(i);
		}
		return Vector(resta,vector1.getLon());
	}

	Vector operator *(Vector vector1, float escalar) {
		float mulEscalar [vector1.getLon()];
		for(int i=0; i<vector1.getLon(); i++){
			mulEscalar[i] = vector1.getValPos(i) * escalar;
		}
		return Vector(mulEscalar,vector1.getLon());
	}

	Vector operator /(Vector vector1, float escalar) {
		float divEscalar [vector1.getLon()];
		for(int i=0; i<vector1.getLon(); i++){
			divEscalar[i] = vector1.getValPos(i) / escalar;
		}
		return Vector(divEscalar,vector1.getLon());
	}

	float Vector::prodEscalar(Vector vector2) {
		float escalar = 0.0;
		for(int i=0;i<lon;i++) {
			escalar = escalar + vector[i]*vector2.getValPos(i);
		}
		return escalar;
	}

	Vector Vector::prodVectorial(Vector vector2) {
		float mulVectorial [lon];
		for(int i=0; i<lon; i++){
			mulVectorial[i] = vector[i] * vector2.getValPos(i);
		}
		return Vector(mulVectorial,lon);
	}

	float Vector::modulo() {
		float modulo = 0.0;
		for(int i=0;i<lon;i++) {
			modulo = modulo + vector[i]^2;
		}
		return sqrt(modulo);
	}
