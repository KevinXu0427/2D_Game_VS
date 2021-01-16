#include "EnemyManager.h"

namespace 
{
	std::unique_ptr<EnemyManager> sInstance;
}

void EnemyManager::staticInitialize()
{
	sInstance = std::make_unique<EnemyManager>();
	sInstance->Initialize();
}

void EnemyManager::staticTerminate()
{
	if (sInstance)
	{
		sInstance->Terminate();
		sInstance.reset();
	}
}


EnemyManager * EnemyManager::Get()
{
	return sInstance.get();
}

void EnemyManager::Initialize()
{
	for (auto& enemy : mEnemy)
	{
		enemy.Load("enemyship.png");
		enemy.LoadExplode("boom.png");
		enemy.SetPosition({ 0.0f, 0.0f });
		enemy.SetSpeed(enemySpeed);
	}
}

void EnemyManager::Terminate()
{
	for (auto& enemy : mEnemy)
	{
		enemy.Unload();
	}
}

void EnemyManager::Update(float deltaTime)
{
	for (auto& enemy : mEnemy)
	{
		enemy.SetFighterPos(mFighterPos);
		enemy.Update(deltaTime);
	}
}

void EnemyManager::Render()
{
	for (auto& enemy : mEnemy)
	{
		enemy.Render();
	}
}

void EnemyManager::SpawnEnemy()
{
	

	if (mSpawnWaitTime < X::GetTime()) // is it timet o spawn yet
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		float randPos = 0.0f;
		float randSpe = 0.0f;

		std::uniform_int_distribution<> dis1(30, 1000);
		randPos = (float)dis1(gen);
		std::uniform_int_distribution<> dis2(100, 500);
		randSpe = (float)dis2(gen);
		enemySpeed = { 0.0f, randSpe };
		mEnemy[mNextEnemy].SetPosition({ randPos,20.0f });
		mEnemy[mNextEnemy].SetSpeed(enemySpeed);
		mEnemy[mNextEnemy].SetCountKills(mKills);
		mEnemy[mNextEnemy].LauchEnemy();
		mNextEnemy = (mNextEnemy + 1) % std::size(mEnemy);

		// every 1 second.
		mSpawnWaitTime = mSpawnWaitTime + 0.5f;
	}
}
