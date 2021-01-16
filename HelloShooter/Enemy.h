#ifndef INCLUDE_ENEMY_H
#define INCLUDE_ENEMY_H

#include"XEngine.h"

class Enemy
{
public:
	void Load(std::string textureName);
	void Unload();
	void Update(float deltaTime);
	void Render();
	void LoadExplode(std::string textureName);
	const X::Math::Vector2& GetPosition() const { return mPosition; }
	const X::TextureId& GetTextureId() const { return mTextureId; }
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	void SetSpeed(X::Math::Vector2 speed) { mSpeed = speed; }
	void SetFighterPos(X::Math::Vector2 pos) { mFighterPosition = pos; }
	void SetHealth(int index) { mHealth = index; }
	void SetCountKills(int index) { mCountEnemyKill = index; }
	bool IsActive() const { return mActive; }
	void killEnemy();
	void LauchEnemy();
	void ResetEnemy();
	int GetKillCount() { return mCountEnemyKill; }
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(mPosition, 23.5); }

private:

	X::Math::Vector2 mPosition{ 0.0f,0.0f };
	X::Math::Vector2 mFighterPosition{ 0.0f,0.0f };
	X::TextureId mTextureId{ 0 };
	X::Math::Vector2 mSpeed{ 0.0f,0.0f };
	bool mActive{ false };
	int explodeTime = 31;
	X::TextureId mExplodeTextureId{ 0 };
	float mNextFireTime{ 0 };
	int mHealth{ 2 };
	int mCountEnemyKill{ 0 };
};






#endif // #ifndef INCLUDE_ENEMY_H