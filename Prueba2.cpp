
#include "Matriz.h";
using namespace std;
#include <iostream>

int main() {
	float t1[3] = {1.0, 2.0, 3.0};
	float t2[3] = {4.0, 5.0, 13.0};
	float t3[3] = {7.0, 8.0, -1.0};
	float t4[3] = {2.0, 3.0, 8.0};
	float t5[3] = {7.0, 6.0, 15.0};
	float t6[3] = {9.0, 4.0, -3.0};
	Vector v1 = Vector(t1,3);
	Vector v2 = Vector(t2,3);
	Vector v3 = Vector(t3,3);
	Vector v4 = Vector(t4,3);
	Vector v5 = Vector(t5,3);
	Vector v6 = Vector(t6,3);

	Vector aV1[] = {v1,v2,v3};
	Vector aV2[] = {v4,v5,v6};

	Matriz m1 = Matriz(aV1,3);
	Matriz m2 = Matriz(aV2,3);
	for(int i=0; i<m1.getNumFilas(); i++){
		for(int j=0; j<m1.getNumColumnas(); j++){
			cout << m1.getMatriz()[i].getValPos(j) << " ";
		}
		cout << "\n";
	}
	cout << "+\n";
	for(int i=0; i<m2.getNumFilas(); i++){
		for(int j=0; j<m2.getNumColumnas(); j++){
			cout << m2.getMatriz()[i].getValPos(j) << " ";
		}
		cout << "\n";
	}

	Matriz m3 = m1 + m2;

	cout << "=\n";
	for(int i=0; i<m3.getNumFilas(); i++){
		for(int j=0; j<m3.getNumColumnas(); j++){
			cout << m3.getMatriz()[i].getValPos(j) << " ";
		}
		cout << "\n";
	}

	return 0;
}
