
/*#include "Matriz.h";

int main() {
	float t1[3] = {1.0, 2.0, 3.0};
	float t2[3] = {4.0, 5.0, 13.0};
	float t3[3] = {7.0, 8.0, -1.0};

	Vector suma [3];
	suma[0] = Vector(t1,3);
	suma[1] = Vector(t2,3);
	suma[2] = Vector(t3,3);

	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			cout << suma[i].getValPos(j) << " ";
		}
		cout << "\n";
	}

	Matriz m1 = Matriz(suma,3);
	Matriz m2 = Matriz(suma,3);

	Matriz resultado;
	resultado = m1 + m2;

	cout << "hola" << "\n";

	for(int i=0; i<resultado.getNumFilas(); i++){
		for(int j=0; j<resultado.getNumColumnas(); j++){
			cout << resultado.getFila(i).getValPos(j) << " ";
		}
		cout << "\n";
	}
	return 0;
}*/
