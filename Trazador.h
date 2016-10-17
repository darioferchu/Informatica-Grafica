#include <math.h>
#include "Rayo.h"
#include "Esfera.h"
#include <iostream>
#include <fstream>
using namespace std;

#define infinito 99999
#define altura 500
#define anchura 500
#define distancia 50
#define escena "escena.txt"

float camara[] = {0.0, 0.0, 0.0};
float esferaCoor[] = {255.0, 255.0, 100.0};

int trazador();
void trazarRayos(Rayo, int);
VectorT interseccion(Rayo, Esfera);
VectorT resolverSegundoGrado(float,float,float);
int leerFichero();
