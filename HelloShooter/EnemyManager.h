#ifndef INCLUDE_ENEMYMANAGER_H
#define INCLUDE_ENEMYMANAGER_H

#include "Enemy.h"

class EnemyManager
{
public:
	static void staticInitialize();
	static void staticTerminate();
	static EnemyManager* Get();

public:
	void Initialize();
	void Terminate();

	void Update(float deltaTime);
	void Render();
	void SpawnEnemy();
	void SetFighterpos(X::Math::Vector2 pos) { mFighterPos = pos; }
	void SetCountKill(int index) { mKills = index; }
	void SetmSpawTime(float time) { mSpawnWaitTime = time; }
	Enemy& GetEnemy(size_t index) { return mEnemy[index]; }
	size_t GetEnemyCount() const { return std::size(mEnemy); }

private:
	Enemy mEnemy[20];
	int mNextEnemy = 0;
	X::Math::Vector2 enemySpeed = { 0.0f,0.0f };
	float mSpawnWaitTime = X::GetTime();
	X::Math::Vector2 mFighterPos{ 0.0f,0.0f };
	int mKills{ 0 };

};



#endif // #ifndef INCLUDE_ENEMYMANAGER_H
