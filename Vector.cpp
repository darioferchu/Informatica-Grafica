
#include "Vector.h"

/*
* Constructor de un objeto Vector vacío.
 */
Vector::Vector(){
	vector = NULL;
	lon = 0;
}

/*
 * Contructor de un objeto Vector.
 */
Vector::Vector(float vectorN[],int n){

	lon = n;
	vector = vectorN;
}

/*
 * Destructor de un objeto Vector.
 */
Vector::~Vector() {}

/*
 * Función que devuelve el valor de un vector de una
 * posición dada.
 */
float Vector::getValPos(int posicion) {

	return vector[posicion];
}

/*
 * Función que cambia el valor de una posición del vector
 * por otro dado.
 */
void Vector::setValPos(float val, int posicion) {

	vector[posicion] = val;
}

/*
 * Función que devuelve la longitud del vector.
 */
int Vector::getLon() {

	return lon;
}

/*
 * Definición de la operación de suma de dos vectores.
 */
Vector operator +(Vector vector1, Vector vector2) {

	float *suma = new float [vector1.getLon()];
	for(int i=0; i<vector1.getLon(); i++){
		suma[i] = vector1.getValPos(i) + vector2.getValPos(i);
	}

	return Vector(suma,vector1.getLon());
}

/*
 * Definición de la operación de resta de dos vectores.
 */
Vector operator -(Vector vector1, Vector vector2) {

	float *resta = new float[vector1.getLon()];
	for(int i=0; i<vector1.getLon(); i++){
		resta[i] = vector1.getValPos(i) - vector2.getValPos(i);
	}

	return Vector(resta,vector1.getLon());
}

/*
 * Definición de la operación de multiplicación de un vector
 * por un escalar.
 */
Vector operator *(Vector vector1, float escalar) {

	float *mulEscalar = new float[vector1.getLon()];
	for(int i=0; i<vector1.getLon(); i++){
		mulEscalar[i] = vector1.getValPos(i) * escalar;
	}

	return Vector(mulEscalar,vector1.getLon());
}

/*
 * Definición de la operación de división de un vector por
 * un escalar.
 */
Vector operator /(Vector vector1, float escalar) {

	float *divEscalar = new float[vector1.getLon()];
	for(int i=0; i<vector1.getLon(); i++){
		divEscalar[i] = vector1.getValPos(i) / escalar;
	}

	return Vector(divEscalar,vector1.getLon());
}

/*
 * Función que calcula el producto escalar de dos vectores.
 */
float Vector::prodEscalar(Vector vector2) {

	float escalar = 0.0;
	for(int i=0;i<lon;i++) {
		escalar = escalar + vector[i]*vector2.getValPos(i);
	}

	return escalar;
}

/*
 * Función que calcula el producto vectorial de dos vectores.
 */
Vector Vector::prodVectorial(Vector vector2) {

	float *mulVectorial = new float[3];
	mulVectorial[0] = vector[1] * vector2.getValPos(2)
							- vector[2] * vector2.getValPos(1);
	mulVectorial[1] = vector[2] * vector2.getValPos(0)
							- vector[0] * vector2.getValPos(2);
	mulVectorial[2] = vector[0] * vector2.getValPos(1)
							- vector[1] * vector2.getValPos(0);

	return Vector(mulVectorial,lon);
}

/*
 * Función que calcula el módulo de un vector.
 */
float Vector::modulo() {

	float modulo = 0.0;
	for(int i=0;i<lon;i++) {
		modulo = modulo + pow(vector[i],2);
	}

	return sqrt(modulo);
}
