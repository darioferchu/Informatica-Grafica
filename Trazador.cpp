
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
	return 0;
}

void trazador(){

	//Establecemos los límites del plano.
	float izquierdo = camara[0]-anchura/2;
	float derecho = camara[0]+anchura/2;
	float arriba = camara[1]+altura/2;
	float abajo = camara[1]-altura/2;
	// Recorremos anchura y altura del mapa pixeles.
	for(float i=arriba-tamPixel/2; i>abajo; i=i-tamPixel){
		for(float j=izquierdo+tamPixel/2; j<derecho; j=j+tamPixel){
			// Creamos rayo primario.
			float direccionRayo[3];
			direccionRayo[0] = j-camara[0];
			direccionRayo[1] = i-camara[1];
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
}

void trazarRayos(Rayo ray, int rebote, int columna){

	//if(rebote != 5){
		// Definimos la distancia inicial de intersección.
		float distInterseccion = infinito;
		// Definimos el objeto más cercano.
		Esfera esfCercana;
		// Creamos el iterador para recorrer la lista.
		list<Esfera>::iterator esfera = objetos.begin();
		VectorT intersecta;
		// Recorremos los objetos para saber intersecciones.
		while(esfera != objetos.end()){
			Esfera esfActual = *esfera;
			// Se calcula la distancia de intersección.
			intersecta = interseccion(ray, esfActual);
			// Se comprueba si es la esfera más cercana.
			if(intersecta.getLon() > 0 && intersecta.getValPos(0) > distancia
					&& intersecta.getValPos(0) < distInterseccion){
				// comparamos para obtener el objeto con distancia mínima.
				distInterseccion = intersecta.getValPos(0);
				// Se guarda el objeto con el que ha intersectado.
				esfCercana = esfActual;
			}
			*esfera++;
		}
		if(distInterseccion != infinito){
			trazarRayosSombra(ray, distInterseccion, columna,esfCercana);
		} else{
			escribirColor(0,0,0,columna);
		}
		// Añadir contribución color.
		//trazarRayos(ray,rebote+1);
	/*} else{
		// Pintar color.

	}*/
}



void trazarRayosSombra(Rayo ray, float distInterseccion, int columna, Esfera origen) {
	//Se calcula el punto con el que se intersecta.
	VectorT puntoIntersectado = ray.getPunto() +
			(ray.getDireccion() * distInterseccion);
	VectorT normal = puntoIntersectado - origen.getCentro();
	normal = normal / normal.modulo();
	float bias = 0.01;
	//Se crea el iterador para recorrer fuentes de luz.
	list<Fuente>::iterator fuente = fuentesLuz.begin();
	bool sombra = true;
	VectorT puntoOrigen = puntoIntersectado + (normal*bias);
	// Recorremos luces si intersecta.
	float luzTotal = 0.0;
	while(fuente != fuentesLuz.end()){
		Fuente fuenteActual = *fuente;
		//Se obtiene la direcci�n del rayo sombra.
		VectorT dirRSombra = fuenteActual.getPunto() - puntoOrigen;
		dirRSombra = dirRSombra / dirRSombra.modulo();
		Rayo rayoSombra = Rayo(&puntoOrigen, &dirRSombra);
		list<Esfera>::iterator esfera = objetos.begin();
		VectorT intersecta;
		// Recorremos los objetos para saber intersecciones.
		while(esfera != objetos.end()){
			Esfera esfActual = *esfera;
			// Se calcula la distancia de intersección.
			intersecta = interseccion(rayoSombra, esfActual);
			// Se comprueba si es la esfera más cercana.
			if(intersecta.getValPos(0) >= 0){
				//Calcular colores
				break;
			}
			*esfera++;
		}
		if(intersecta.getValPos(0) < 0) {
			sombra = false;
			//Se obtiene el factor de incidencia de la luz.
			float cos = dirRSombra.prodEscalar(normal);
			if(cos < 0) {	//Si es menor que 0, se iguala a 0.
				cos = 0;
			}
			luzTotal += cos*fuenteActual.getPotencia();
		}
		*fuente++;
	}
	if(sombra) {
		escribirColor(0, 0, 0, columna);
	} else {
		//Se obtiene el color en el punto intersectado.
		int R = origen.getColor().getValPos(0)*luzTotal;
		int G = origen.getColor().getValPos(1)*luzTotal;
		int B = origen.getColor().getValPos(2)*luzTotal;

		//Si sobrepasa el maximo se iguala a 255.
		if(R > 255) {
			R = 255;
		}
		if(G > 255) {
			G = 255;
		}
		if(B > 255) {
			B = 255;
		}

		escribirColor(R, G, B, columna);
	}
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
			float sol[] = {-b/(2*a)};
			return VectorT(sol,1);
		} else {
			float raiz = sqrt(delta);
			float sol[] = {(-b-raiz)/(2*a), (-b+raiz)/(2*a)};
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
			// Declaramos variables.
			float *centro = new float[3];
			float *color = new float[3];
			float radio;
			// Leemos datos.
			centro[0] = stof(strtok(NULL,"*"));
			centro[1] = stof(strtok(NULL,"*"));
			centro[2] = stof(strtok(NULL,"*"));
			radio = stof(strtok(NULL,"*"));
			color[0] = stof(strtok(NULL,"*"));
			color[1] = stof(strtok(NULL,"*"));
			color[2] = stof(strtok(NULL,"*"));
			// Creamos la esfera y la introducimos en la lista.
			Esfera esfera = Esfera(VectorT(centro,3),radio,VectorT(color,3));
			objetos.push_back(esfera);
		} else if(objeto=="Triangulo"){	// Si es triángulo...

		} else if(objeto=="Luz") {

			float *punto = new float[3];
			float potencia;
			// Leemos datos.
			punto[0] = stof(strtok(NULL,"*"));
			punto[1] = stof(strtok(NULL,"*"));
			punto[2] = stof(strtok(NULL,"*"));
			potencia = stof(strtok(NULL,"*"));
			Fuente fuente = Fuente(VectorT(punto,3), potencia);
			fuentesLuz.push_back(fuente);
		} else{	// Si es la cabecera.
			// Leemos la altura y anchura del plano.
			tamPixel = stof(objeto);
			altura = stof(strtok(NULL,"*"));
			anchura = stof(strtok(NULL,"*"));
			// Leemos las coordenadas de la cámara.
			camara[0] = stof(strtok(NULL,"*"));
			camara[1] = stof(strtok(NULL,"*"));
			camara[2] = stof(strtok(NULL,"*"));
			// Calculamos la distancia.
			distancia = anchura*2;
		}
	}

	ficheroEntrada.close(); // Cerramos el fichero de entrada.
}

/*
 * Función que escribe en el fichero el color del pixel.
 */
void escribirColor(int R, int G, int B, int columna){

	// Escribimos el color del píxel.
	ficheroSalida << R << " " << G << " " << B <<" ";
	// Se escribe salto de línea al acabar una fila.
	if(columna-anchura==0){
		ficheroSalida << "\n";
	}
}

/*
 * Función que escribe la cabecera del fichero de salida.
 */
void escribirCabecera(){

	// Escribimos los datos de la cabecera del fichero.
	ficheroSalida << "P3\n";
	ficheroSalida << "# Escena\n";
	ficheroSalida << anchura/tamPixel << " " << altura/tamPixel << "\n";
	ficheroSalida << "255\n";
}
