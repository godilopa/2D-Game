
#include "../include/player.h"
#include "../include/globales.h"

#define DISTANCEFROMBASE 80

void CPlayer::Run(){

	m_mouseX = g_pGame ->GetUserInterface()->GetMouseX();
	m_mouseY = g_pGame->GetUserInterface()->GetMouseY();

	m_angle = Angle(m_mouseX, -m_mouseY, screen.GetWidth() / 2, -screen.GetHeight() / 2);
	m_x = screen.GetWidth() / 2 + DISTANCEFROMBASE * DegCos(m_angle);
	m_y = screen.GetHeight() / 2 + DISTANCEFROMBASE * DegSin(m_angle);

	SetPos(m_x, m_y);
	m_pSprite->SetAngle(Angle(m_mouseX, m_mouseY, m_x, m_y) + 90); // To face the player correctly
}