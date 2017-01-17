/*********************************************************************************
Copyright (C) 2014 Adrian Jarabo (ajarabo@unizar.es)
Copyright (C) 2014 Diego Gutierrez (diegog@unizar.es)
All rights reserved.

This is an educational Ray Tracer developed for the course 'Informatica Grafica'
(Computer Graphics) tought at Universidad de Zaragoza (Spain). As such, it does not 
intend to be fast or general, but just to provide an educational tool for undergraduate
students. 

This software is provided as is, and any express or implied warranties are disclaimed.
In no event shall copyright holders be liable for any damage.
**********************************************************************************/
#include "PhotonMapping.h"
#include "World.h"
#include "Intersection.h"
#include "Ray.h"
#include "BSDF.h"
#include <random>

//*********************************************************************
// Compute the photons by tracing the Ray 'r' from the light source
// through the scene, and by storing the intersections with matter
// in the lists 'xx_photons', storing the diffuse (global) and caustic
// photons respectively. For efficiency, both are computed at the same
// time, since computing them separately would result into a lost of
// several samples marked as caustic or diffuse.
// Same goes with the boolean 'direct', that specifies if direct 
// photons (from light to surface) are being stored or not. 
// The initial traced photon has energy defined by the tristimulus
// 'p', that accounts for the emitted power of the light source.
// The function will return true when there are more photons (caustic
// or diffuse) to be shot, and false otherwise.
//---------------------------------------------------------------------
bool PhotonMapping::trace_ray(const Ray& r, const Vector3 &p, 
			   std::list<Photon> &global_photons, std::list<Photon> &caustic_photons, bool direct)
{

	//Check if max number of shots done...
	if( ++m_nb_current_shots > m_max_nb_shots )
	{
		return false;
	}
	
	// Compute irradiance photon's energy
	Vector3 energy(p);
	
	Ray photon_ray(r);
	photon_ray.shift();

	bool is_caustic_particle = false;

	//Iterate the path
	while(1)
	{
		// Throw ray and update current_it
		Intersection it;
		world->first_intersection(photon_ray, it);

		if( !it.did_hit() )
			break;

		//Check if has hit a delta material...
		if( it.intersected()->material()->is_delta() )
		{
			// If delta material, then is caustic...
			// Don't store the photon!
			is_caustic_particle = true;
		}
		else if (photon_ray.get_level() > 0 || direct)
		{
			//If non-delta material, store the photon!
			if( is_caustic_particle )	
			{				
				//If caustic particle, store in caustics
				if( caustic_photons.size() < m_nb_caustic_photons )
					caustic_photons.push_back( Photon(it.get_position(), photon_ray.get_direction(), energy ));
			}
			else						
			{
				//If non-caustic particle, store in global
				if( global_photons.size() < m_nb_global_photons )
					global_photons.push_back( Photon(it.get_position(), photon_ray.get_direction(), energy ));
			}
			is_caustic_particle = false;
		}	
		
		Real pdf;

		Vector3 surf_albedo = it.intersected()->material()->get_albedo(it);
		Real avg_surf_albedo = surf_albedo.avg();

		Real epsilon2 = static_cast<Real>(rand())/static_cast<Real>(RAND_MAX);
		while (epsilon2 < 0.)
			epsilon2 = static_cast<Real>(rand())/static_cast<Real>(RAND_MAX);
		
		if (epsilon2 > avg_surf_albedo || photon_ray.get_level() > 20 ) 
			break;
			
		// Random walk's next step
		// Get sampled direction plus pdf, and update attenuation
		it.intersected()->material()->get_outgoing_sample_ray(it, photon_ray, pdf );

		// Shade...
		energy = energy*surf_albedo;
		if( !it.intersected()->material()->is_delta() )
			energy *= dot_abs(it.get_normal(), photon_ray.get_direction())/3.14159;		

		energy = energy /(pdf*avg_surf_albedo);
	}
	
	if( caustic_photons.size() == m_nb_caustic_photons && 
		global_photons.size() == m_nb_global_photons )
	{
		m_max_nb_shots = m_nb_current_shots-1;
		return false;
	}

	return true;
}

