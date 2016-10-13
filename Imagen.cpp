
#include "Imagen.h"

Imagen::Imagen(int altura, int ancho) {

	this->altura = altura;
	this->ancho = ancho;
	numDatosFila = 3*ancho;
	datos = new int*[this->numDatosFila];
}

Imagen::Imagen(int altura, int ancho, int *datos) {

	this->altura = altura;
	this->ancho = ancho;
	numDatosFila = 3*ancho;
	this->datos = datos;
}

Imagen::~Imagen() {}

int Imagen::getAltura() {

	return altura;
}

int Imagen::getDatosFila() {

	return numDatosFila;
}

int Imagen::getAncho() {

	return ancho;
}

void Imagen::setValorPos(int fila,int columna, int color) {

	datos[fila][columna] = color;
}

void Imagen::crearFichero(char* nombre){

	ofstream ficheroSalida;
	ficheroSalida.open (nombre);
	ficheroSalida << "P3\n";
	ficheroSalida << "# Imagen de trazador de rayos\n";
	ficheroSalida << ancho << " " << altura << "\n";
	ficheroSalida << "255\n";
	for(int i=0; i<altura; i++){
		for(int j=0; j<numDatosFila; j++){
			ficheroSalida << datos[i][j] << " ";
		}
		ficheroSalida << "\n";
	}
	ficheroSalida.close();

}

