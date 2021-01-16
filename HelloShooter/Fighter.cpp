#include "Fighter.h"
#include "BulletManager.h"

void Fighter::Load(std::string textureName, std::string textureName2, std::string textureExplode, std::string textureHeart)
{
	mTextureId = X::LoadTexture(textureName.c_str());
	mTextureId2 = X::LoadTexture(textureName2.c_str());
	mExplodeTextureId = X::LoadTexture(textureExplode.c_str());
	mHeartTextureId = X::LoadTexture(textureHeart.c_str());
	mActive = true;
}

void Fighter::Unload()
{
	mExplodeTextureId = 0;
	mTextureId = 0;
	mTextureId2 = 0;
}

void Fighter::Update(float deltaTime)
{
	
	if (X::IsKeyDown(X::Keys::RIGHT))
	{
		if (mPosition.x < (X::GetScreenWidth() - X::GetSpriteWidth(mTextureId) * 0.5f))
		{
			mPosition.x += mSpeed * deltaTime;
		}
		
	}
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		if (mPosition.x > (X::GetSpriteWidth(mTextureId) * 0.5f))
		{
			mPosition.x -= mSpeed * deltaTime;

		}
		
	}
	if (X::IsKeyDown(X::Keys::UP))
	{
		if (mPosition.y > (X::GetSpriteHeight(mTextureId) * 0.5f))
		{
			mPosition.y -= mSpeed * deltaTime;
			mEnginFrame = 0;
		}
		
	}

	if (X::IsKeyDown(X::Keys::DOWN))
	{
		if (mPosition.y < (X::GetScreenHeight() - X::GetSpriteHeight(mTextureId) * 0.5f))
		{
			mPosition.y += mSpeed * deltaTime;
		}
		
	}

	if (X::IsKeyDown(X::Keys::SPACE) && mNextFireTime < X::GetTime())
	{
		X::Math::Vector2 position0 = GetPosition();
		X::Math::Vector2 position1 = { position0.x + 20.0f, position0.y };
		X::Math::Vector2 position2 = { position0.x - 20.0f, position0.y };

		X::Math::Vector2 velocity0{ -50.0f, -500.0f };
		X::Math::Vector2 velocity1{ 0.0f, -500.0f };
		X::Math::Vector2 velocity2{ 50.0f, -500.0f };

		if (mNumOfKills >= 0 && mNumOfKills < 5)
		{
			BulletManager::Get()->FireBullet(position0, velocity1, true);
			// Advance next fire time into 0.1 second in the future
			mNextFireTime = X::GetTime() + 0.2f;
		}
		else if (mNumOfKills >= 5 && mNumOfKills < 10)
		{
			BulletManager::Get()->FireBullet(position1, velocity1, true);
			BulletManager::Get()->FireBullet(position2, velocity1, true);
			// Advance next fire time into 0.1 second in the future
			mNextFireTime = X::GetTime() + 0.2f;
		}
		else if (mNumOfKills >= 10)
		{
			BulletManager::Get()->FireBullet(position0, velocity1, true);
			BulletManager::Get()->FireBullet(position2, velocity0, true);
			BulletManager::Get()->FireBullet(position1, velocity2, true);


			// Advance next fire time into 0.1 second in the future
			mNextFireTime = X::GetTime() + 0.1f;
		}

		
	}

}

void Fighter::Render()
{
	
	if (IsActive())
	{
		if (mEnginFrame < 5)
		{
			X::DrawSprite(mTextureId2, mPosition);
			mEnginFrame++;
		}
		else
		{
			X::DrawSprite(mTextureId, mPosition);
		}
	}
	else
	{
		if (explodeTime < 30)
		{
			X::DrawSprite(mExplodeTextureId, mPosition);
			explodeTime++;
		}
	}
	

}

void Fighter::Destroy()
{
	explodeTime = 0;
	mActive = false;
}

void Fighter::PrintInfo()
{
	float xPos = 10.0f;
	float yPos = 20.0f;
	float textSize = 24.0f;

	

	std::string score;
	std::stringstream ss;
	ss << GetNumOfKills();
	score = ss.str();

	X::DrawScreenText("Score: ", xPos, yPos, textSize, X::Math::Vector4::Magenta());
	X::DrawScreenText(score.c_str(), xPos + 100, yPos, textSize, X::Math::Vector4::Magenta());
	
	if (mHeart == 1)
	{
		X::DrawSprite(mHeartTextureId, { xPos + 20.f, yPos + 60.0f });
	}
	if (mHeart == 2)
	{
		X::DrawSprite(mHeartTextureId, { xPos + 20.f, yPos + 60.0f });
		X::DrawSprite(mHeartTextureId, { xPos + 80.0f, yPos + 60.0f });
	}
	if (mHeart == 3)
	{
		X::DrawSprite(mHeartTextureId, { xPos + 20.f, yPos + 60.0f });
		X::DrawSprite(mHeartTextureId, { xPos + 80.0f, yPos + 60.0f });
		X::DrawSprite(mHeartTextureId, { xPos + 140.0f, yPos + 60.0f });
	}
	
	if (mNumOfKills >= 0 && mNumOfKills < 5)
	{
		
		X::DrawScreenText("Leve: 1 (Enemy Health 2)", X::GetScreenWidth() * 0.4f, yPos, textSize, X::Math::Vector4::Magenta());
	}
	else if (mNumOfKills >= 5 && mNumOfKills < 10)
	{
		
		X::DrawScreenText("Leve: 2 (Enemy Health 4)", X::GetScreenWidth() * 0.4f, yPos, textSize, X::Math::Vector4::Magenta());
	}
	else if (mNumOfKills >= 10)
	{
		
		X::DrawScreenText("Leve: 3 (Enemy Health 6)", X::GetScreenWidth() * 0.4f, yPos, textSize, X::Math::Vector4::Magenta());
	}




}

