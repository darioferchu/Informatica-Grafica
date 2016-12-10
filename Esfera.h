
#include "VectorT.h"

/*
 * Clase Esfera con construcores, destructor y métodos
 * para trabajar con ellas.
 */
class Esfera {
	public:
		Esfera();	// Constructor sin parámetros.
		Esfera(VectorT, float, VectorT,int, float);	// Constructor con parámetros.
		virtual ~Esfera();	// Destructor.

		// Métodos getter.
		float getRadio();
		VectorT getCentro();
		VectorT getColor();
		VectorT getKd();
		float getKs();
		float getAlpha();
		int getMaterial();
		float getIor();
		// Métodos setter.
		void setKs(float);
		void setAlpha(float);

	private:
		float radio;	// Radio de la esfera.
		VectorT centro;	// Centro de la esfera.
		VectorT color;	// Color de la esfera.
		// Valores para la BRDF.
		VectorT Kd;
		float Ks;
		float alpha;
		int material;	// Material de la esfera.
		float ior;	// Coeficiente de refracción.
};
