
#include <iostream>
#include <fstream>
using namespace std;

class Imagen {
public:
	Imagen(int, int);
	Imagen(int, int, int*);
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
	int *datos[];
};
