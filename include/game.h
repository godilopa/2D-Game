#ifndef GAME_H
#define GAME_H
#define WIN32_LEAN_AND_MEAN

#include "AppState.h"
#include "world.h"
#include "userInterface.h"

class CGame {

public:
	CGame();
	~CGame();
	void ProcessInput();
	void Run();
	void Draw();
	void UpdateLevel();
	void SetGameComplete(bool gameComplete) { m_gameComplete = gameComplete; }
	bool GetGameComplete() const { return m_gameComplete; }
	CWorld* GetWorld() const { return m_pWorld; } //So userInterface can access to world
	CUserInterface* GetUserInterface() const { return m_pUserInterface; }
private:
	CWorld* m_pWorld;
	CUserInterface* m_pUserInterface;
	int32 m_bossLife;
	bool m_gameComplete;
};

#endif
