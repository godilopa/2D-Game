
#include "../include/SA_Menu.h"
#include "../include/SA_Playing.h"
#include "../include/font.h"
#include "../include/globales.h"

void SA_Menu::Run() {

}

void SA_Menu::Draw() {
	renderer.SetBlendMode(renderer.ALPHA);
	font->Render(start, 2*screen.GetWidth() / 5, screen.GetHeight() / 2);
	screen.Refresh();
	renderer.Clear();
}

void SA_Menu::ProcessInput() {
	if (screen.KeyPressed(GLFW_KEY_ENTER)) {
		g_wantedState = SA_OPTIONS;
	}
}

void SA_Menu::Activate() {
	font = new Font("data/arial16.png");
	start = "Press enter to play";
}

void SA_Menu::Deactivate() {
	delete font;
}