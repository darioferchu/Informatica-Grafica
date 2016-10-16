
//#include <random>
//#include "Imagen.h"
//using namespace std;

/*int random() {
	static std::random_device dev;
	static std::default_random_engine gen(dev());
	static std::uniform_int_distribution<int> dis(0,255);
	return dis(gen);
}*/

/*int main() {

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
	/*int prueba [2000*2000];
	for(int i=0; i<2000; i++){
		for(int j=0; j<2000; j++){
			prueba[i*j] = (i*j)%255;
		}
	}
	Imagen ima = Imagen(2000,2000,prueba);
	ima.crearFichero("Probando.ppm");*/
//}
