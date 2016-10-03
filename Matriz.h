/*
 * Matriz.h
 */

#include "Vector.h"

class Matriz {
	public:
		Matriz();
		Matriz(int, int);
		Matriz(Vector[],int);
		virtual ~Matriz();

		void suma(Matriz,Matriz);
		void resta(Matriz,Matriz);
		void mult(Matriz,Matriz);
		void mult(Matriz,float);
		void div(Matriz,float);
		void trasponer();

		int getHor();
		int getVert();

		Vector* getMatriz();
	private:
		int numVect;
		int tamVect;
		Vector *matriz;
};
