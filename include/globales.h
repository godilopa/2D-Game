#ifndef GLOBALES_H
#define GLOBALES_H

#include "u-gine.h"
#include "level.h"
#include "game.h"

#define level CLevel::Instance()
#define screen Screen::Instance()
#define renderer Renderer::Instance()
#define resourceManager ResourceManager::Instance()

enum EAppState { SA_NULL, SA_MENU, SA_PLAYING, SA_PAUSE, SA_OPTIONS, SA_GAMEOVER };
extern CGame* g_pGame;
extern EAppState g_wantedState;

#endif
