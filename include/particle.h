#ifndef PARTICLE_H
#define PARTICLE_H

#include "sprite.h"

class Particle : public Sprite {
public:
	Particle();
	Particle(Image* image, double velx, double vely, double angularVel,
		double lifetime, bool autofade);
	virtual void SetVelocityx(double velocityx) { Particle::velocityx = velocityx; }
	virtual void SetVelocityy(double velocityy) { Particle::velocityy = velocityy; }
	virtual void SetAngularVelocity(double angularVelocity) { Particle::angularVelocity = angularVelocity; } //??porque si no pongo set no me deja hacer Particle::angularVelocity
	virtual double GetLifetime() const { return lifetime; }
	virtual bool IsAffected() const { return affected; }
	virtual void SetAffected(bool affected) { Particle::affected = affected; }
	virtual void Update(double elapsed);
private:
	double velocityx, velocityy;
	double angularVelocity;
	double lifetime;
	double initialLifetime;
	bool autofade;
	bool affected;
};

#endif