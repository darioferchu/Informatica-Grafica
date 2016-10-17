
#include "Trazador.h"

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
			float direccionRayo[3];
			direccionRayo[0] = i-camara[0];
			direccionRayo[1] = j-camara[1];
			direccionRayo[2] = distancia-camara[2];
			VectorT punto = VectorT(camara,3);
			VectorT direccion = VectorT(direccionRayo,3);
			Rayo ray = Rayo(&punto,&direccion);
			trazarRayos(ray,0);

		}
	}
	return 0;
}

int trazarRayos(Rayo ray, int rebote){
	
	//if(rebote != 5){
		// Definimos la distancia inicial de intersección.
		float distInterseccion = infinito;
		// Definimos el objeto más cercano.
		Esfera esfCercana;
		// Recorremos los objetos para saber intersecciones.
		//for(int k=0; k<esferas.size(); k++){
			//Esfera esfera = esferas.get(k);
			VectorT esferaCoo = VectorT(esferaCoor,3);
			Esfera esfera = Esfera(esferaCoo,3.0);
			VectorT intersecta = interseccion(ray, esfera);
			if(intersecta.getLon()>0 && intersecta.getValPos(0) < distInterseccion){
				// comparamos para obtener el objeto con distancia mínima.
				distInterseccion = intersecta;
				// Se guarda el objeto con el que ha intersectado.
				esfCercana = esfera;
			}
		//}
		if(distInterseccion != infinito){
			// Calculamos rayo sombra

			// Recorremos luces si intersecta.
			//for(int k=0; k<luces.size(); k++){
				//if(intersecta){
					// le da la sombra y se sale del bucle.
				//}
			//}
		} else{

		}
		// Añadir contribución color.
		trazarRayos(ray,rebote+1);
	/*} else{
		// Pintar color.

	}*/
}

/*
 * Función que calcula si un cierto rayo intersecta con una esféra.
 */
VectorT interseccion(Rayo ray, Esfera esfera) {
		float a = 1.0;
		VectorT OC = ray.getPunto() - esfera.getCentro();
		float b = 2.0*(ray.getDireccion().prodEscalar(OC));
		float c = OC.prodEscalar(OC) - pow(esfera.getRadio(),2);

		return resolverSegundoGrado(a,b,c);
}

/*
 * Función que calcula la solución o soluciones de una cierta ecuación
 * de segundo grado.
 */
VectorT resolverSegundoGrado(float a,float b, float c) {
		float delta = pow(b,2) - 4*a*c;
		if (delta<0.0) {
			return VectorT({},0);
		} else if(delta == 0.0) {
			float sol[] = {-b/(2.0*a)};
			return VectorT(sol,1);
		} else {
			float raiz = sqrt(delta);
			float sol[] = {(-b+raiz)/(2.0*a),(-b-raiz)/(2.0*a)};
			return VectorT(sol,2);
		}
}

/*
 * Función que lee desde un fichero los datos de la escena.
 */
int leerFichero(){

	// Declaramos los datos para trabajar con el fichero.
	ifstream ficheroEntrada;
	char linea[256];
	string objeto;

	// Leemos línea por línea el fichero.
	ficheroEntrada.open(escena);
	while(ficheroEntrada.getline(linea,256)){
		objeto = strtok(linea,"-");
		if(objeto.compare("Esfera")){	// Si es esfera...
			// Declaramos variables.
			float centro[3]; float radio;
			// Leemos datos.
			centro[0] = atof(strtok(NULL,"-"));
			centro[1] = atof(strtok(NULL,"-"));
			centro[2] = atof(strtok(NULL,"-"));
			radio = atof(strtok(NULL,"-"));
		} else{	// Si es triángulo...

		}
	}

	ficheroEntrada.close(); // Cerramos el fichero de entrada.
	return 0;
}