//*********************************************************************
// TODO: Implement the preprocess step of photon mapping,
// where the photons are traced through the scene. To do it,
// you need to follow these steps for each shoot:
//  1 - Sample a world's light source in the scene to create
//		the initial direct photon from the light source.
//	2 - Trace the photon through the scene storing the inter-
//		sections between the photons and matter. You can use
//		the function 'trace_ray' for this purpose.
//	3 - Finally, once all the photons have been shot, you'll
//		need to build the photon maps, that will be used later
//		for rendering. 
//		NOTE: Careful with function
//---------------------------------------------------------------------
void PhotonMapping::preprocess()
{
	// Parámetros para el random.
	default_random_engine random;
	uniform_real_distribution<float> distribution(-1.0, 1.0);

	// Se crean listas de fotones.
	std::list<Photon> global_photons;
	std::list<Photon> caustic_photons;
	// Se obtiene una lista de las luces
	std::vector<LightSource*> lights = world->light_source_list;
	bool caust = false;

	for (int i = 0; i < static_cast<int>(lights.size()); i++) {		// Se recorren las luces.
		LightSource *light = lights.at(i);		// Se obtiene la luz actual.
		Vector3 origin = light->get_position(); // Se obtiene posición de la luz actual.
		Ray ray;		// Se declara el rayo.
						// Se calcula dirección aleatoria.
		Real randomX = distribution(random);
		Real randomY = distribution(random);
		Real randomZ = distribution(random);
		while (pow(randomX, 2) + pow(randomY, 2) + pow(randomZ, 2) > 1) {
			randomX = distribution(random);
			randomY = distribution(random);
			randomZ = distribution(random);
		}
		Vector3 direction = Vector3(randomX, randomY, randomZ);	// Se crea el vector con la dirección.
		direction = direction.normalize();		// Se normaliza.
		ray = Ray(origin, direction);		// Se crea y lanza el rayo.
		while (trace_ray(ray, light->get_intensities() / m_max_nb_shots, global_photons, caustic_photons, false)) {
			// Se guardan los fotones en el KD-Tree.
			list<Photon>::iterator fotones = global_photons.begin();		// Se crea el iterador.
			for (int i = 0; i < static_cast<int>(global_photons.size()); i++) {		// Se recorren los fotones.
				Photon foton = *fotones;		// Se obtiene el fotón actual.
				std::vector<Real> position = { foton.position.getComponent(0),
					foton.position.getComponent(1),foton.position.getComponent(2) };	// Vector para la posición.
				m_global_map.store(position, foton);	// Se almacena el fotón.
				*fotones++;		// Se pasa al siguiente fotón.
			}
			fotones = caustic_photons.begin();		// Se crea el iterador.
			for (int i = 0; i < static_cast<int>(caustic_photons.size()); i++) {		// Se recorren los fotones.
				Photon foton = *fotones;		// Se obtiene el fotón actual.
				std::vector<Real> position = { foton.position.getComponent(0),
					foton.position.getComponent(1),foton.position.getComponent(2) };	// Vector para la posición.
				m_caustics_map.store(position, foton);		// Se almacena el fotón.
				*fotones++;		// Se pasa al siguiente fotón.
				caust = true;
			}
			global_photons.clear();
			caustic_photons.clear();
			// Se calcula dirección aleatoria.
			randomX = distribution(random);
			randomY = distribution(random);
			randomZ = distribution(random);
			while (pow(randomX, 2) + pow(randomY, 2) + pow(randomZ, 2) > 1) {
				randomX = distribution(random);
				randomY = distribution(random);
				randomZ = distribution(random);
			}
			direction = Vector3(randomX, randomY, randomZ);	// Se crea el vector con la dirección.
			direction = direction.normalize();		// Se normaliza.
			ray = Ray(origin, direction);		// Se crea y lanza el rayo.
		} 
	}
	m_global_map.balance();
	if (caust) {
		m_caustics_map.balance();
	}
}

