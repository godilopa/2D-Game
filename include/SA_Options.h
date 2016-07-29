#ifndef SA_OPTIONS_H
#define SA_OPTIONS_H

#include "AppState.h"
class Font;
class String;

class SA_Options : public AppState {

public:
	virtual void Run();
	virtual void Draw();
	virtual void ProcessInput();
	virtual void Activate();
	virtual void Deactivate();
private:
	Font* font;
	String difficulty, easy, medium, hard;
};

#endif