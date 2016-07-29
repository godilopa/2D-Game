
#include "../include/SA_Pause.h"
#include "../include/SA_Menu.h"
#include "../include/globales.h"

void SA_Pause::ProcessInput() {
	if (screen.KeyPressed(GLFW_KEY_ESC)) {
		g_wantedState = SA_PLAYING;
	}
}

void SA_Pause::Run() {
}

void SA_Pause::Draw() {
	g_pGame->Draw();
}

void SA_Pause::Activate() {

}

void SA_Pause::Deactivate() {

}