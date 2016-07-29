#include "../include/emitter.h"

#include <random>
#include <cstdlib>
#include <ctime>

//double RandDouble(double min, double max){
//	std::tr1::uniform_real<double> unif(min, max);
//	std::default_random_engine re;
//	return unif(re);
//}


Emitter::Emitter(Image* image, bool autofade): image(image), autofade(autofade){
	emitting = false;
}

void Emitter::Start(){
	srand(static_cast<unsigned int>(time(0)));
		double rate = (rand() % (int)(maxrate - minrate)) + (int)minrate;
		for (int32 i = 0; i < rate; i++){
			double velx = minvelx + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxvelx - minvelx)));
			double vely = minvely + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxvely - minvely)));
			double angvel = minangvel + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxangvel - minangvel)));
			double lifetime = minlifetime + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxlifetime - minlifetime)));
			Particle particle(image, velx, vely, angvel, lifetime, autofade);
			particle.SetBlendMode(Renderer::ADDITIVE);
			particle.SetColor(rand() % 255, rand() % 255, rand() % 255);
			particle.SetPosition(GetX(), GetY());
			particles.Add(particle);
		}
		emitting = true;
}

void Emitter::Update(double elapsed){
	for (int32 i = 0; i < particles.Size(); i++){ //Para cada particula
			for (int32 j = 0; j < affectors.Size(); j++){ //Comprobamos para cada afector si la particula entra en su region
				if (ParticleAffected(particles[i], affectors[j]) && !particles[i].IsAffected()){ //Si la particula entra en la region cambia sus estados y se actualiza
					//Calculamos el random de cada atributo que se va a cambiar
					int8 newr, newg, newb;
					double newangvel = affectors[j].newminangvel + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (affectors[j].newmaxangvel - affectors[j].newminangvel)));
					if (affectors[j].newmaxr == 0){
						newr = 0;
					}
					else{
						newr = (rand() % (affectors[j].newmaxr - affectors[j].newminr)) + affectors[j].newminr;
					}

					if (affectors[j].newmaxg == 0){
						newg = 0;
					}
					else{
						newg = (rand() % (affectors[j].newmaxg - affectors[j].newming)) + affectors[j].newming;
					}

					if (affectors[j].newmaxb == 0){
						newb = 0;
					}
					else{
						newb = (rand() % (affectors[j].newmaxb - affectors[j].newminb)) + affectors[j].newminb;
					}

					particles[i].SetColor(newr,newg,newb);
					particles[i].SetAngularVelocity(newangvel);
					particles[i].SetAffected(true);
					particles[i].Update(elapsed);
				}

				if(!particles[i].IsAffected()){ //Si la particula no ha sido afectada vuelve a su estado original
					double angvel = minangvel + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxangvel - minangvel)));
					particles[i].SetColor(rand() % 255, rand() % 255, rand() % 255);
					particles[i].SetAngularVelocity(angvel);
					particles[i].Update(elapsed);
				}
			}
			particles[i].SetAffected(false); //la particula ya esta lista para volver a ser afectada
		
	if (particles[i].GetLifetime() <= 0) particles.RemoveAt(i); //la particula se elimina
	}
}

void Emitter::Stop(){
	emitting == false;
}

void Emitter::Render() const{
	for (int32 i = 0; i < particles.Size(); i++){
		particles[i].Render();
	}
}

bool Emitter::ParticleAffected(const Particle& particle, const Affector& affector) {
	double x = particle.GetX();
	double y = particle.GetY();
	Vector2 vector = { x, y };
	//Recta p1-p2
	double v1 = affector.region.p2.x - affector.region.p1.x;
	double v2 = affector.region.p2.y - affector.region.p1.y;
	double c1 = v2 * x - v1 * y + v1 * affector.region.p1.y - v2 * affector.region.p1.x;
	//Recta p2-p3
	v1 = affector.region.p3.x - affector.region.p2.x;
	v2 = affector.region.p3.y - affector.region.p2.y;
	double c2 = v2 * x - v1 * y + v1 * affector.region.p2.y - v2 * affector.region.p2.x;
	//Recta p4-p3
	v1 = affector.region.p3.x - affector.region.p4.x;
	v2 = affector.region.p3.y - affector.region.p4.y;
	double c3 = v2 * x - v1 * y + v1 * affector.region.p4.y - v2 * affector.region.p4.x;
	//Recta p1-p4
	v1 = affector.region.p4.x - affector.region.p1.x;
	v2 = affector.region.p4.y - affector.region.p1.y;
	double c4 = v2 * x - v1 * y + v1 * affector.region.p1.y - v2 * affector.region.p1.x;
	if (c1 < 0 && c2 < 0 && c3 > 0 && c4 > 0){
		return true;
	}
	else{
		return false;
	}


}