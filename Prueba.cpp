


#include "Matriz.h"

int main() {
	float t1[2] = {1.0, 2.0};
	float t2[2] = {4.0, 5.0};
	float t3[2] = {7.0, 8.0};
	Vector v1 = Vector(t1,2);
	Vector v2 = Vector(t2,2);

	Vector v3 = Vector(t3,2);
	Vector L[3] = {v1,v2,v3};

	Matriz m1 = Matriz(L,3);
	Matriz m2 = Matriz(L,3);
	m2.trasponer();
	for(int i=0;i<m1.getVert();i++) {
			for(int j=0;j<m1.getHor();j++) {
				cout << m1.getMatriz()[i].getValPos(j) << " ";
			}
			cout << "\n";
	}
	cout << "X\n";
	for(int i=0;i<m2.getVert();i++) {
			for(int j=0;j<m2.getHor();j++) {
				cout << m2.getMatriz()[i].getValPos(j) << " ";
			}
			cout << "\n";
	}
	m1.mult(m1, m2);
	cout << "=\n";
	for(int i=0;i<m1.getVert();i++) {
		for(int j=0;j<m1.getHor();j++) {
			cout << m1.getMatriz()[i].getValPos(j) << " ";
		}
		cout << "\n";
	}

	return 0;
}
