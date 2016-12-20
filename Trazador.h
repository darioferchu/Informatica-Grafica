#include <math.h>
#include "Rayo.h"
#include "Esfera.h"
#include "Fuente.h"
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <list>
#include <random>
using namespace std;

default_random_engine generator;
uniform_real_distribution<float> distribution(0.0,1.0);
/*
 * Definiciones de valores de variables.
 */
#define infinito 99999
#define escena "escena.txt"
#define PI 3.14159265
enum {PHONG = 0, REFLECTANTE = 1, TRANSPARENTE = 2, LAMBERTIANO = 3};

/*
 * Variables globales.
 */
float camara[] = {0.0, 0.0, 0.0};		// Posición de la cámara.
float esferaCoor[] = {255.0, 255.0, 100.0};
float **buffer;
float anchura = 0.0;	// Anchura del plano.
float altura = 0.0;		// Altura del plano.
float distancia = 0.0;	// Distancia entre el observador y el plano.
float tamPixel = 0.0;	// Tamaño del pixel.
float IRefraccion = 1;
float IRefAnterior = 1;
float RUltimo = 0, GUltimo = 0, BUltimo = 0;
int rayosIndirecta = 16; 	// Número de rayos de luz indirecta.
int numEscritos = 0;	// Número de pixeles escritos.
ofstream ficheroSalida;	// Fichero de salida.
list<Esfera> objetos;	// Lista de objetos de la escena.
list<Fuente> fuentesLuz;	// Lista de las fuentes de luz de la escena.

/*
 * Métodos del trazador.
 */
void trazador();
void trazarRayos(Rayo, int, float&, float&, float&,bool);
VectorT interseccion(Rayo, Esfera);
VectorT resolverSegundoGrado(float,float,float);
void leerFichero();
void escribirColor();
void escribirCabecera();
VectorT phong(Rayo, VectorT, VectorT, Esfera, bool);
void reflection(VectorT, int, VectorT, VectorT, float&, float&, float&);
void refraction(VectorT, int, VectorT, VectorT, Esfera,float, float&, float&, float&);
VectorT objetosIntersectados(Rayo);
VectorT trazarRayosSombra(Rayo, VectorT, VectorT, Esfera);
VectorT indirectLight(VectorT, VectorT, Esfera, VectorT,int);
Matriz sistemaCoordenadas(VectorT);
Matriz uniformeSemiesfera(float, float);
