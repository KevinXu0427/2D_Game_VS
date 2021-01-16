#ifndef INCLUDE_BULLETMANAGER_H
#define INCLUDE_BULLETMANAGER_H

#include"Bullet.h"

class BulletManager
{
public:
	static void staticInitialize();
	static void staticTerminate();
	static BulletManager* Get();

public:
	void Initialize();
	void Terminate();

	void Update(float deltaTime);
	void Render();
	void FireBullet(const X::Math::Vector2& position, X::Math::Vector2& velocity, bool friendly);
	Bullet& GetBullet(size_t index) { return mBullets[index]; }
	size_t GetBulletCount() const { return std::size(mBullets); }

private:
	Bullet mBullets[1024];
	int mNextBullet{ 0 };
};



#endif // #ifndef INCLUDE_BULLETMANAGER_H
