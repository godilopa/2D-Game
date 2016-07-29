#ifndef SA_PAUSE_H
#define SA_PAUSE_H

#include "AppState.h"

class SA_Pause : public AppState{

public:
	virtual void Run();
	virtual void Draw();
	virtual void ProcessInput();
	virtual void Activate();
	virtual void Deactivate();
private:

};

#endif