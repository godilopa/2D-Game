#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class CBullet : public CEntity {

public:
	CBullet(Sprite* sprite, int32 life) : CEntity(sprite, life) { m_id = EBULLET; };
	~CBullet() {};
	void SetDir(double x, double y){ m_dirX = x; m_dirY = y; }
	virtual void Run();
private:
	double m_dirX, m_dirY; // direction vector of the movement
};

#endif