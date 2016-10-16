
#include "trazador.h"

/*
 * Método principal que inicializa el trazador de rayos y los
 * objetos a trazar.
 */
int main(){

	// Declaramos objetos y fuentes de luz.

	// Iniciamos el trazador de rayos.
	trazador();
	return 0;
}

int trazador(){
	// Recorremos anchura y altura del mapa pixeles.
	for(int i=0; i<altura; i++){
		for(int j=0; j<anchura; j++){
			// Creamos rayo primario.
			float puntoRayo[3] = {1.0,2.0,3.0}:
			float direccionRayo[3] = {1.0,2.0,3.0}:
			Vector punto = Vector(puntoRayo,3);
			Vector direccion = Vector(direccionRayo,3);
			Rayo ray = Rayo(punto,direccion);
			trazarRayos(ray,0);

		}
	}
	return 0;
}

int trazarRayos(Rayo ray, int rebote){
	
	if(rebote != 5){
		// Definimos la distancia inicial de intersección.
		float distInterseccion = infinito;
		// Definimos el objeto más cercano.
		Esfera esfCercana;
		// Recorremos los objetos para saber intersecciones.
		for(int k=0; k<esferas.size(); k++){
			Esfera esfera = esferas.get(k);
			Vector intersecta = Interseccion(ray, esfera);
			if(intersecta.getLon()>0 && intersecta.getValPos(0) < distInterseccion){
				// comparamos para obtener el objeto con distancia mínima.
				distInterseccion = intersecta;
				// Se guarda el objeto con el que ha intersectado.
				esfCercana = esfera;
			}
		}
		if(distInterseccion != infinito){
			// Calculamos rayo sombra

			// Recorremos luces si intersecta.
			for(int k=0; k<luces.size(); k++){
				if(intersecta){
					// le da la sombra y se sale del bucle.
				}
			}
		}
		// Añadir contribución color.
		trazarRayos(ray,rebote+1);
	} else{
		// Pintar color.

	}
}

/*
 * Función que calcula si un cierto rayo intersecta con una esféra.
 */
Vector Interseccion(Rayo ray, Esfera esfera) {
		float a = 1.0;
		Vector OC = ray.getPunto() - esfera.getCentro();
		float b = 2.0*(ray.getDireccion().prodEscalar(OC));
		float c = OC.prodEscalar(OC) - pow(esfera.getRadio(),2);

		return resolverSegundoGrado(a,b,c);
}

/*
 * Función que calcula la solución o soluciones de una cierta ecuación
 * de segundo grado.
 */
Vector resolverSegundoGrado(float a,float b, float c) {
		float delta = pow(b,2) - 4*a*c;
		if (delta<0.0) {
			return Vector({},0);
		} else if(delta == 0.0) {
			return Vector({-b/(2.0*a)},1);
		} else {
			float raiz = sqrt(delta);
			return Vector({(-b+raiz)/(2.0*a),(-b-raiz)/(2.0*a)},2);
		}
}
