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
	VectorT punto = VectorT(camara,3);
	// Recorremos anchura y altura del mapa pixeles.
	for(float i=arriba-tamPixel/2; i>abajo; i=i-tamPixel){
		for(float j=izquierdo+tamPixel/2; j<derecho; j=j+tamPixel){
			// Creamos rayo primario.
			float direccionRayo[3];
			direccionRayo[0] = j-camara[0];
			direccionRayo[1] = i-camara[1];
			direccionRayo[2] = distancia-camara[2];
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
VectorT trazarRayos(Rayo ray, int rebote, float &R, float &G, float &B){
	VectorT puntoOrigen;
	float distInterseccion = infinito;
	if(rebote != 5){
		// Definimos las variables.
		Esfera esfCercana; VectorT intersecta;
		// Creamos el iterador para recorrer la lista.
		list<Esfera>::iterator esfera = objetos.begin();
		float nuevoIndice = -1;
		bool salida = false;
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
			} else if(intersecta.getLon() > 1 &&
					// Se mira si se está saliendo de una transparente.
					esfActual.getMaterial() == TRANSPARENTE &&
					intersecta.getValPos(1) > 0 &&
					intersecta.getValPos(1) < distInterseccion) {
				// Se obtiene la distancia de intersección.
				distInterseccion = intersecta.getValPos(1);
				// Se guarda el objeto con el que ha intersectado.
				esfCercana = esfActual;
				nuevoIndice = IRefAnterior;	// El índice de refracción es el anterior.
				salida = true;
			}
			*esfera++;	// Se pasa a la siguiente esfera de la lista.
		}

		if(distInterseccion != infinito){	// Si ha intersecado se calcula color.
			//Se calcula el punto con el que se intersecta.
			VectorT puntoIntersectado = ray.getPunto() +
					(ray.getDireccion() * distInterseccion);
			// Se calcula la normal al punto.
			VectorT normal = puntoIntersectado - esfCercana.getCentro();
			normal = normal / normal.modulo();	// Se normaliza.
			// Se modifica el punto de intersecci�n por errores de precisi�n.
			float bias = 0.0001;
			puntoOrigen = puntoIntersectado + (normal*bias);
			VectorT luz;
			//Si el objeto es reflectante se obtiene el color reflejado.
			if(esfCercana.getMaterial() == REFLECTANTE) {
				reflection(ray.getDireccion(), rebote,normal, puntoOrigen, R, G, B);
				float RGB[3] = {R, G, B};
				luz = VectorT(RGB, 3);	//Se inicializa color.
			} else if(esfCercana.getMaterial() == TRANSPARENTE) {
				//Al ser transparente se usara puntoIntersectado en lugar de puntoOrigen.
				if(salida) {
					refraction(ray.getDireccion(), rebote, normal,
							puntoOrigen,esfCercana, nuevoIndice, R, G, B);
				} else {
					refraction(ray.getDireccion(), rebote, normal,
							puntoIntersectado-(normal*bias),esfCercana, nuevoIndice, R, G, B);
				}
				float RGB[3] = {R, G, B};
				luz = VectorT(RGB, 3);	//Se inicializa color.
			} else {
				luz = trazarRayosSombra(ray, puntoOrigen, normal, esfCercana);
				if(rebote==0) {
					// Calcular luz indirecta.
					VectorT luzIndirecta = indirectLight(puntoOrigen, normal,esfCercana,
							ray.getDireccion());
					luz = luz+luzIndirecta;
				}
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
	}
	return puntoOrigen;
}


/*
 * Método que traza rayos de sombra y calcula el color.
 */
VectorT trazarRayosSombra(Rayo ray, VectorT puntoIntersectado, VectorT normal,
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
		// Se obtiene la distancia a la fuente de luz.
		float distanciaFuente = (fuenteActual.getPunto() - puntoIntersectado).modulo();
		bool sombra = false; //Indica si el punto es alcanzado por una fuente de luz.
		// Recorremos los objetos para saber intersecciones.
		while(esfera != objetos.end()){
			Esfera esfActual = *esfera;	// Obtenemos la esfera actual.
			// Se calcula la distancia de intersección.
			intersecta = interseccion(rayoSombra, esfActual);
			// Se comprueba si está entre el foco y la esfera.
			if(intersecta.getValPos(0) >= 0 && intersecta.getValPos(0)<distanciaFuente){
				// Si es transparente, la luz pasara.
				if(esfActual.getMaterial() != TRANSPARENTE) {
					// Si no es transparente, se indica.
					sombra = true;
					break;
				}
			}
			*esfera++;	// Se pasa a la siguiente esfera.
		}

		if(!sombra) {	// Se comprueba si ha intersectado.
			// Se obtiene el factor de incidencia de la luz.
			float cos = dirRSombra.prodEscalar(normal);
			if(cos < 0) {	//Si es menor que 0, se iguala a 0.
				cos = 0;
			}
			// Se obtiene la potencia de la luz que incide en el punto.
			float luzIncidente = fuenteActual.getPotencia()
					/(distanciaFuente*distanciaFuente);
			VectorT p;
			if(esfIntersectada.getMaterial() == PHONG) {	// Si es phong, se calcula la luz.
				// Se calcula como incide la luz mediante la BDRF de Phong.
				p = phong(rayoSombra, normal,
							ray.getPunto()-puntoIntersectado,esfIntersectada,true);
			} else if(esfIntersectada.getMaterial() == LAMBERTIANO){	// Si es lambertiana...
				// Se calcula como incide la luz mediante la BDRF de Phong.
				p = phong(rayoSombra, normal,
							ray.getPunto()-puntoIntersectado,esfIntersectada,false);
			}
			// Se obtiene la luz total del punto.
			luzTotal = luzTotal+(p*cos*luzIncidente);
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
			float radio, ks, alpha;
			// Leemos centro.
			centro[0] = stof(strtok(NULL,"*"));
			centro[1] = stof(strtok(NULL,"*"));
			centro[2] = stof(strtok(NULL,"*"));
			radio = stof(strtok(NULL,"*"));		// Leemos radio.
			int material = stof(strtok(NULL,"*"));	// Leemos material.
			float ior = 1;	// Declaramos el coeficiente.
			if(material == TRANSPARENTE) {
				//Si es transparente se indica el índice
				//de refracción del material del interior.
				ior = stof(strtok(NULL,"*"));
				// Creamos la esfera y la introducimos en la lista.
				Esfera esfera = Esfera(VectorT(centro,3),radio,VectorT(color,3),material,ior);
				objetos.push_back(esfera);
			}  else if(material == PHONG){
				// Leemos color.
				color[0] = stof(strtok(NULL,"*"));
				color[1] = stof(strtok(NULL,"*"));
				color[2] = stof(strtok(NULL,"*"));
				ks = stof(strtok(NULL,"*"));
				alpha = stof(strtok(NULL,"*"));
				// Creamos la esfera y la introducimos en la lista.
				Esfera esfera = Esfera(VectorT(centro,3),radio,VectorT(color,3),material,ior);
				esfera.setAlpha(alpha);
				esfera.setKs(ks);
				objetos.push_back(esfera);
			} else if(material == LAMBERTIANO) {
				// Leemos color.
				color[0] = stof(strtok(NULL,"*"));
				color[1] = stof(strtok(NULL,"*"));
				color[2] = stof(strtok(NULL,"*"));
				// Creamos la esfera y la introducimos en la lista.
				Esfera esfera = Esfera(VectorT(centro,3),radio,VectorT(color,3),material,ior);
				objetos.push_back(esfera);
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
	float factor;
	float aux = IRefraccion;
	float cos = normal.prodEscalar(direccionRayo);
	if(cos < 0) {
		cos = -cos;
		factor = IRefraccion/nuevoIndice;
		IRefAnterior = IRefraccion;
		IRefraccion = nuevoIndice;
	} else {		//Sale de la esfera.
		factor = IRefAnterior/IRefraccion;
		IRefraccion = IRefAnterior;
	}
	float c2 = 1 - factor*factor*(1 - cos*cos);
	VectorT direccion;
	if(c2 < 0) {
		direccion = direccionRayo;
	} else {
		direccion = (direccionRayo + normal*cos)*factor -
				normal*(sqrt(c2));
		direccion = direccion/direccion.modulo();
	}
	trazarRayos(Rayo(&punto,&direccion), rebote+1, R, G, B);
	IRefraccion = aux;
}

/*
 * Método que calcula la luz indirecta.
 */
VectorT indirectLight(VectorT punto, VectorT normal,Esfera esfera, VectorT dirCam){

	// Declaramos los vectores para el sistema de coordenadas.
	Matriz sistema = sistemaCoordenadas(normal);	// Calculamos el sistema de coordenadas.
	/*cout <<"Sistema: " << endl;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			cout << sistema.getFila(i).getValPos(j) << " ";
		}
		cout << endl;
	}*/
	float inicial[3] = {0,0,0};		// Inicializamos el color inicial.
	VectorT luzIndirecta = VectorT(inicial,3);
	for(int i=0; i<rayosIndirecta; i++){		// Lanzamos los rayos de luz indirecta.
		float R = 0, G = 0, B = 0;
		float random1 = random();		// Obtenemos el primer número aleatorio.
		float random2 = random();		// Obtenemos el segundo número aleatorio.
		// Calculamos los valores de theta y phi.
		float theta = acos(sqrtf(1-random1));
		float phi = 2*PI*random2;
		Matriz coordenadas = uniformeSemiesfera(theta,phi);	// Obtenemos la coordenada random.
		/*cout << "Coordenadas: ";
		for(int i=0; i<3; i++){
			cout << coordenadas.getFila(i).getValPos(0) << " ";
		}
		cout << endl;*/
		// Pasamos a coordenadas del mundo.
		Matriz coordenadasMundo = sistema.mult(coordenadas);
		/*cout << "Multiplicación: ";
				for(int i=0; i<3; i++){
					cout << coordenadasMundo.getFila(i).getValPos(0) << " ";
				}
				cout << endl;*/
		// Lanzamos el rayo para calcular el color.
		VectorT direccion = coordenadasMundo.trasponer().getFila(0);
		direccion = direccion / direccion.modulo();
		/*cout << "direccion: ";
						for(int i=0; i<3; i++){
							cout << direccion.getValPos(i) << " ";
						}
						cout << endl;*/
		Rayo rayo = Rayo(&punto,&direccion);
		VectorT puntoIndirecta = trazarRayos(rayo, 1, R, G, B);
		VectorT dirSombra = (puntoIndirecta -punto);
		dirSombra = dirSombra/dirSombra.modulo();
		float distancia = dirSombra.modulo();
		Rayo sombra = Rayo(&punto, &dirSombra);
		float color[3] = {R, G, B};
		// VectorT luzDevuelta = cos(theta)*lanzarRayo;
		VectorT luzDevuelta = VectorT(color,3);
		luzDevuelta = luzDevuelta / (distancia*distancia);
		VectorT p = phong(sombra, normal, dirCam, esfera, esfera.getMaterial()==PHONG);
		luzDevuelta.setValPos(p.getValPos(0)*luzDevuelta.getValPos(0),0);
		luzDevuelta.setValPos(p.getValPos(1)*luzDevuelta.getValPos(1),1);
		luzDevuelta.setValPos(p.getValPos(2)*luzDevuelta.getValPos(2),2);
		float coseno = cosf(theta);
		if(coseno < 0) {
			coseno = -coseno;
		}
		luzDevuelta = luzDevuelta*coseno;
		// Metemos en luz total la aportación captada por el rayo.
		luzIndirecta = luzIndirecta + luzDevuelta;
	}
	// Calculamos la media de la contribución de cada color.
	luzIndirecta = luzIndirecta / rayosIndirecta;

	return luzIndirecta;		// Devolvemos la luz indirecta.
}

/*
 * Función que calcula el sistema de coordenadas locales.
 */
Matriz sistemaCoordenadas(VectorT normal){

	// Inicializamos el vector con uno perpendicular a la normal.
	float vector[3] = {normal.getValPos(1),-normal.getValPos(0),0};
	VectorT vectorU = VectorT(vector,3);	// Construimos el primer vector perpendicular.
	// Construimos el tercer vector perpendicular con el producto vectorial.
	vectorU = vectorU / vectorU.modulo();
	VectorT vectorV = normal.prodVectorial(vectorU);
	vectorV = vectorV / vectorV.modulo();
	VectorT vectorSistema[3] = {vectorU, vectorV, normal};
	/*float prodEscalar = vectorU.prodEscalar(vectorV);
	cout << prodEscalar << endl;
	cout << "Vector1: " << normal.getValPos(0) << " " << normal.getValPos(1) << " " << normal.getValPos(2);
	cout << endl;
	cout << "Vector2: " << vectorV.getValPos(0) << " " << vectorV.getValPos(1) << " " << vectorV.getValPos(2);
	cout << endl;
	cout << "Vector3: " << vectorU.getValPos(0) << " " << vectorU.getValPos(1) << " " << vectorU.getValPos(2);
	cout << endl;*/
	// Creamos la matriz con el sistema de coordenadas.
	Matriz sistema = Matriz(vectorSistema,3);
	sistema = sistema.trasponer();	// Se traspone la matriz para tener vectores columna.
	return sistema;		// Se devuelve el sistema.

}

/*
 * Función que calcula las muestras uniformes de la semiesfera.
 */
Matriz uniformeSemiesfera(float theta, float phi){

	// Se obtienen las tres coordenadas.
	float x = sinf(theta)*cosf(phi);
	float y = sinf(theta)*sinf(phi);
	float z = cosf(theta);
	float vector[3] = {x,y,z};
	VectorT coordenadas(vector,3);
	VectorT vectores[] = {coordenadas};
	// Se crea la matriz de coordenadas.
	Matriz coord = Matriz(vectores,1);
	coord = coord.trasponer();		// Se traspone para que queden en una columna.
	return coord;		// Se devuelve la matriz.
}


double random() {
	static random_device dev;
	static default_random_engine generator(dev());
	static uniform_real_distribution<double> distribution(0.0,1.0);
	return distribution(generator);
}
