#ifndef INCLUDE_FIGHTER_H
#define INCLUDE_FIGHTER_H

#include"XEngine.h"

class Fighter
{
public:
	void Load(std::string textureName, std::string textureName2, std::string textureExplode, std::string textureHeart);
	void Unload();
	void Update(float deltaTime);
	void Render();

	bool IsActive() const { return mActive; }
	void ResetmActive(bool value) { mActive = value; };
	X::Math::Vector2& GetPosition() { return mPosition; }
	void SetPosition(const X::Math::Vector2& position)  { mPosition = position; }
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetNumOfKills(int count) { mNumOfKills = count; }
	void SetHealth(int count) { mHeart = count; }
	const int GetHealth() const { return mHeart; }
	const int GetNumOfKills() const { return mNumOfKills; }
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(mPosition, 23.5); }
	void Destroy();
	void PrintInfo();

private:
	// Default Member Initializer
	// Syntactic Sugar
	// 'm' stands for member
	X::Math::Vector2 mPosition{ 0.0f,0.0f };
	X::TextureId mTextureId{ 0 };
	X::TextureId mTextureId2{ 0 };
	X::TextureId mHeartTextureId{ 0 };
	float mSpeed{ 0 };
	int mEnginFrame = 6;
	float mNextFireTime = 0.0f;
	int explodeTime = 31;
	X::TextureId mExplodeTextureId{ 0 };
	bool mActive{ false };
	int mNumOfKills{ 0 };
	int mHeart;
};



#endif // #ifndef INCLUDE_FIGHTER_H
