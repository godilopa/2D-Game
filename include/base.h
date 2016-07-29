#ifndef BASE_H
#define BASE_H

#include "entity.h"

class CBase : public CEntity {

public:
	CBase(Sprite* sprite, int32 life) : CEntity(sprite, life) { m_id = EBASE; };
	~CBase() {};
	virtual void Run(){}
private:

};

#endif
