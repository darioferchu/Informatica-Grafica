
#include <iostream>
#include <fstream>
using namespace std;
#include <imagen.cpp>

int main() {

	/*ofstream ficheroSalida;
	ficheroSalida.open ("ficheroTexto.ppm");
	ficheroSalida << "P3\n";
	ficheroSalida << "# Imagen de prueba con c++\n";
	ficheroSalida << "75 75\n";
	ficheroSalida << "255\n";
	for(int i=0; i<75; i++){
		for(int j=0; j<75; j++){
			int aleatorio1 = std::rand()%255;
			int aleatorio2 = std::rand()%255;
			int aleatorio3 = std::rand()%255;
			ficheroSalida << aleatorio1 << " " << aleatorio2 << " "
					<< aleatorio3 << " ";
		}
		ficheroSalida << "\n";
	}
	ficheroSalida.close();*/
	int prueba [75][75];
	for(int i=0; i<75; i++){
		for(int j=0; j<75; j++){
			prueba[i][j] = std::rand()%255;
		}
	}
	Imagen ima = Imagen(75,75,prueba);
	ima.crearFichero("Probando.ppm");
}
