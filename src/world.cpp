
#include "../include/world.h"
#include "../include/globales.h"
#include "../include/entity.h"
#include "../include/player.h"
#include "../include/base.h"
#include "../include/boss.h"
#include "../include/enemy.h"
#include "../include/bullet.h"
#include <ctime>
#include <cstdlib>

#define ENEMYOFFSETX 30 //to avoid the enemy appear in the screen suddenly
#define ENEMYOFFSETY 30
#define BULLETVELOCITY 100
#define BOSSVELOCITY 20
#define BASELIFEX 30 //position of the life text
#define BASELIFEY 30

CWorld::CWorld() {
	Init();
}

CWorld::~CWorld() {
	//Delete all entities
	for (int32 i = 0; i < m_entities.Size(); i++) {
		delete m_entities[i];
		m_entities[i] = nullptr;
	}
	resourceManager.FreeResources(); //delete sprites and images
}

void CWorld::Init() {
	//Load images for sprites
	bg = resourceManager.LoadImage("data/bg.png");
	nave = resourceManager.LoadImage("data/nave.png");
	caza = resourceManager.LoadImage("data/caza.png");
	base = resourceManager.LoadImage("data/estrella.png");
	bala = resourceManager.LoadImage("data/bala.png");
	falcon = resourceManager.LoadImage("data/boss.png");
	nave->SetMidHandle();
	caza->SetMidHandle();
	base->SetMidHandle();
	bala->SetMidHandle();
	falcon->SetMidHandle();
	//Load the font
	m_pFont = resourceManager.LoadFont("data/monospaced.png");
	//Create the player
	Sprite* s_player = new Sprite(caza);
	s_player->SetScale(0.2, 0.2);
	s_player->SetColor(0, 0, 255, 0);
	m_pPlayer = new CPlayer(s_player, 1);
	m_pPlayer->SetRadius(caza->GetWidth() / 3 * 0.2);
	m_entities.Add(m_pPlayer);
	//Create the base
	Sprite* s_base = new Sprite(base);
	s_base->SetScale(0.5, 0.5);
	m_baseLife = 5; //a variable to save the life in this particular case, just to not calling GetLife and SetTime so many times
	CBase* base = new CBase(s_base, m_baseLife);
	base->SetPos(screen.GetWidth() / 2, screen.GetHeight() / 2);
	m_entities.Add(base);
}

void CWorld::Run() {
	//We create the boss in the third level instead of enemies
	if (level.GetNumberLevel() != 3) {
		CreateEnemies();
	}
	else{
		CreateBoss();
	}

	DeleteBullets(false); //delete bullets that are out of the screen
	CalculateCollisions();
	for (int32 i = 0; i < m_entities.Size(); i++) {
		m_entities[i]->Run();
	}
}

void CWorld::Draw() {
	//Draw the background
	renderer.DrawImage(bg,0,0,0,screen.GetWidth(),screen.GetHeight());
	//Draw the current info in the ScreenTitle, depending on the level
	switch(level.GetNumberLevel()) {
		case 1:
			screen.SetTitle(level.GetNameLevel() + " " + String::FromInt(level.GetNumberGoal()));
			break;
		case 2:
			screen.SetTitle(level.GetNameLevel() + " " + String::FromFloat(level.GetNumberGoal()));
			break;
		case 3:
			screen.SetTitle(level.GetNameLevel() + " Life: " + String::FromInt(level.GetNumberGoal()*m_enemyLife));
			break;
	}

	String string = "Death Star Life: ";
	renderer.DrawText(m_pFont, string + String::FromInt(m_baseLife), BASELIFEX, BASELIFEY);
	//Draw entites
	for (int32 i = 0; i < m_entities.Size(); i++) {
		m_entities[i]->Draw();
	}

	screen.Refresh();
	renderer.Clear();
}

