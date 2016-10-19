
#include "Trazador.h"

/*
 * Método principal que inicializa el trazador de rayos y los
 * objetos a trazar.
 */
int main(){

	// Inicializamos el fichero de salida.
	ficheroSalida.open ("ficheroEscena.ppm");
	// Leemos el fichero.
	leerFichero();
	// Escribimos la cabecera del fichero de salida.
	escribirCabecera();
	// Iniciamos el trazador de rayos.
	trazador();
	// Cerramos el fichero.
	ficheroSalida.close();
	cout << "Probando4";
	return 0;
}

int trazador(){

	// Recorremos anchura y altura del mapa pixeles.
	for(int i=altura; i>0; i--){
		for(int j=0; j<anchura; j++){
			// Creamos rayo primario.
			float direccionRayo[3];
			direccionRayo[0] = i-camara[0];
			direccionRayo[1] = j-camara[1];
			direccionRayo[2] = distancia-camara[2];
			VectorT punto = VectorT(camara,3);
			VectorT direccion = VectorT(direccionRayo,3);
			direccion = direccion / direccion.modulo();
			/***************
			 * OJO que se lo estamos mandando con dirección.
			 */
			Rayo ray = Rayo(&punto,&direccion);
			trazarRayos(ray,0,j);

		}
	}
	return 0;
}

void trazarRayos(Rayo ray, int rebote, int columna){
	
	//if(rebote != 5){
		// Definimos la distancia inicial de intersección.
		float distInterseccion = infinito;
		// Definimos el objeto más cercano.
		Esfera esfCercana;
		// Creamos el iterador para recorrer la lista.
		list<Esfera>::iterator esfera = objetos.begin();
		// Recorremos los objetos para saber intersecciones.
		while(esfera != objetos.end()){
			Esfera esfActual = *esfera;
			VectorT intersecta = interseccion(ray, esfActual);
			if(intersecta.getLon()>0 && intersecta.getValPos(0) < distInterseccion){
				cout << "Intersecta\n";
				// comparamos para obtener el objeto con distancia mínima.
				distInterseccion = intersecta.getValPos(0);
				// Se guarda el objeto con el que ha intersectado.
				esfCercana = esfActual;
			}
			*esfera++;
		}
		if(distInterseccion != infinito){
			escribirColor(esfCercana.getColor().getValPos(0),
					esfCercana.getColor().getValPos(1),esfCercana.getColor().getValPos(2),
					columna);

			// Calculamos rayo sombra

			// Recorremos luces si intersecta.
			//for(int k=0; k<luces.size(); k++){
				//if(intersecta){
					// le da la sombra y se sale del bucle.
				//}
			//}
		} else{
			escribirColor(0,0,0,columna);
		}
		// Añadir contribución color.
		//trazarRayos(ray,rebote+1);
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
			float sol[] = {-infinito};
			return VectorT(sol,0);
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
void leerFichero(){

	// Declaramos los datos para trabajar con el fichero.
	ifstream ficheroEntrada;
	char linea[256];
	string objeto;

	// Leemos línea por línea el fichero.
	ficheroEntrada.open(escena);
	while(ficheroEntrada.getline(linea,256)){
		objeto = strtok(linea,"*");
		if(objeto=="Esfera"){	// Si es esfera...
			cout << objeto << "probando2\n";
			// Declaramos variables.
			float centro[3], color[3]; float radio;
			// Leemos datos.
			centro[0] = atof(strtok(NULL,"*"));
			centro[1] = atof(strtok(NULL,"*"));
			centro[2] = atof(strtok(NULL,"*"));
			radio = atof(strtok(NULL,"*"));
			cout << "probando3\n";
			color[0] = atof(strtok(NULL,"*"));
			color[1] = atof(strtok(NULL,"*"));
			color[2] = atof(strtok(NULL,"*"));
			// Creamos la esfera y la introducimos en la lista.
			Esfera esfera = Esfera(VectorT(centro,3),radio,VectorT(color,3));
			objetos.push_back(esfera);
		} else if(objeto=="Triangulo"){	// Si es triángulo...

		} else{	// Si es la cabecera.
			cout << objeto << "probando1\n";
			// Leemos la altura, anchura y distancia al plano.
			altura = stoi(objeto);
			anchura = stoi(strtok(NULL,"*"));
			distancia = atof(strtok(NULL,"*"));
		}
	}

	ficheroEntrada.close(); // Cerramos el fichero de entrada.
}

/*
 * Función que escribe en el fichero el color del pixel.
 */
void escribirColor(float R, float G, float B, int columna){

	ficheroSalida << R << " " << G << " " << B <<" ";
	if(columna%30==0){
		ficheroSalida << "\n";
	}
}

/*
 * Función que escribe la cabecera del fichero de salida.
 */
void escribirCabecera(){
	ficheroSalida << "P3\n";
	ficheroSalida << "# Escena\n";
	ficheroSalida << anchura << " " << altura << "\n";
	ficheroSalida << "255\n";
}
