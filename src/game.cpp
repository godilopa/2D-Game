#include "../include/game.h"
#include "../include/globales.h"
#include <windows.h> //To use sleep

CGame::CGame() {
	//Pointer initialization
	m_pWorld = new CWorld();
	m_pUserInterface = new CUserInterface();
	m_gameComplete = false;
	//Create the first level
	level.ReadLevel(1);
}

CGame::~CGame() {
	delete m_pWorld;
	delete m_pUserInterface;
}

void CGame::ProcessInput() {
	m_pUserInterface->Input();
}

void CGame::Run() {
	m_pWorld->Run();
	UpdateLevel();
}

void CGame::Draw() {
	m_pWorld->Draw();
}

void CGame::UpdateLevel(){
	//In the second level goal is decreased because of the time
	if (level.GetNumberLevel() == 2) {
		double numberGoal = level.GetNumberGoal() - screen.ElapsedTime();
		level.SetNumberGoal(numberGoal);
	}

	//Next level if goal is reached
	if (level.GetNumberGoal() <= 0 && !m_gameComplete) {
		screen.SetTitle("LEVEL COMPLETED !!!");
		m_pWorld->DeleteEnemies();
		m_pWorld->DeleteBullets(true);
		g_wantedState = SA_PAUSE;
		Sleep(2000); //2 seconds to start next level
		screen.Refresh(); //to avoid a huge elapsedTime
		g_wantedState = SA_PLAYING;
		int32 number = level.GetNumberLevel();
		level.ReadLevel(++number); //we load the new level info
	}
}