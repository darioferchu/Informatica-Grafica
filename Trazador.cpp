#define infinito 99999
#define altura 500
#define anchura 500

int main(){

	float distInterseccion = infinito;

	// Recorremos anchura y altura del mapa pixeles.
	for(int i=0; i<altura; i++){
		for(int j=0; j<anchura; j++){
			// Creamos rayo primario.
			float puntoRayo[3] = {}:
			float DireccionRayo[3] = {}:
			Vector punto = Vector(puntoRayo,3);
			Vector direccion = Vector(direccionRayo,3);
			Rayo ray = Rayo(punto,direccion);
			TrazarRayos(ray);

		}
	}
	return 0;
}

int trazarRayos(Rayo ray, int rebote){
	
	if(rebote != 5){
		// Recorremos los objetos para saber intersecciones.
		for(int k=0; k<objetos.size(); k++){
			float intersecta = Interseccion();
			if(intersecta && intersecta < distInterseccion){
				// comparamos para obtener el objeto con distancia mínima.
				distInterseccion = intersecta;
				// Se guarda el objeto con el que ha intersectado.
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
