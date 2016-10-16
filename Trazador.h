#include <math.h>

#define infinito 99999
#define altura 500
#define anchura 500

int trazador();
int trazarRayos(Rayo, int);
Vector inteseccion(Rayo, Esfera);
Vector resolverSegundoGrado(float,float,float);
