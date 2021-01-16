#include"Fighter.h"
#include"BulletManager.h"
#include"Enemy.h"
#include"EnemyManager.h"
#include"BackgroundManager.h"
#include<XEngine.h>
#include<random>

Fighter myFighter;
BgSetup myBg;

int screenWidth = 0;
int screenHeight = 0;

void BulletsCollisions();
void ShipCollisions();
void BulletsAndEnmeyclean();
int health{ 3 };
int countNumOfKills{ 0 };
bool IntersectMath(X::Math::Circle c1, X::Math::Circle c2);
float shipSpeed = 500.0f;

enum class GameState
{
	StartScreen,
	Gameplay,
	GameOver
};

GameState gameState;

void GameInit()
{
	screenWidth = X::GetScreenWidth();
	screenHeight = X::GetScreenHeight();
	myFighter.Load("spaceshipT2.png", "spaceshipT1.png", "boom.png", "heart.png");
	myFighter.SetPosition({ screenWidth * 0.5f, screenHeight * 0.5f });
	myFighter.SetSpeed(shipSpeed);
	myFighter.SetHealth(health);

	myBg.Load("background.png", "background.png");
	myBg.SetScreenInfo((float)screenWidth, (float)screenHeight);

	BulletManager::staticInitialize();
	EnemyManager::staticInitialize();
	
}

void GameLoopStart(float deltaTime)
{
	float xPos = screenWidth * 0.4f;
	float yPos = screenHeight * 0.3f;

	float textSize = 24.0f;
	float textSize1 = 64.0f;
	// print the header
	X::DrawScreenText("SPACE SHOOTER \n", xPos-10.0f, yPos - 100.0f, 50, X::Math::Vector4(0.50f, 0.5, 0.0f, 1.0f));
	X::DrawScreenText("Start Game(Press Y) \n Quit (Press Esc)", xPos-10.0f, yPos, textSize, X::Math::Vector4(0.50f, 1.0f, 0.0f, 1.0f));
	X::DrawScreenText("Info:\n Level 1: \n Enemy health = 2\n Kill Count under 20 (1 line bullets) \n\n Level 2: \n Enemy health = 4 \n Kill Count 20 - 50 (2 line bullets) \n\n Level 3: \n Enemy health = 6 \n Kill Count over 50 (3 line bullets)", X::GetScreenWidth() * 0.2f, yPos + 50.0f, textSize, X::Math::Vector4(1.0f, 2.0f, 0.0f, 1.0f));

	

	if (X::IsKeyPressed(X::Keys::Y))
	{
		gameState = GameState::Gameplay;
		EnemyManager::Get()->SetmSpawTime(X::GetTime());
		return;
	}

	myBg.Update(deltaTime);
	myBg.Render();
}

void GameLoop(float deltaTime)
{
		// Spawn Enemy
		EnemyManager::Get()->SpawnEnemy();

		// Update
		myFighter.Update(deltaTime);
		myBg.Update(deltaTime);
		EnemyManager::Get()->SetFighterpos(myFighter.GetPosition());

		BulletManager::Get()->Update(deltaTime);
		EnemyManager::Get()->Update(deltaTime);

		// Render
		myBg.Render();
		myFighter.Render();

		BulletManager::Get()->Render();
		EnemyManager::Get()->Render();

		BulletsCollisions();
		ShipCollisions();
		BulletsAndEnmeyclean();

		// Print Score
		myFighter.PrintInfo();
	
}

void ResetGame()
{
	myFighter.SetPosition({ screenWidth * 0.5f, screenHeight * 0.5f });
	myFighter.SetSpeed(shipSpeed);
	myFighter.SetHealth(health);
	myFighter.ResetmActive(true);
	countNumOfKills = { 0 };
	health = { 3 };
	myFighter.SetNumOfKills(countNumOfKills);
	myFighter.SetHealth(health);

	EnemyManager::Get()->SetmSpawTime(X::GetTime());
	EnemyManager::Get()->Initialize();

	for (int i = 0; i < BulletManager::Get()->GetBulletCount(); ++i)
	{
		auto& bullet = BulletManager::Get()->GetBullet(i);
		bullet.killBullet();
	}

	// what else?
}

void GameLoopEnd(float deltaTime)
{
	float xPos = screenWidth * 0.4f;
	float yPos = screenHeight * 0.6f;

	// print the header
	X::DrawScreenText("Play again(Press Y)", xPos, yPos + 50.0f, 24.0f, X::Math::Vector4(1.0f, 2.0f, 0.0f, 1.0f));
	X::DrawScreenText("Quit (Press Esc)", xPos, yPos + 100.0f, 24.0f, X::Math::Vector4(1.0f, 2.0f, 0.0f, 1.0f));

	if (X::IsKeyPressed(X::Keys::Y))
	{
		gameState = GameState::Gameplay;
		ResetGame();
		return;
	}

	X::TextureId textureEnd = X::LoadTexture("gameover.png");
	X::DrawSprite(textureEnd, {screenWidth * 0.5f,screenHeight * 0.5f});

	/*myBg.Update(deltaTime);
	myBg.Render();*/
}

