
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

/*
 * Método que traza el rayo principal desde la cámara a través de cada
 * uno de los pixeles.
 */
void trazador(){

	//Establecemos los límites del plano.
	float izquierdo = camara[0]-anchura/2;
	float derecho = camara[0]+anchura/2;
	float arriba = camara[1]+altura/2;
	float abajo = camara[1]-altura/2;
	float R, G, B;
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
			direccion = direccion / direccion.modulo();	// Normalizamos con el modulo.
			Rayo ray = Rayo(&punto,&direccion);	// Creamos el rayo.
			trazarRayos(ray,0,R,G,B);	// Trazamos el rayo.
			escribirColor(R, G, B, j);
		}
	}
}

/*
 * Método que comprueba si el rayo interseca con algún objeto y lanza
 * llama al método correspondiente para calcular color si encuentra
 * alguna esfera.
 */
void trazarRayos(Rayo ray, int rebote, float &R, float &G, float &B){

	//if(rebote != 5){
		// Definimos las variables.
		float distInterseccion = infinito; Esfera esfCercana; VectorT intersecta;
		// Creamos el iterador para recorrer la lista.
		list<Esfera>::iterator esfera = objetos.begin();
		float nuevoIndice = -1;

		while(esfera != objetos.end()){	// Recorremos los objetos para saber intersecciones.
			Esfera esfActual = *esfera;	// Sacamos la esfera actual.
			// Se calcula la distancia de intersección.
			intersecta = interseccion(ray, esfActual);
			// Se comprueba si es la esfera más cercana.
			if(intersecta.getLon() > 0 && (intersecta.getValPos(0) > distancia || rebote > 0)
					&& intersecta.getValPos(0) < distInterseccion
					&& intersecta.getValPos(0) > 0){
				// Comparamos para obtener el objeto con distancia mínima.
				distInterseccion = intersecta.getValPos(0);
				// Se guarda el objeto con el que ha intersectado.
				esfCercana = esfActual;
				nuevoIndice = esfActual.getIor();
			} else if(intersecta.getLon() > 1 &&		// Se mira si se está saliendo de una transparente.
					esfActual.getMaterial() == TRANSPARENTE &&
					intersecta.getValPos(1) > 0 &&
					intersecta.getValPos(1) < distInterseccion) {
				// Se obtiene la distancia de intersección.
				distInterseccion = intersecta.getValPos(1);
				// Se guarda el objeto con el que ha intersectado.
				esfCercana = esfActual;
				nuevoIndice = IRefAnterior;	// El índice de refracción es el anterior.
			}
			*esfera++;	// Se pasa a la siguiente esfera de la lista.
		}

		if(distInterseccion != infinito){	// Si ha intersecado se calcula color.
			//Se calcula el punto con el que se intersecta.
			VectorT puntoIntersectado = ray.getPunto() +
					(ray.getDireccion() * distInterseccion);
			VectorT normal = puntoIntersectado - esfCercana.getCentro(); // Se calcula la normal al punto.
			normal = normal / normal.modulo();	// Se normaliza.
			// Se modifica el punto de intersecci�n por errores de precisi�n.
			float bias = 0.01;
			VectorT puntoOrigen = puntoIntersectado + (normal*bias);
			VectorT luz;
			//Si el objeto es reflectante se obtiene el color reflejado.
			if(esfCercana.getMaterial() == REFLECTANTE) {
				reflection(ray.getDireccion(), rebote,normal, puntoOrigen, R, G, B);
				float RGB[3] = {R, G, B};
				VectorT color = VectorT(RGB, 3);	//Se inicializa color.
				luz = trazarRayosSombra(ray, puntoOrigen, normal, color, esfCercana);
			} else if(esfCercana.getMaterial() == TRANSPARENTE) {
				//Al ser transparente se usara puntoIntersectado en lugar de puntoOrigen.
				refraction(ray.getDireccion(), rebote, normal,
						puntoIntersectado,esfCercana, nuevoIndice, R, G, B);
				float RGB[3] = {R, G, B};
				VectorT color = VectorT(RGB, 3);	//Se inicializa color.
				luz = trazarRayosSombra(ray, puntoOrigen, normal, color, esfCercana);
			} else {
				//Si es phong o lambertiana no se calcula ningun color inicial(sera el de la
				//propia esfera).
				float RGB[3] = {0, 0, 0};
				VectorT color = VectorT(RGB, 3);
				luz = trazarRayosSombra(ray, puntoOrigen, normal, color, esfCercana);
			}
			R = luz.getValPos(0);
			G = luz.getValPos(1);
			B = luz.getValPos(2);
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
		} else{		// Si no ha intersectado se pone color de fondo.
			R = 0;
			G = 0;
			B = 0;
		}
		// Añadir contribución color.
		//trazarRayos(ray,rebote+1);
	/*} else{
		// Pintar color.

	}*/
}


