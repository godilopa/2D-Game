#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "types.h"

class CUserInterface{

public:
	void Input();
	int32 GetMouseX(){ return mouseX; }
	int32 GetMouseY(){ return mouseY; }
private:
	int32 mouseX, mouseY;
	double m_shootDelay = 1;
};

#endif