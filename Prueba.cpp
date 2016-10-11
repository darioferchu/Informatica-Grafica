
#include "Vector.h";
using namespace std;
#include <iostream>

int main() {
	float t1[3] = {1.0, 2.0, 3.0};
	float t2[3] = {4.0, 5.0, 13.0};
	float t3[3] = {7.0, 8.0, -1.0};
	Vector v1 = Vector(t1,3);
	Vector v2 = Vector(t2,3);

	Vector suma = v1.prodVectorial(v2);
	float escalar = v1.prodEscalar(v2);

	for(int i=0; i<v1.getLon(); i++){
		cout << suma.getValPos(i) << " ";
	}

	return 0;
}
