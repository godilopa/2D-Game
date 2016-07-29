#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"
#include "sprite.h"

enum EntityId{ ENULL, EPLAYER, EBULLET, EENEMY, EBASE, EBOSS};

class CEntity {

public:
	CEntity(Sprite* sprite, int32 life) : m_pSprite(sprite), m_life(life) {}
	~CEntity() { delete m_pSprite; };

	void SetPos(double x, double y) { m_pSprite->SetPosition(x, y); }
	void SetRadius(double r) { m_radius = r; }
	void SetVelocity(double v) { m_velocity = v; }
	void SetLife(int32 life){ m_life = life; }

	int32 GetLife() const { return m_life; }
	EntityId GetId() const { return m_id; }
	double GetRadius() const { return m_radius; }
	double GetPosX() const { return m_pSprite->GetX(); }
	double GetPosY() const { return m_pSprite->GetY(); }

	void Draw(){ m_pSprite->Render(); }
	virtual void Run() = 0;
protected:
	Sprite* m_pSprite;
	EntityId m_id;
	int32 m_life;
	double m_radius; //radius around the centre of the sprite to check collisions
	double m_velocity; 
};


#endif