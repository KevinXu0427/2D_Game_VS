#include "BackGroundManager.h"

void BgSetup::Load(std::string textures[])
{
	mTextureIds = std::make_unique<X::TextureId[]>(textures->size());
	mTextureIds[0] = X::LoadTexture(textures[0].c_str());
	mTextureIds[1] = X::LoadTexture(textures[1].c_str());

}

void BgSetup::Unload()
{
	mTextureIds.reset();
}

void BgSetup::Update(float deltaTime)
{
	float speed = 500.0f;
	if (IsLoadFinished())
	{
		if (mPositionBg.y > X::GetSpriteHeight(mTextureIds[0]) * 1.8f)
		{
			mLoadFinished = false;
			mStart = true;
		}
		else
		{
			mPositionBg.y += speed * deltaTime;
		}
	}
}

void BgSetup::Render()
{
	if (IsEndGame())
	{
		X::DrawSprite(mTextureIds[0], mPositionBgRing);
	}
	else
	{
		X::DrawSprite(mTextureIds[1], mPositionBgRing);
		X::DrawSprite(mTextureIds[0], mPositionBg);
	}
}

void BgSetup::SetScreenInfo(float width, float height)
{
	mPositionBg.x = width * 0.5f;
	mPositionBg.y = height * 0.5f;

	mPositionBgRing = mPositionBg;
}
