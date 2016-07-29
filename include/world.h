#ifndef WORLD_H
#define WORLD_H

#include "array.h"
class CEntity;
class Image;
class CPlayer;
class Font;

class CWorld {

public:
	CWorld();
	~CWorld();
	void Init();
	void Run();
	void Draw();
	void SetNumberOfEnemies(int32 numberOfEnemies){ m_enemiesOnScreen = numberOfEnemies; };
	void SetEnemyLife(int32 enemyLife){ m_enemyLife = enemyLife; };
	void CreateEnemies();
	void CreateBoss();
	void CreateBullet();
	void CalculateCollisions();
	void DeleteBullets(bool all); //true, all bullets are deleted, false only the ones that are out of the screen
	void DeleteEnemies();
private:
	Image* bg, *bala, *nave, *base, *caza, *falcon;
	Font* m_pFont; //To print base life
	CPlayer* m_pPlayer; //We keep a pointer to the player because createBullet need it
	Array<CEntity*> m_entities;
	int32 m_enemiesNumber = 0;
	int32 m_enemiesOnScreen = 0; // this value is changed when we set the difficulty
	int32 m_enemyLife = 0; // this value is changed when we set the difficulty
	int32 m_baseLife;
	bool m_bossCreated = false;
};

#endif