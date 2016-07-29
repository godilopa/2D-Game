
#include "../include/userInterface.h"
#include "../include/globales.h"

void CUserInterface::Input() {
	mouseX = screen.GetMouseX();
	mouseY = screen.GetMouseY();
	m_shootDelay += screen.ElapsedTime();
	if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && m_shootDelay >= 0.3) {
		g_pGame->GetWorld()->CreateBullet();
		m_shootDelay = 0;
	}
	if (screen.KeyPressed(GLFW_KEY_ESC)) {
		g_wantedState = SA_PAUSE;
	}



}