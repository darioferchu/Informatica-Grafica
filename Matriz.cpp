
#include "Matriz.h"

/*
 * Constructor de un objeto Matríz vacío.
 */
Matriz::Matriz() {
	tamColumnas = 0;
	tamFilas = 0;
	matriz = NULL;
	inver = NULL;
}

/*
 * Constructor de un objeto Matríz.
 */
Matriz::Matriz(VectorT vectores[],int vects) {

	tamFilas = vects;
	tamColumnas = vectores[0].getLon();
	matriz = vectores;
	inver = NULL;
}

/*
 * Destructor de un objeto Matríz.
 */
Matriz::~Matriz() {}

/*
 * Definición de la operación de suma de dos matrices.
 */
Matriz operator +(Matriz m1, Matriz m2) {

	VectorT *suma = new VectorT[m1.getNumFilas()];
	for(int i=0; i<m1.getNumFilas(); i++){
		suma[i] = m1.getFila(i) + m2.getFila(i);
	}

	return Matriz(suma,m1.getNumFilas());
}

/*
 * Definición de la operación de resta de dos matrices.
 */
Matriz operator -(Matriz m1, Matriz m2) {

	VectorT *resta = new VectorT[m1.getNumFilas()];
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

	VectorT *mulEscalar = new VectorT[m1.getNumFilas()];
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

	VectorT *divEscalar = new VectorT[m1.getNumFilas()];
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
	VectorT *result = new VectorT[tamFilas];
	for(int i = 0; i<tamFilas; i++) {
		float *vector = new float [m2.getNumColumnas()];
		for(int j = 0; j < m2.getNumColumnas(); j++) {
			vector[j] = matriz[i].prodEscalar(m2T.getFila(j));
		}
		result[i] = VectorT(vector, m2.getNumColumnas());
	}

	return Matriz(result, tamFilas);
}

/*
 * Función que devuelve la matríz traspuesta de una matríz dada.
 */
Matriz Matriz::trasponer() {

	VectorT *traspuesto = new VectorT[tamColumnas];
	for (int i = 0; i< tamColumnas; i++) {
		float *vector = new float [tamFilas];
		for(int j = 0; j < tamFilas; j++) {
			vector[j] = matriz[j].getValPos(i);
		}
		traspuesto[i] = VectorT(vector,tamColumnas);
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
VectorT Matriz::getFila(int fila){

	return matriz[fila];
}

/*
 * Función que devuelve el número de columnas de la matríz.
 */
int Matriz::getNumColumnas() {

	return tamColumnas;
}

/*
 * Función que calcula la matriz inversa.
 */
Matriz Matriz::inversa() {

	int i = 0; int j = 0; float pivote = 0;	// Variables para el calculo.
	inver = new VectorT[tamFilas];	// Matriz inversa final.
	for(int i=0; i<tamFilas; i++){		// Se rellena la matriz inversa con los valores iniciales.
		float *vector = new float [tamFilas];
		for(int j=0; j<tamFilas; j++){
			vector[j] = matriz[i].getValPos(j);
		}
		inver[i] = VectorT(vector,tamColumnas);
	}

	for(i=0; i<tamFilas; i++){		// Se iteran todos los elementos.
		j=i;
		pivote=inver[i].getValPos(j);	// Se obtiene el pivote.
		// Se calcula la inversa.
		b[i][j]=1/pivote;
		fila_pivote(i,pivote);
		col_pivote(j,pivote);
		otros(i,j,pivote);
		for(int k=0; k<tamFilas; k++){	// Se meten los valores finales en la inversa.
			for(int l=0; l<tamFilas; l++){
				inver[k].setValPos(b[k][l],l);
			}
		}
	}

	return Matriz(inver,tamFilas);		// Se devuelve la matriz inversa.
}

/*
 * Función que itera en las filas.
 */
void Matriz::fila_pivote(int i, float pivote)
{
    int m;
    for(m=0; m<tamFilas; m++)
        if(m != i)
            b[i][m]=inver[i].getValPos(m)/pivote;
}

/*
 * Función que itera en las columnas.
 */
void Matriz::col_pivote(int j, float pivote)
{
    int m;
    for(m=0; m<tamFilas; m++)
        if(m != j)
            b[m][j]=-inver[m].getValPos(j)/pivote;
}

/*
 * Función que itera en el resto de elementos.
 */
void Matriz::otros(int i, int j, float pivote)
{
    int x,y;
    for(x=0 ;x<tamFilas; x++)
        for(y=0; y<tamFilas; y++)
            if(x!=i && y!=j)
    			b[x][y]=inver[x].getValPos(y)-(inver[i].getValPos(y)*inver[x].getValPos(j))/pivote;
}
