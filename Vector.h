#include <cmath>
using namespace std;
#include <iostream>

/*
 * Clase vector con construcores, destructor y métodos
 * para trabajar con ellos.
 */
class Vector {
	public:
		Vector();
		Vector(float vectorN[], int);
		~Vector();

		Vector prodVectorial(Vector);
		float prodEscalar(Vector);
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
Vector operator +(Vector, Vector);
Vector operator -(Vector, Vector);
Vector operator *(Vector, float);
Vector operator /(Vector, float);
