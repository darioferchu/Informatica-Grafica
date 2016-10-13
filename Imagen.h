/*
 * Imagen.h
 *
 *  Created on: 13 oct. 2016
 *      Author: Jorge
 */


class Imagen {
public:
	Imagen(int, int);
	Imagen(int, int, int**);
	virtual ~Imagen();

	int getAltura();
	int getAncho();
	int getDatosFila();
	void setValorPos(int,int,int);

	void crearFichero(char* nombre);

private:
	int altura;
	int ancho;
	int numDatosFila;
	int **datos;
};