/*
 * Método que traza rayos de sombra y calcula el color.
 */
VectorT trazarRayosSombra(Rayo ray, VectorT puntoIntersectado, VectorT normal, VectorT color,
		Esfera esfIntersectada) {

	// Se declara la luz total inicial.
	float inicial[3] = {0,0,0};
	VectorT luzTotal = VectorT(inicial,3);

	//Se crea el iterador para recorrer fuentes de luz.
	list<Fuente>::iterator fuente = fuentesLuz.begin();

	while(fuente != fuentesLuz.end()){	// Se recorren las fuentes.
		Fuente fuenteActual = *fuente;	// Se obtiene la primera fuente.
		//Se obtiene la dirección del rayo sombra.
		VectorT dirRSombra = fuenteActual.getPunto() - puntoIntersectado;
		dirRSombra = dirRSombra / dirRSombra.modulo();	// Se normaliza.
		Rayo rayoSombra = Rayo(&puntoIntersectado, &dirRSombra);	// Se crea el rayo.

		// Iterador para recorres los objetos de la escena.
		list<Esfera>::iterator esfera = objetos.begin();
		VectorT intersecta;
		// Recorremos los objetos para saber intersecciones.
		while(esfera != objetos.end()){
			Esfera esfActual = *esfera;	// Obtenemos la esfera actual.
			// Se calcula la distancia de intersección.
			intersecta = interseccion(rayoSombra, esfActual);
			// Se comprueba si está entre el foco y la esfera.
			if(intersecta.getValPos(0) >= 0){
				// Si es transparente, la luz pasara.
				if(esfActual.getMaterial() == TRANSPARENTE) {
					intersecta.setValPos(-1,0);	// Si es transparente, se indica.
				} else {
					break;		// Si está entre el foco y la esfera, hay sombra.
				}
			}
			*esfera++;	// Se pasa a la siguiente esfera.
		}

		if(intersecta.getValPos(0) < 0) {	// Se comprueba si ha intersectado.
			// Se obtiene el factor de incidencia de la luz.
			float cos = dirRSombra.prodEscalar(normal);
			if(cos < 0) {	//Si es menor que 0, se iguala a 0.
				cos = 0;
			}
			// Se obtiene la distancia a la fuente de luz.
			float distanciaFuente = (fuenteActual.getPunto() - puntoIntersectado).modulo();
			// Se obtiene la potencia de la luz que incide en el punto.
			float luzIncidente = fuenteActual.getPotencia()
					/(distanciaFuente*distanciaFuente);

			if(esfIntersectada.getMaterial() == PHONG) {	// Si es phong, se calcula la luz.
				// Se calcula como incide la luz mediante la BDRF de Phong.
				color = phong(rayoSombra, normal,
						ray.getPunto()-puntoIntersectado,esfIntersectada,true);
			} else if(esfIntersectada.getMaterial() == LAMBERTIANO){	// Si es lambertiana...
				// Se calcula como incide la luz mediante la BDRF de Phong.
				color = phong(rayoSombra, normal,
						ray.getPunto()-puntoIntersectado,esfIntersectada,false);
			}
			// Se obtiene la luz total del punto.
			luzTotal = luzTotal+(color*cos*luzIncidente);
		}
		*fuente++;		// Se pasa a la siguiente fuente de luz.
	}

	return luzTotal;
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
 * de segundo grado para la intersección rayo-esfera.
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
	ifstream ficheroEntrada; char linea[256]; string objeto;

	// Leemos línea por línea el fichero.
	ficheroEntrada.open(escena);
	while(ficheroEntrada.getline(linea,256)){
		objeto = strtok(linea,"*");
		if(objeto=="Esfera"){	// Si es esfera...
			// Declaramos variables.
			float *centro = new float[3]; float *color = new float[3];
			float radio;
			// Leemos centro.
			centro[0] = stof(strtok(NULL,"*"));
			centro[1] = stof(strtok(NULL,"*"));
			centro[2] = stof(strtok(NULL,"*"));
			radio = stof(strtok(NULL,"*"));		// Leemos radio.
			// Leemos color.
			color[0] = stof(strtok(NULL,"*"));
			color[1] = stof(strtok(NULL,"*"));
			color[2] = stof(strtok(NULL,"*"));
			int material = stof(strtok(NULL,"*"));	// Leemos material.
			float ior = 1;	// Declaramos el coeficiente.
			if(material == TRANSPARENTE) {
				//Si es transparente se indica el índice
				//de refracción del material del interior.
				ior = stof(strtok(NULL,"*"));
			}
			// Creamos la esfera y la introducimos en la lista.
			Esfera esfera = Esfera(VectorT(centro,3),radio,VectorT(color,3),material,ior);
			objetos.push_back(esfera);
		} else if(objeto=="Triangulo"){	// Si es triángulo...

		} else if(objeto=="Luz") {	// Si es foco de luz...
			// Declaramos las variables.
			float *punto = new float[3]; float potencia;
			// Leemos punto.
			punto[0] = stof(strtok(NULL,"*"));
			punto[1] = stof(strtok(NULL,"*"));
			punto[2] = stof(strtok(NULL,"*"));
			potencia = stof(strtok(NULL,"*"));	// Leemos potencia.
			// Creamos la fuente y la introducimos en la lista.
			Fuente fuente = Fuente(VectorT(punto,3), potencia);
			fuentesLuz.push_back(fuente);
		} else{	// Si es la cabecera.
			// Leemos el tamaño del pixel, la altura y anchura del plano.
			tamPixel = stof(objeto);
			altura = stof(strtok(NULL,"*"));
			anchura = stof(strtok(NULL,"*"));
			// Leemos las coordenadas de la cámara.
			camara[0] = stof(strtok(NULL,"*"));
			camara[1] = stof(strtok(NULL,"*"));
			camara[2] = stof(strtok(NULL,"*"));
			// Calculamos la distancia del plano al observador.
			distancia = anchura*2;
		}
	}

	ficheroEntrada.close(); // Cerramos el fichero de entrada.
}

