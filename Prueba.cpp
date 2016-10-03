

#include "Vector.h"

int main() {
	float vector1[] = {1.0, 2.0, 3.0, 4.0};
	float vector2[] = {1.0,2.0,3.0,4.0};
	cout << "jajaja";
	Vector v1 = Vector(vector1,4);

	Vector v2 = Vector(vector2,4);
	Vector resul;
	float division = 2.0;
	float resultado = v1.prodEscalar(v2);
	for (int i=0;i<resul.getLon();i++){
		cout << resultado << " ";
		cout << "\n";
	}
	cout << "\n";
	return 0;
}