//*********************************************************************
// TODO: Implement the function that computes the rendering equation 
// using radiance estimation with photon mapping, using the photon
// maps computed as a proprocess. Note that you will need to handle
// both direct and global illumination, together with recursive the 
// recursive evaluation of delta materials. For an optimal implemen-
// tation you should be able to do it iteratively.
// In principle, the class is prepared to perform radiance estimation
// using k-nearest neighbors ('m_nb_photons') to define the bandwidth
// of the kernel.
//---------------------------------------------------------------------
Vector3 PhotonMapping::shade(Intersection &it0)const
{
	Vector3 L(0);		// Variables a utilizar.
	Intersection it(it0);

	// Se obtiene la dirección de la cámara.
	Vector3 direccionCam = it.get_position() - world->get_ambient();
	direccionCam = direccionCam.normalize();		// Se normaliza.
	if(it.intersected()->material()->is_delta()){		// Si el material es delta...
		int rebotes = 0;		// Número de rebotes que se permiten.
		while (it.did_hit() && rebotes < 50 && it.intersected()->material()->is_delta()) {
			Ray r; Real x;	// Variables para calcular.
			Vector3 normal = it.get_normal();		// Se obtiene la normal.
			// Se fija el rayo de salida.
			it.intersected()->material()->get_outgoing_sample_ray(it, r, x);
			world->first_intersection(r, it);		// Se obtiene la intersección.
			if (it.did_hit()) {		// Si choca con algo...
				// Se crea un vector auxiliar.
				Vector3 aux = r.get_origin() - it.get_position();
				// Se modifica respecto a la normal.
				Real dist = sqrtf(pow(aux.getComponent(0), 2) + pow(aux.getComponent(1), 2) + pow(aux.getComponent(2), 2));
				if (dist < 0.0001) {
					// Se lanza el rayo.
					r = Ray(r.get_origin() + normal*0.001, r.get_direction());
					world->first_intersection(r, it);
				}
			} 
			// Se obtiene la dirección a la cámara y se normaliza.
			direccionCam = r.get_direction();
			direccionCam = direccionCam.normalize();
			rebotes++;		// Se aumenta el número de rebotes.
		}
		if (!it.did_hit()) {		// Si no choca con nada se devuelve el color del fondo.
			return world->get_background();
		}
	}

	// Se obtiene el color difuso y el coeficiente especular.
	Vector3 Kd = it.intersected()->material()->get_albedo(it);
	Real specular = (it.intersected()->material()->get_specular(it));

	Real k = 1.0;		// Se fija el parámetro del filtro de cono.
	// Se crea el vector con la posición de la intersección.
	std::vector<Real> p = {it.get_position().getComponent(0),it.get_position().getComponent(1),
		it.get_position().getComponent(2)};
	Real radio = 0;		// Se fija la variable del radio.

	// Se crea el vector para los fotones más cercanos.
	std::vector<const KDTree<Photon, 3U>::Node*> nodes;
	m_global_map.find(p, 50, nodes, radio);		// Se buscan los fotones.

	// Luz del mapa global.
	Vector3 indirecta = Vector3(0,0,0);		// Vector de la luz indirecta.
	for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
		// Se obtiene el fotón.
		const KDTree<Photon, 3>::Node *foton = nodes.at(i);
		Vector3 flujo = foton->data().flux;		// Se saca el flujo.
		// Se calcula el valor de la BRDF.
		Vector3 Wr = Vector3(0, 0, 0);		// Dirección del rayo reflejado.
		Wr = Wr.reflect(it.get_normal());
		// Producto escalar del reflejado con la cámara.
		Real prod = direccionCam.dot_abs(Wr);
		// Valor final de la BRDF.
		Vector3 brdf = Kd / 3.14159 + specular*((100 + 2) / (2 * 3.14159))*pow(prod, 100);
		Real wp = 0.0;		// Parámetros para el filtro de cono.
		Vector3 d = it.get_position() - foton->data().position;
		Real dk = 1-(sqrtf(pow(d.getComponent(0),2) + pow(d.getComponent(1),2) +
			pow(d.getComponent(2),2))/(k*radio));
		if (wp < dk) {
			wp = dk;
		}
		indirecta += brdf*flujo*wp;	// Aplicamos flujo, BRDF y cono.
	}
	// Aplicamos el filtro de cono.
	Real denominador = (1-(2/3*k))*3.14159265 * pow(radio, 2);
	indirecta = indirecta / denominador;

	nodes.clear();
	m_caustics_map.find(p, 50, nodes, radio);	// Se buscan los fotones.
	
	// Luz del mapa de cáusticas.
	Vector3 causticas = Vector3(0, 0, 0);	// Vector de luz de caústicas.
	for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
		// Se obtiene el fotón.
		const KDTree<Photon, 3>::Node *foton = nodes.at(i);
		Vector3 flujo = foton->data().flux;		// Se saca el flujo.

		// Se calcula el valor de la BRDF.
		Vector3 Wr = Vector3(0, 0, 0);		// Dirección del rayo reflejado.
		Wr = Wr.reflect(it.get_normal());
		// Producto escalar del reflejado con la cámara.
		Real prod = direccionCam.dot_abs(Wr);
		// Valor final de la BRDF. 
		Vector3 brdf = Kd / 3.14159 + specular*((100 + 2) / (2 * 3.14159))*pow(prod, 100);
		Real wp = 0.0;	// Parámetros para el filtro de cono.
		Vector3 d = it.get_position() - foton->data().position;
		Real dk = 1 - (sqrtf(pow(d.getComponent(0), 2) + pow(d.getComponent(1), 2) + 
			pow(d.getComponent(2), 2)) / (k*radio));
		if (wp < dk) {
			wp = dk;
		}
		causticas += brdf*flujo*wp;	// Aplicamos flujo, BRDF y cono.
	}
	// Aplicamos el filtro de cono.
	denominador = (1 - (2 / 3 * k))*3.14159265 * pow(radio, 2);
	causticas = causticas / denominador;

	// Luz Directa 
	Vector3 directa = Vector3(0, 0, 0);		// Vector para la luz directa.
	// Se obtiene la lista de luces.
	std::vector<LightSource*> lights = world->light_source_list;
	for (int i = 0; i < static_cast<int>(lights.size()); i++) {
		LightSource *light = lights.at(i);		// Se obtiene la luz.
		if(light->is_visible(it.get_position())) {	// Se comprueba si es visible.
			// Se obtiene la dirección de sombra.
			Vector3 dirSombra = light->get_incoming_direction(it.get_position());
			dirSombra = dirSombra.normalize();
			Vector3 Wr = Vector3(0, 0, 0);		// Dirección del rayo reflejado.
			Wr = it.get_normal().reflect(dirSombra);
			// Producto escalar entre la cámara y la sombra.
			Real prod = dirSombra.dot_abs(Wr);
			// Calculo final de la BRDF.
			Vector3 brdf = Kd / 3.14159 + specular*((100 + 2) / (2 * 3.14159))*pow(prod, 100);
			// Se acumula para cada fuente de luz.
			Real cos = dirSombra.dot_abs(it.get_normal());
			directa = directa + light->get_incoming_light(it.get_position())*brdf*cos;
		}
	}
	//indirecta = (0, 0, 0);
	//causticas = (0, 0, 0);
	//directa = (0, 0, 0);
	// Sumar aportación de todas.
	return directa+indirecta+causticas;

	
	//**********************************************************************
	// The following piece of code is included here for two reasons: first
	// it works as a 'hello world' code to check that everthing compiles 
	// just fine, and second, to illustrate some of the functions that you 
	// will need when doing the work. Goes without saying: remove the 
	// pieces of code that you won't be using.
	//
	/*unsigned int debug_mode = 1;

	switch (debug_mode)
	{
	case 1:
		// ----------------------------------------------------------------
		// Display Albedo Only
		L = it.intersected()->material()->get_albedo(it);
		break;
	case 2:
		// ----------------------------------------------------------------
		// Display Normal Buffer
		L = it.get_normal();
		break;
	case 3:
		// ----------------------------------------------------------------
		// Display whether the material is specular (or refractive) 
		L = Vector3(it.intersected()->material()->is_delta());
		break;

	case 4:
		// ----------------------------------------------------------------
		// Display incoming illumination from light(0)
		L = world->light(0).get_incoming_light(it.get_position());
		break;

	case 5:
		// ----------------------------------------------------------------
		// Display incoming direction from light(0)
		L = world->light(0).get_incoming_direction(it.get_position());
		break;

	case 6:
		// ----------------------------------------------------------------
		// Check Visibility from light(0)
		if (world->light(0).is_visible(it.get_position()))
			L = Vector3(1.);
		break;
	}
	// End of exampled code
	//**********************************************************************
	
	return L;*/
}