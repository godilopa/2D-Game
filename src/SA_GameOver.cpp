#include "../include/SA_Menu.h"
#include "../include/SA_GameOver.h"
#include "../include/globales.h"
#include "../include/font.h"

void SA_GameOver::Run() {

}

void SA_GameOver::Draw() {
	renderer.SetBlendMode(renderer.ALPHA);
	font->Render(gameStatus, 2 * screen.GetWidth() / 5, screen.GetHeight() / 2);
	screen.Refresh();
	renderer.Clear();
}

void SA_GameOver::ProcessInput() {
	if (screen.KeyPressed(GLFW_KEY_ENTER)) {
		g_wantedState = SA_MENU;
	}
}

void SA_GameOver::Activate() {
	screen.SetTitle("");
	if (g_pGame->GetGameComplete()) {
		gameStatus = "GAME COMPLETE :D !!!";
	}
	else{
		gameStatus = "GAME OVER :(";
	}
	font = new Font("data/arial16.png");
}

void SA_GameOver::Deactivate() {
	delete font;
	//Reset the game
	delete g_pGame;
	g_pGame = new CGame();
}