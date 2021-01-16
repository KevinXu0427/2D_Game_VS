#include "BackgroundManager.h"
#include "Enemy.h"
#include "EnemyManager.h"
void BgSetup::Load(std::string textureName, std::string textureName2)
{
	
	mTextureId = X::LoadTexture(textureName.c_str());
	mTextureId2 = X::LoadTexture(textureName2.c_str());

	mBgImageWidth = (float)X::GetSpriteWidth(mTextureId);
	mBgImageHeight = (float)X::GetSpriteHeight(mTextureId);
}

void BgSetup::Unload()
{
	mTextureId = 0;
	mTextureId2 = 0;
}

void BgSetup::Update(float deltaTime)
{
	if (mPosition.y > (mScreenHeight * 0.45f) + mScreenHeight)
	{
		mActive = true;
	}
	if (mPosition2.y > (mScreenHeight * 0.45f) + mScreenHeight)
	{
		mActive2 = true;
	}
	if (mActive)
	{
		mPosition.y = mPosition2.y - X::GetSpriteHeight(mTextureId2);
		mActive = false;
	}
	if (mActive2)
	{
		mPosition2.y = mPosition.y - X::GetSpriteHeight(mTextureId);
		mActive2 = false;
	}

	if (X::IsKeyDown(X::Keys::UP))
	{
		mPosition.y += (mSpeed + 100.f) * deltaTime;
		mPosition2.y += (mSpeed + 100.f) * deltaTime;

	}
	if (X::IsKeyDown(X::Keys::DOWN))
	{
		mPosition.y += (mSpeed - 100.f) * deltaTime;
		mPosition2.y += (mSpeed - 100.f) * deltaTime;
	}
	else
	{
		mPosition.y += mSpeed * deltaTime;
		mPosition2.y += mSpeed * deltaTime;
	}
	
}

void BgSetup::Render()
{
	X::DrawSprite(mTextureId, mPosition);
	X::DrawSprite(mTextureId2, mPosition2);
	
}

void BgSetup::SetScreenInfo(float width, float height)
{
	mScreenHeight = height;
	mScreenWidth = width;
	mPosition = { width * 0.5f, height * 0.5f };
	mPosition2 = { width * 0.5f,  -height * 0.5f };
}
