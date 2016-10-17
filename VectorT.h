#pragma once
#include <cmath>

/*
 * Clase vector con construcores, destructor y métodos
 * para trabajar con ellos.
 */
class VectorT {
	public:
		VectorT();
		VectorT(float[], int);
		~VectorT();

		VectorT prodVectorial(VectorT);
		float prodEscalar(VectorT);
		float modulo();

		float getValPos(int);
		void setValPos(float,int);
		int getLon();

	private:
		int lon;
		float *vector;
};

/*
 * Sobrecarga de operadores para vector.
 */
VectorT operator +(VectorT, VectorT);
VectorT operator -(VectorT, VectorT);
VectorT operator *(VectorT, float);
VectorT operator /(VectorT, float);
