#include "Matriz.h"

/*
 * Constructor de un objeto Matríz vacío.
 */
Matriz::Matriz() {}

/*
 * Constructor de un objeto Matríz.
 */
Matriz::Matriz(Vector vectores[],int vects) {

	tamFilas = vects;
	tamColumnas = vectores[0].getLon();
	matriz = vectores;
}

/*
 * Destructor de un objeto Matríz.
 */
Matriz::~Matriz() {}

/*
 * Definición de la operación de suma de dos matrices.
 */
Matriz operator +(Matriz m1, Matriz m2) {

	Vector *suma = new Vector[m1.getNumFilas()];
	for(int i=0; i<m1.getNumFilas(); i++){
		suma[i] = m1.getFila(i) + m2.getFila(i);
	}

	return Matriz(suma,m1.getNumFilas());
}

/*
 * Definición de la operación de resta de dos matrices.
 */
Matriz operator -(Matriz m1, Matriz m2) {

	Vector *resta = new Vector[m1.getNumFilas()];
	for(int i=0; i<m1.getNumFilas(); i++){
		resta[i] = m1.getFila(i) - m2.getFila(i);
	}

	return Matriz(resta,m1.getNumFilas());
}

/*
 * Definición de la operación de multiplicación de una matríz
 * por un escalar.
 */
Matriz operator *(Matriz m1, float escalar) {

	Vector *mulEscalar = new Vector[m1.getNumFilas()];
	for(int i=0; i<m1.getNumFilas(); i++){
		mulEscalar[i] = m1.getFila(i) * escalar;
	}

	return Matriz(mulEscalar,m1.getNumFilas());
}


/*
 * Definición de la operación de división de una matríz por
 * un escalar.
 */
Matriz operator /(Matriz m1, float escalar) {

	Vector *divEscalar = new Vector[m1.getNumFilas()];
	for(int i=0; i<m1.getNumFilas(); i++){
		divEscalar[i] = m1.getFila(i) / escalar;
	}

	return Matriz(divEscalar,m1.getNumFilas());
}

/*
 * Función que devuelve la matríz resultante de la multiplicación
 * de dos matríces.
 */
Matriz Matriz::mult(Matriz m2) {

	Matriz m2T = m2.trasponer();
	Vector *result = new Vector[tamFilas];
	for(int i = 0; i<tamFilas; i++) {
		float *vector = new float [m2.getNumColumnas()];
		for(int j = 0; j < m2.getNumColumnas(); j++) {
			vector[j] = matriz[i].prodEscalar(m2T.getFila(j));
		}
		result[i] = Vector(vector, m2.getNumColumnas());
	}

	return Matriz(result, tamFilas);
}

/*
 * Función que devuelve la matríz traspuesta de una matríz dada.
 */
Matriz Matriz::trasponer() {

	Vector *traspuesto = new Vector[tamColumnas];
	for (int i = 0; i< tamColumnas; i++) {
		float *vector = new float [tamFilas];
		for(int j = 0; j < tamFilas; j++) {
			vector[j] = matriz[j].getValPos(i);
		}
		traspuesto[i] = Vector(vector,tamColumnas);
	}

	return Matriz(traspuesto,tamColumnas);
}

/*
 * Función que devuelve el número de filas de la matríz.
 */
int Matriz::getNumFilas() {

	return tamFilas;
}

/*
 * Función que devuelve el vector de una fila dada de la matríz.
 */
Vector Matriz::getFila(int fila){

	return matriz[fila];
}

/*
 * Función que devuelve el número de columnas de la matríz.
 */
int Matriz::getNumColumnas() {

	return tamColumnas;
}
