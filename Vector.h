/*
 * Vector.h
 *
 *  Created on: 1 oct. 2016
 *      Author: Jorge
 */
using namespace std;
#include <iostream>

class Vector {
	public:
		Vector();
		Vector(float vectorN[], int);
		~Vector();

		void suma(Vector,Vector);
		void resta(Vector,Vector);
		void mult(Vector,float);
		void div(Vector,float);
		void prodVectorial(Vector,Vector);
		float prodEscalar(Vector);
		float getValPos(int);
		int getLon();
	private:
		int lon;
		float *vector;
};
