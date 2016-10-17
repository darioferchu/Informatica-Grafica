
#include "Matriz.h"
#include <iostream>
#include <fstream>
using namespace std;

/*
 * Función que lee desde un fichero los datos de la escena.
 */
/*int leerFichero(){

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
}*/
