
#include "../include/boss.h"
#include "../include/globales.h"
#include <ctime>
#include <cstdlib>

void CBoss::Run(){

	m_pSprite->SetAngle(Angle(GetPosX(), GetPosY(), screen.GetWidth() / 2, screen.GetHeight() / 2) + 180); // +180 to face the ship towards the base

	//If rand condition is true, boss changes the position around the base instantly, keeping the actual distance
	if ((rand() % 125) < 1) { // 1/120 probability per frame
		double angle = rand() % 360;
		double distance = Distance(m_pSprite->GetX(),m_pSprite->GetY(), screen.GetWidth() / 2, screen.GetHeight() / 2);
		m_pSprite->SetPosition(screen.GetWidth() / 2 + distance * DegCos(angle), screen.GetHeight() / 2 - distance * DegSin(angle));
		m_pSprite->MoveTo(screen.GetWidth() / 2, screen.GetHeight() / 2, m_velocity);
	}

	m_pSprite->Update(screen.ElapsedTime());
}