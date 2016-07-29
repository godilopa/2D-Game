#ifndef BOSS_H
#define BOSS_H

#include "entity.h"

class CBoss : public CEntity {

public:
	CBoss(Sprite* sprite, int32 life) : CEntity(sprite, life) { m_id = EBOSS; };
	~CBoss() {};
	virtual void Run();
private:

};


#endif