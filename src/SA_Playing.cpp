
#include "../include/SA_Playing.h"
#include "../include/SA_Menu.h"
#include "../include/globales.h"

void SA_Playing::ProcessInput() {
	g_pGame->ProcessInput();
}

void SA_Playing::Run() {
	g_pGame->Run();
}

void SA_Playing::Draw() {
	g_pGame->Draw();
}

void SA_Playing::Activate() {

}

void SA_Playing::Deactivate() {

}