
#include "../include/globales.h"
#include "../include/AppState.h"
#include "../include/SA_Menu.h"
#include "../include/SA_Playing.h"
#include "../include/SA_Pause.h"
#include "../include/SA_Options.h"
#include "../include/SA_GameOver.h"

//Declare global variables
CGame* g_pGame;
EAppState g_wantedState;

//Manage the change state requests
AppState* NewAppState(EAppState type) {
	switch (type) {
		case SA_MENU:
			return new SA_Menu();
			break;
		case SA_PLAYING:
			return new SA_Playing();
			break;
		case SA_PAUSE:
			return new SA_Pause();
			break;
		case SA_OPTIONS:
			return new SA_Options();
			break;
		case SA_GAMEOVER:
			return new SA_GameOver();
			break;
	}
}

int main(int argc, char** argv) {
	screen.Open(800, 600, false);
	g_pGame = new CGame();
	AppState* currentState;
	g_wantedState = SA_NULL;
	currentState = NewAppState(SA_MENU);
	currentState->Activate();

	while (screen.IsOpened()) {

		if (g_wantedState != SA_NULL) {
			if(currentState) currentState->Deactivate();
			delete currentState;
			currentState = NewAppState(g_wantedState);
			currentState->Activate();
			g_wantedState = SA_NULL;
		}

		currentState->ProcessInput();
		currentState->Run();
		currentState->Draw();
	}

}