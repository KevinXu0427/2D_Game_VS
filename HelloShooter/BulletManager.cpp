#include "BulletManager.h"

namespace {
	std::unique_ptr<BulletManager> sInstance;
}

void BulletManager::staticInitialize()
{
	sInstance = std::make_unique<BulletManager>();
	sInstance->Initialize();
}

void BulletManager::staticTerminate()
{
	if (sInstance)
	{
		sInstance->Terminate();
		sInstance.reset();
	}
}

BulletManager * BulletManager::Get()
{
	return sInstance.get();
}

void BulletManager::Initialize()
{
	for (auto& bullet : mBullets)
	{
		bullet.Load("bullet1.png","bullet2.png");
	}
}

void BulletManager::Terminate()
{
	for (auto& bullet : mBullets)
	{
		bullet.Unload();
	}
}

void BulletManager::Update(float deltaTime)
{
	for (auto& bullet : mBullets)
	{
		bullet.Update(deltaTime);
	}
}

void BulletManager::Render()
{
	for (auto& bullet : mBullets)
	{
		bullet.Render();
	}
}

void BulletManager::FireBullet(const X::Math::Vector2 & position, X::Math::Vector2 & velocity, bool friendly)
{
	mBullets[mNextBullet].FireBullet(position, velocity, friendly);
	mNextBullet = (mNextBullet + 1) % std::size(mBullets);
}
