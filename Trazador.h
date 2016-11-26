#include <math.h>
#include "Rayo.h"
#include "Esfera.h"
#include "Fuente.h"
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <list>
using namespace std;

/*
 * Definiciones de valores de variables.
 */
#define infinito 99999
#define escena "escena.txt"
#define PI 3.14159265
enum {DIFUSO = 0, REFLECTANTE = 1, TRANSPARENTE = 2};

/*
 * Variables globales.
 */
float camara[] = {0.0, 0.0, 0.0};
float esferaCoor[] = {255.0, 255.0, 100.0};
float anchura = 0.0;
float altura = 0.0;
float distancia = 0.0;
float tamPixel = 0.0;
float IRefraccion = 1;
float IRefAnterior = 1;
ofstream ficheroSalida;
list<Esfera> objetos;
list<Fuente> fuentesLuz;

/*
 * Métodos del trazador.
 */
void trazador();
void trazarRayos(Rayo, int, int);
void calcularColor(Rayo, float, int, Esfera);
VectorT interseccion(Rayo, Esfera);
VectorT resolverSegundoGrado(float,float,float);
void leerFichero();
void escribirColor(float,float,float, int);
void escribirCabecera();
VectorT phong(Rayo, VectorT, VectorT, Esfera);
VectorT reflection(VectorT , VectorT, VectorT);
VectorT refraction(VectorT, VectorT, VectorT, Esfera,float);
VectorT objetosIntersectados(Rayo);
VectorT trazarRayosSombra(Rayo, Esfera, float, float);