/*
 * Función que escribe en el fichero el color del pixel.
 */
void escribirColor(float R, float G, float B, int columna){

	// Escribimos el color del píxel.
	ficheroSalida << (int)R << " " << (int)G << " " << (int)B <<" ";
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

/*
 * Calcula la BDRF de Phong en función de las características del material intersectado.
 */
VectorT phong(Rayo rayoSombra, VectorT normal, VectorT direccionV, Esfera esfera, bool especular) {
	VectorT difusa = esfera.getKd()/PI;	// Se calcula la parte difusa.
	if(especular){
		// Se obtiene Wr.
		VectorT Wr = rayoSombra.getDireccion() - (rayoSombra.getDireccion()-normal*
				(rayoSombra.getDireccion().prodEscalar(normal)))*2;
		direccionV = direccionV/direccionV.modulo();	// Se normaliza el vector dirección de la cámara.
		float prod = direccionV.prodEscalar(Wr);	// Producto entre dirección y Wr.
		if(prod < 0) {	//Se obtiene su valor absoluto.
			prod = -prod;
		}
		//Se obtiene la especular.
		float especular = (esfera.getKs()*((esfera.getAlpha()+2)/(2*PI)))*pow(
				prod,esfera.getAlpha());
		// Se suman ambas partes.
		difusa.setValPos(difusa.getValPos(0)+especular,0);
		difusa.setValPos(difusa.getValPos(1)+especular,1);
		difusa.setValPos(difusa.getValPos(2)+especular,2);
	}
	return difusa;	// Se devuelve el resultado.
}

/*
 * Método que devuelve el color reflejado.
 */
void reflection(VectorT camara, int rebote, VectorT normal, VectorT punto
		, float &R, float &G, float &B) {
	float cos = normal.prodEscalar(camara);
	VectorT reflejo = camara - normal*cos*2;
	trazarRayos(Rayo(&punto,&reflejo), rebote+1, R, G, B);
}

/*
 * Método que devuelve el color refractado.
 */
void refraction(VectorT direccionRayo, int rebote, VectorT normal, VectorT punto,
		Esfera esfera, float nuevoIndice, float &R, float &G, float &B) {
	float factor = IRefraccion/nuevoIndice;
	float cos = normal.prodEscalar(direccionRayo);
	VectorT direccion = (direccionRayo + normal*cos)*factor -
			normal*(sqrt(1 - factor*factor*(1 - cos*cos)));
	float aux = IRefraccion;
	IRefAnterior = IRefraccion;
	IRefraccion = nuevoIndice;
	trazarRayos(Rayo(&punto,&direccion), rebote+1, R, G, B);
	IRefraccion = aux;
}