void GameCleanUp()
{
	BulletManager::staticTerminate();
	EnemyManager::staticTerminate();
	myBg.Unload();
	myFighter.Unload();
}

void BulletsAndEnmeyclean()
{
	for (int i = 0; i < EnemyManager::Get()->GetEnemyCount(); ++i)
	{
		auto& enemy = EnemyManager::Get()->GetEnemy(i);
		if (enemy.IsActive())
		{
			X::Math::Vector2 enemypos = enemy.GetPosition();
			if (enemypos.y > screenHeight)
			{
				enemy.ResetEnemy();
			}
		}
	}

	for (int i = 0; i < BulletManager::Get()->GetBulletCount(); ++i)
	{
		auto& bullet = BulletManager::Get()->GetBullet(i);
		if (bullet.IsActive())
		{
			X::Math::Vector2 bulletpos = bullet.GetPosition();
			if (bulletpos.y > screenHeight)
			{
				bullet.killBullet();
			}
			if (bulletpos.y < 0)
			{
				bullet.killBullet();
			}
			if (bulletpos.x > screenWidth)
			{
				bullet.killBullet();
			}
			if (bulletpos.x < 0)
			{
				bullet.killBullet();
			}

		}
	}

}

void BulletsCollisions()
{
	for (size_t i = 0; i < BulletManager::Get()->GetBulletCount(); ++i)
	{
		auto& bullet = BulletManager::Get()->GetBullet(i);
		if (bullet.IsActive())
		{
			if (bullet.IsFriendly())
			{
				for (int j = 0; j < EnemyManager::Get()->GetEnemyCount(); ++j)
				{
					auto& enemy = EnemyManager::Get()->GetEnemy(j);
					if (enemy.IsActive())
					{
						auto bulletCircle = bullet.GetBoundingCircle();
						auto enemyCircle = enemy.GetBoundingCircle();
					
						if (IntersectMath(bulletCircle, enemyCircle))
						{
							bullet.killBullet();
							enemy.killEnemy();
							if (!enemy.IsActive())
							{
								countNumOfKills++;
								myFighter.SetNumOfKills(countNumOfKills);
								EnemyManager::Get()->SetCountKill(countNumOfKills);
							}
							
						}

					}
				}
			}
			else
			{
				auto bulletCircle = bullet.GetBoundingCircle();
				auto myFighterCircle = myFighter.GetBoundingCircle();
				
				if (IntersectMath(bulletCircle, myFighterCircle))
				{
					bullet.killBullet();
					health--;
					myFighter.SetHealth(health);

					if (myFighter.GetHealth() == 0)
					{
						myFighter.Destroy();
						gameState = GameState::GameOver;
					}
				}
			}
		}
	}
}

void ShipCollisions()
{
	for (int i = 0; i < EnemyManager::Get()->GetEnemyCount(); ++i)
	{
		auto& enemy = EnemyManager::Get()->GetEnemy(i);
		if (enemy.IsActive())
		{
			auto enemyCircle = enemy.GetBoundingCircle();
			auto myFighterCircle = myFighter.GetBoundingCircle();

			if (IntersectMath(enemyCircle, myFighterCircle))
			{
				enemy.killEnemy();
				health--; 
				myFighter.SetHealth(health);
				if (myFighter.GetHealth() == 0)
				{
					myFighter.Destroy();
					gameState = GameState::GameOver;
				}
			}
		}
	}
}

bool IntersectMath(X::Math::Circle c1, X::Math::Circle c2)
{
	float radius = c1.radius + c2.radius;
	float radiusSqur = radius * radius;
	X::Math::Vector2 magnitude = { c1.center - c2.center };
	float magnitudeSqur = (magnitude.x * magnitude.x) + (magnitude.y * magnitude.y);
	float disSqur = magnitudeSqur;

	return (disSqur < radiusSqur);
}

bool MainLoop(float deltaTime)
{

	switch (gameState)
	{
	case GameState::StartScreen:
		GameLoopStart(deltaTime);
		break;
	case GameState::Gameplay:
		GameLoop(deltaTime);
		break;
	case GameState::GameOver:
		GameLoopEnd(deltaTime);
		break;
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(MainLoop);

	GameCleanUp();
	X::Stop();
	return 0;
}

// () - Parentheses
// {} - Braces
// <> - Chevrons
// [] - Brackets