void CWorld::CreateEnemies() {
	//Set the rand seed
	srand(time(0));
	while (m_enemiesNumber < m_enemiesOnScreen) {
		int32 screenSide = rand() % 4; //
		switch (screenSide) {
			case 0: //left
			{
				Sprite* s_enemy = new Sprite(nave);
				s_enemy->SetScale(0.2, 0.2);
				CEnemy* enemy = new CEnemy(s_enemy, m_enemyLife);
				enemy->SetPos(-ENEMYOFFSETX, rand() % screen.GetHeight());
				enemy->SetRadius(nave->GetHeight() / 4 * 0.2);
				enemy->SetVelocity(rand() % 50 + 50);
				m_entities.Add(enemy);
				m_enemiesNumber++;
				break;
			}
			case 1: //up
			{
				Sprite* s_enemy = new Sprite(nave);
				s_enemy->SetScale(0.2, 0.2);
				CEnemy* enemy = new CEnemy(s_enemy, m_enemyLife);
				enemy->SetPos(rand() % screen.GetWidth(), -ENEMYOFFSETY);
				enemy->SetRadius((nave->GetHeight() / 4)*0.2);
				enemy->SetVelocity(rand() % 50 + 50);
				m_entities.Add(enemy);
				m_enemiesNumber++;
				break;
			}
			case 2: //right
			{
				Sprite* s_enemy = new Sprite(nave);
				s_enemy->SetScale(0.2, 0.2);
				CEnemy* enemy = new CEnemy(s_enemy, m_enemyLife);
				enemy->SetPos(screen.GetWidth() + ENEMYOFFSETX, rand() % screen.GetHeight());
				enemy->SetRadius((nave->GetHeight() / 4)*0.2);
				enemy->SetVelocity(rand() % 50 + 50);
				m_entities.Add(enemy);
				m_enemiesNumber++;
				break;
			}
			case 3: //down
			{
				Sprite* s_enemy = new Sprite(nave);
				s_enemy->SetScale(0.2, 0.2);
				CEnemy* enemy = new CEnemy(s_enemy, m_enemyLife);
				enemy->SetPos(rand() % screen.GetWidth(), screen.GetHeight() + ENEMYOFFSETY);
				enemy->SetRadius((nave->GetHeight() / 4)*0.2);
				enemy->SetVelocity(rand() % 50 + 50);
				m_entities.Add(enemy);
				m_enemiesNumber++;
				break;
			}
		}
	}
}

void CWorld::DeleteEnemies() {
	for (int32 i = 0; i < m_entities.Size(); i++) {
		if (m_entities[i]->GetId() == EENEMY) {
			delete m_entities[i];
			m_entities.RemoveAt(i);
			i--;
		}
	}

	m_enemiesNumber = 0;
}

void CWorld::CreateBoss() {
	if (!m_bossCreated) {
		Sprite* s_boss = new Sprite(falcon);
		s_boss->SetScale(0.2, 0.2);
		CBoss* boss = new CBoss(s_boss, level.GetNumberGoal() * m_enemyLife); //change the boss life, depending on the difficulty (or enemyLife)
		boss->SetPos(rand() % screen.GetWidth(), screen.GetHeight() + ENEMYOFFSETY);
		boss->SetRadius(falcon->GetHeight() /3 *0.2);
		boss->SetVelocity(BOSSVELOCITY);
		m_entities.Add(boss);
		m_bossCreated = true;
	}
}

void CWorld::CreateBullet() {
	Sprite* s_bullet = new Sprite(bala);
	s_bullet->SetScale(0.1, 0.1);
	CBullet* bullet = new CBullet(s_bullet, 1);
	bullet->SetRadius(nave->GetHeight() / 2 * 0.1);
	//Calculate the distance to set direction
	double playerX = m_pPlayer->GetPosX();
	double playerY = m_pPlayer->GetPosY();
	double mouseX = g_pGame->GetUserInterface()->GetMouseX();
	double mouseY = g_pGame->GetUserInterface()->GetMouseY();
	double distancia = Distance(playerX, playerY, mouseX, mouseY);
	bullet->SetDir((mouseX - playerX) / distancia, ((mouseY - playerY) / distancia));
	//The bullet starts in the player position
	bullet->SetPos(playerX, playerY);
	bullet->SetVelocity(BULLETVELOCITY);
	m_entities.Add(bullet);
}

void CWorld::DeleteBullets(bool all) {
	for (int32 i = 0; i < m_entities.Size(); i++) {
		if (m_entities[i]->GetId() == EBULLET) {
			if (!all) {
				if (m_entities[i]->GetPosX() < 0 || m_entities[i]->GetPosX() > screen.GetWidth() ||
					m_entities[i]->GetPosY() < 0 || m_entities[i]->GetPosY() > screen.GetHeight())
				{
					delete m_entities[i];
					m_entities.RemoveAt(i);
					i--;
				}
			}
			else {
				delete m_entities[i];
				m_entities.RemoveAt(i);
				i--;
			}
		}
	}
}

