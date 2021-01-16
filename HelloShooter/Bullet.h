#ifndef INCLUDE_BULLET_H
#define INCLUDE_BULLET_H

#include"XEngine.h"

class Bullet
{
public:
	void Load(std::string textureName, std::string textureName2);
	void Unload();
	void Update(float deltaTime);
	void Render();
	
	void FireBullet(const X::Math::Vector2& position, X::Math::Vector2& velocity, bool friendly);
	bool IsActive() const { return mActive; }
	bool IsFriendly() const { return mFriendly; }
	void killBullet();
	const X::Math::Vector2 GetPosition() const { return mPosition; }
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(mPosition, 10.0f); }


private:
	// Default Member Initializer
	// Syntactic Sugar
	X::Math::Vector2 mPosition{ 0.0f,0.0f };
	X::Math::Vector2 mVelocity{ 0.0f,0.0f };
	X::TextureId mTextureId{ 0 };
	X::TextureId mTextureId2{ 0 };
	bool mActive{ false };
	bool mFriendly{ false };
};



#endif // #ifndef INCLUDE_BULLET_H
