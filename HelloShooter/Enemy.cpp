#include "Enemy.h"
#include "BulletManager.h"
#include "Fighter.h"
void Enemy::Load(std::string textureName)
{
	mTextureId = X::LoadTexture(textureName.c_str());
	
}

void Enemy::Unload()
{
	mTextureId = 0;

}

void Enemy::Update(float deltaTime)
{
	if (IsActive())
	{
		mPosition += mSpeed * deltaTime;

		
	}

	if (IsActive() && mNextFireTime < X::GetTime())
	{
		X::Math::Vector2 fighterPos = mFighterPosition;
		X::Math::Vector2 position = GetPosition();

		X::Math::Vector2 magnitude = fighterPos - position;
		float unitNum = X::Math::Sqrt((magnitude.x * magnitude.x) + (magnitude.y * magnitude.y));
		unitNum = 1.0f / unitNum;
		X::Math::Vector2 velocity = { 300.f * (unitNum * magnitude.x), 300.f * (unitNum * magnitude.y) };
		
		//X::Math::Vector2 velocity = { (magnitude.x),(magnitude.y) };
		//X::Math::Vector2 velocity{ 0.0f, 600.0f };

		BulletManager::Get()->FireBullet(position, velocity, false);

		// Advance next fire time into 0.1 second in the future
		mNextFireTime = X::GetTime() + 2.5f;
	}
	
}

void Enemy::Render()
{

	if (IsActive())
	{
		X::DrawSprite(mTextureId, mPosition);
	}
	if (explodeTime < 30)
	{
		X::DrawSprite(mExplodeTextureId, mPosition);
		explodeTime++;
	}
	
}

void Enemy::LoadExplode(std::string textureName)
{
	mExplodeTextureId = X::LoadTexture(textureName.c_str());
}

void Enemy::killEnemy()
{
	mHealth--;
	if (mHealth == 0)
	{
		mActive = false;
		explodeTime = 0;
	}
}

void Enemy::LauchEnemy()
{
	if (mCountEnemyKill < 10)
	{
		mHealth = 2;
	}
	if ((mCountEnemyKill >= 20) && (mCountEnemyKill < 50))
	{
		mHealth = 4;
	}
	if (mCountEnemyKill >= 50)
	{
		mHealth = 6;
	}
	mActive = true;
}

void Enemy::ResetEnemy()
{
	mActive = false;
}
