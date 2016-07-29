#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class CEnemy : public CEntity {

public:
	CEnemy(Sprite* sprite, int32 life) : CEntity(sprite, life) { m_id = EENEMY; };
	~CEnemy() {};
	virtual void Run();
private:

};


#endif