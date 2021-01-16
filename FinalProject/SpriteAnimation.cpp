#include "SpriteAnimation.h"

void SpriteAnimation::Load(Info info)
{
	mInfo = std::move(info);
	mSpriteSheetId = X::LoadTexture(mInfo.fileName.c_str());
	mTimer = 0.0f;
}

void SpriteAnimation::Unload()
{
	mSpriteSheetId = 0;
}

void SpriteAnimation::Update(float deltaTime)
{
	if (mActive)
	{
		mTimer += mInfo.framePerSecond * deltaTime;

		if (!mInfo.looping && mTimer >= mInfo.frameCount)
		{
			Stop();
		}

	}
}

void SpriteAnimation::Render()
{
	if (mActive)
	{
		int frameIndex = static_cast<int>(mTimer) % mInfo.frameCount;
		int column = frameIndex % mInfo.columns;
		int row = frameIndex / mInfo.columns;
		float frameWidth = X::GetSpriteWidth(mSpriteSheetId) / mInfo.columns;
		float frameHeight = X::GetSpriteHeight(mSpriteSheetId) / mInfo.rows;

		X::Math::Rect rect;
		rect.left = column * frameWidth;
		rect.right = (column + 1) * frameWidth;
		rect.top = row * frameHeight;
		rect.bottom = (row + 1) * frameHeight;

		X::DrawSprite(mSpriteSheetId, rect, mPosition);
	}
}

void SpriteAnimation::Play()
{
	mTimer = 0.0f;
	mActive = true;
}

void SpriteAnimation::Stop()
{
	mActive = false;
}
