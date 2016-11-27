#pragma once
#include <cmath>

/*
 * Clase vector con construcores, destructor y métodos
 * para trabajar con ellos.
 */
class VectorT {
	public:
		VectorT();	// Constructor sin parámetros.
		VectorT(float[], int);	// Constructor con parámetros.
		~VectorT();	// Destructor.

		VectorT prodVectorial(VectorT);		// Método para el productor vectorial.
		float prodEscalar(VectorT);		// Método para el producto escalar.
		float modulo();		// Método para el modulo.

		// Métodos getter.
		float getValPos(int);
		void setValPos(float,int);
		int getLon();

	private:
		int lon;	// Número de elementos del vector.
		float *vector;	// Puntero al vector.
};

/*
 * Sobrecarga de operadores para vector.
 */
VectorT operator +(VectorT, VectorT);
VectorT operator -(VectorT, VectorT);
VectorT operator *(VectorT, float);
VectorT operator /(VectorT, float);
