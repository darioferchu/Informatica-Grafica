#include <math.h>
#include "Matriz.h"
#include "Rayo.h"
#include "Esfera.h"

#define infinito 99999
#define altura 500
#define anchura 500
#define distancia 50

const float camara[] = {0.0, 0.0, 0.0};
const float esferaCoor[] = {255.0, 255.0, 100.0};

int trazador();
int trazarRayos(Rayo, int);
Vector inteseccion(Rayo, Esfera);
Vector resolverSegundoGrado(float,float,float);
