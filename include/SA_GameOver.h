#ifndef SA_GAMEOVER_H
#define SA_GAMEOVER_H

#include "AppState.h"
class String;
class Font;

class SA_GameOver : public AppState {

public:
	virtual void Run();
	virtual void Draw();
	virtual void ProcessInput();
	virtual void Activate();
	virtual void Deactivate();
private:
	Font* font;
	String gameStatus;
};

#endif