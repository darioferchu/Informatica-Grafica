

using namespace std;
#include <iostream>
#include "Matriz.h"

int main() {
	float t1[] = {1.0, 2.0, 3.0};
	float t2[] = {4.0, 5.0,6.0};
	float t3[] = {7.0, 8.0,9.0};
	Vector v1 = Vector(t1,3);
	Vector v2 = Vector(t2,3);

	Vector v3 = Vector(t3,3);
	Vector L[3] = {v1,v2, v3};

	Matriz m1 = Matriz(L,3);
	Matriz m2 = Matriz(L,3);

	m1.trasponer();
	for(int i=0;i<m1.getVert();i++) {
		for(int j=0;j<m1.getHor();j++) {
			cout << m1.getMatriz()[i].getValPos(j) << " ";
		}
		cout << "\n";
	}

	return 0;
}