void CWorld::CalculateCollisions() {
	for (int32 i = 0; i < m_entities.Size(); i++) {
		for (int32 j = 0; j < m_entities.Size(); j++) {
			//Enemy bullet
			if (m_entities[i]->GetId() == EENEMY && m_entities[j]->GetId() == EBULLET) {
				double distanceEnemyBullet = Distance(m_entities[i]->GetPosX(), m_entities[i]->GetPosY(), m_entities[j]->GetPosX(), m_entities[j]->GetPosY());
				if (distanceEnemyBullet < (m_entities[i]->GetRadius() + m_entities[j]->GetRadius())) {
					//We delete the bullet, remove it from the array so j is decreased
					delete m_entities[j];
					m_entities.RemoveAt(j);
					j--;
					//We get the enemy life to check if we have to kill him
					int32 life = m_entities[i]->GetLife();
					m_entities[i]->SetLife(--life);
					if (life == 0) {
						delete m_entities[i];
						m_entities.RemoveAt(i);
						i--;
						m_enemiesNumber--;
						i--;
						//In the first level, goal is decrased if we kill a enemy
						if (level.GetNumberLevel() == 1) {
							int32 numberGoal = level.GetNumberGoal();
							level.SetNumberGoal(--numberGoal);
						}
					}
				}
			}

			//Enemy base
			if (m_entities[i]->GetId() == EENEMY && m_entities[j]->GetId() == EBASE) {
				if (m_entities[i]->GetPosX() == screen.GetWidth() / 2 && m_entities[i]->GetPosY() == screen.GetHeight() / 2) {
					delete m_entities[i];
					m_entities.RemoveAt(i);
					i--;
					m_enemiesNumber--;
					m_baseLife--;
					if (m_baseLife == 0) {
						g_pGame->SetGameComplete(false);
						g_wantedState = SA_GAMEOVER;
					}
				}
			}

			//Enemy player
			if (m_entities[i]->GetId() == EENEMY && m_entities[j]->GetId() == EPLAYER) {
				double distanceEnemyPlayer = Distance(m_entities[i]->GetPosX(), m_entities[i]->GetPosY(), m_pPlayer->GetPosX(), m_pPlayer->GetPosY());
				if (distanceEnemyPlayer < (m_pPlayer->GetRadius() + m_entities[i]->GetRadius())) {
					g_pGame->SetGameComplete(false);
					g_wantedState = SA_GAMEOVER;
				}
			}

			//Boss player
			if (m_entities[i]->GetId() == EBOSS && m_entities[j]->GetId() == EPLAYER) {
				double distanceEnemyPlayer = Distance(m_entities[i]->GetPosX(), m_entities[i]->GetPosY(), m_pPlayer->GetPosX(), m_pPlayer->GetPosY());
				if (distanceEnemyPlayer < (m_pPlayer->GetRadius() + m_entities[i]->GetRadius())) {
					g_pGame->SetGameComplete(false);
					g_wantedState = SA_GAMEOVER;
				}
			}

			//Boss bullet
			if (m_entities[i]->GetId() == EBOSS && m_entities[j]->GetId() == EBULLET) {
				double distanceBossBullet = Distance(m_entities[i]->GetPosX(), m_entities[i]->GetPosY(), m_entities[j]->GetPosX(), m_entities[j]->GetPosY());
				if (distanceBossBullet < (m_entities[i]->GetRadius() + m_entities[j]->GetRadius())) {
					delete m_entities[j];
					m_entities.RemoveAt(j);
					j--;
					int32 life = m_entities[i]->GetLife();
					m_entities[i]->SetLife(--life);
					level.SetNumberGoal(m_entities[i]->GetLife());
					if (life == 0){
						g_pGame->SetGameComplete(true);
						g_wantedState = SA_GAMEOVER;
					}
				}
			}

			//Boss base
			if (m_entities[i]->GetId() == EBOSS && m_entities[j]->GetId() == EBASE) {
				if (m_entities[i]->GetPosX() == screen.GetWidth() / 2 && m_entities[i]->GetPosY() == screen.GetHeight() / 2) {
						g_pGame->SetGameComplete(false);
						g_wantedState = SA_GAMEOVER;
				}
			}
		}
	}
}