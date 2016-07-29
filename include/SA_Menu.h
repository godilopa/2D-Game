#ifndef SA_MENU_H
#define SA_MENU_H

#include "AppState.h"
#include "string.h"
class Font;

class SA_Menu : public AppState {

public:
	virtual void Run();
	virtual void Draw();
	virtual void ProcessInput();
	virtual void Activate();
	virtual void Deactivate();
private:
	Font* font;
	String start;
};

#endif
