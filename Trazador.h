#include <math.h>
#include "Rayo.h"
#include "Esfera.h"
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <list>
using namespace std;

#define infinito 99999
#define escena "escena.txt"

float camara[] = {0.0, 0.0, 0.0};
float esferaCoor[] = {255.0, 255.0, 100.0};
float anchura = 0.0;
float altura = 0.0;
float distancia = 0.0;
ofstream ficheroSalida;
list<Esfera> objetos;

int trazador();
void trazarRayos(Rayo, int, int);
VectorT interseccion(Rayo, Esfera);
VectorT resolverSegundoGrado(float,float,float);
void leerFichero();
void escribirColor(float,float,float, int);
