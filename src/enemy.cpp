
#include "../include/enemy.h"
#include "../include/globales.h"

void CEnemy::Run(){

	if (m_pSprite->IsMoving() == false) {
		m_pSprite->MoveTo(screen.GetWidth() / 2, screen.GetHeight() / 2, m_velocity);
		m_pSprite->SetAngle(Angle(GetPosX(), GetPosY(), screen.GetWidth() / 2, screen.GetHeight() / 2) - 90); // -90 to face the ship towards the base
	}

	m_pSprite->Update(screen.ElapsedTime());
}