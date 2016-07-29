#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class CPlayer : public CEntity {
public:
	CPlayer(Sprite* sprite, int32 life) : CEntity(sprite, life) { m_id = EPLAYER; };
	~CPlayer() {};
	virtual void Run();
private:
	double m_angle; //to control where the player is rotating around the base
	int32 m_mouseX, m_mouseY;
	double m_x, m_y;
};

#endif