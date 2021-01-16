#include "Bullet.h"

void Bullet::Load(std::string textureName, std::string textureName2)
{
	mTextureId = X::LoadTexture(textureName.c_str());
	mTextureId2 = X::LoadTexture(textureName2.c_str());
}

void Bullet::Unload()
{
	mTextureId = 0;
}

void Bullet::Update(float deltaTime)
{
	if (IsActive())
	{
		mPosition += mVelocity * deltaTime;
	}

}

void Bullet::Render()
{
	if (IsActive())
	{
		
		if (!IsFriendly())
		{
			X::DrawSprite(mTextureId2, mPosition);
		}
		else
		{
			X::DrawSprite(mTextureId, mPosition);
		}
	}
	
}

void Bullet::FireBullet(const X::Math::Vector2 & position, X::Math::Vector2 & velocity, bool friendly)
{
	mActive = true;
	mFriendly = friendly;
	mPosition = position;
	mVelocity = velocity;
}

void Bullet::killBullet()
{
	mActive = false;
}
