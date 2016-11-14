
#include "VectorT.h"

/*
* Constructor de un objeto VectorT vacío.
 */
VectorT::VectorT(){
	vector = NULL;
	lon = 0;
}

/*
 * Contructor de un objeto VectorT.
 */
VectorT::VectorT(float vectorN[],int n){

	lon = n;
	vector = vectorN;
}

/*
 * Destructor de un objeto VectorT.
 */
VectorT::~VectorT() {}

/*
 * Función que devuelve el valor de un vector de una
 * posición dada.
 */
float VectorT::getValPos(int posicion) {

	return vector[posicion];
}

/*
 * Función que cambia el valor de una posición del vector
 * por otro dado.
 */
void VectorT::setValPos(float val, int posicion) {

	vector[posicion] = val;
}

/*
 * Función que devuelve la longitud del vector.
 */
int VectorT::getLon() {

	return lon;
}

/*
 * Definición de la operación de suma de dos vectores.
 */
VectorT operator +(VectorT vector1, VectorT vector2) {

	float *suma = new float [vector1.getLon()];
	for(int i=0; i<vector1.getLon(); i++){
		suma[i] = vector1.getValPos(i) + vector2.getValPos(i);
	}

	return VectorT(suma,vector1.getLon());
}

/*
 * Definición de la operación de resta de dos vectores.
 */
VectorT operator -(VectorT vector1, VectorT vector2) {

	float *resta = new float[vector1.getLon()];
	for(int i=0; i<vector1.getLon(); i++){
		resta[i] = vector1.getValPos(i) - vector2.getValPos(i);
	}

	return VectorT(resta,vector1.getLon());
}

/*
 * Definición de la operación de multiplicación de un vector
 * por un escalar.
 */
VectorT operator *(VectorT vector1, float escalar) {

	float *mulEscalar = new float[vector1.getLon()];
	for(int i=0; i<vector1.getLon(); i++){
		mulEscalar[i] = vector1.getValPos(i) * escalar;
	}

	return VectorT(mulEscalar,vector1.getLon());
}

/*
 * Definición de la operación de división de un vector por
 * un escalar.
 */
VectorT operator /(VectorT vector1, float escalar) {

	float *divEscalar = new float[vector1.getLon()];
	for(int i=0; i<vector1.getLon(); i++){
		divEscalar[i] = vector1.getValPos(i) / escalar;
	}

	return VectorT(divEscalar,vector1.getLon());
}

/*
 * Función que calcula el producto escalar de dos vectores.
 */
float VectorT::prodEscalar(VectorT vector2) {

	float escalar = 0.0;
	for(int i=0;i<lon;i++) {
		escalar = escalar + vector[i]*vector2.getValPos(i);
	}

	return escalar;
}

/*
 * Función que calcula el producto vectorial de dos vectores.
 */
VectorT VectorT::prodVectorial(VectorT vector2) {

	float *mulVectorial = new float[3];
	mulVectorial[0] = vector[1] * vector2.getValPos(2)
							- vector[2] * vector2.getValPos(1);
	mulVectorial[1] = vector[2] * vector2.getValPos(0)
							- vector[0] * vector2.getValPos(2);
	mulVectorial[2] = vector[0] * vector2.getValPos(1)
							- vector[1] * vector2.getValPos(0);

	return VectorT(mulVectorial,lon);
}

/*
 * Función que calcula el módulo de un vector.
 */
float VectorT::modulo() {

	float modulo = 0.0;
	for(int i=0;i<lon;i++) {
		modulo = modulo + pow(vector[i],2);
	}

	return sqrt(modulo);
}
