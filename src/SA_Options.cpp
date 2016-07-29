
#include "../include/SA_Menu.h"
#include "../include/SA_Options.h"
#include "../include/font.h"
#include "../include/globales.h"

void SA_Options::Run() {

}

void SA_Options::Draw() {
	renderer.SetBlendMode(renderer.ALPHA);
	font->Render(difficulty, 2 * screen.GetWidth() / 5, 4 * screen.GetHeight() / 10);
	font->Render(easy, 2 * screen.GetWidth() / 5 + font->GetTextWidth(difficulty), 4 * screen.GetHeight() / 10);
	font->Render(medium, 2 * screen.GetWidth() / 5 + font->GetTextWidth(difficulty), screen.GetHeight() / 2);
	font->Render(hard, 2 * screen.GetWidth() / 5 + font->GetTextWidth(difficulty), 6 * screen.GetHeight() / 10);
	screen.Refresh();
	renderer.Clear();
}

void SA_Options::ProcessInput() {
	if (screen.KeyPressed(69)){
		g_wantedState = SA_PLAYING;
		g_pGame->GetWorld()->SetEnemyLife(1);
		g_pGame->GetWorld()->SetNumberOfEnemies(4);
	}
	if (screen.KeyPressed(77)) {
		g_wantedState = SA_PLAYING;
		g_pGame->GetWorld()->SetEnemyLife(2);
		g_pGame->GetWorld()->SetNumberOfEnemies(4);
	}
	if (screen.KeyPressed(72)) {
		g_wantedState = SA_PLAYING;;
		g_pGame->GetWorld()->SetEnemyLife(2);
		g_pGame->GetWorld()->SetNumberOfEnemies(5);
	}
}

void SA_Options::Activate() {
	font = new Font("data/arial16.png");
	difficulty = "Difficulty: ";
	easy = "Easy (press e)";
	medium = "Medium (press m)";
	hard = "Hard (press h)";
}

void SA_Options::Deactivate() {
	delete font;
}