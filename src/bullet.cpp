
#include "../include/bullet.h"
#include "../include/globales.h"

void CBullet::Run() {
	if (m_pSprite->IsMoving() == false) {
		m_pSprite->MoveTo(GetPosX() + m_dirX * 400, GetPosY() + m_dirY * 400, m_velocity); //400 to exceed the limits of the screen
	}

	m_pSprite->Update(screen.ElapsedTime());
}
