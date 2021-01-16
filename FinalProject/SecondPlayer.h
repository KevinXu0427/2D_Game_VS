#ifndef INCLUDE_SECONDPLAYER_H
#define INCLUDE_SECONDPLAYER_H

#include <XEngine.h>
#include "AnimationManager.h"

enum StateMachineB
{
	IdleB,
	WalkB,
	WalkBackB,
	PunchLeftB,
	PunchRightB,
	PunchUpB,
	BlockingB,
	DizzyB,
	HurtB,
	KOB
};

class SecondPlayer
{
public:
	void Load(std::string textures[]);
	void Unload();
	void Update(float deltaTime);
	void Render(bool debug);

	void UpdateIdle(float deltaTime);
	void UpdateMovement(float deltaTime);
	void UpdateBlocking(float deltaTime);
	void UpdatePunch(float deltaTime);
	void UpdateDizzy(float deltaTime);
	void UpdateHurt(float deltaTime);
	void UpdateKO(float deltaTime);

	int GetHealth() { return mHealth; }
	void ResetHealth() { mHealth = 50; }
	void SetPlayerName(std::string name) { mPlayerName = name; }
	std::string GetPlayerName() const { return mPlayerName; }
	void SetEnemyPosition(const X::Math::Vector2& position) { mEnemyPosition = position; }
	void GetHurt();

	bool IsBlocking() { return mBlocking; }
	bool IsPunching() { return stateMachine == StateMachineB::PunchLeftB || stateMachine == StateMachineB::PunchRightB || stateMachine == StateMachineB::PunchUpB; }

	std::vector<int> GetDamageData() { return mDamageData; }

	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	X::Math::Vector2 GetPosition() const { return mPosition; }
	X::Math::Rect GetBoundary() const;
	void SetAnimationMap(AnimationManager animations) { mAnimations = animations; }
	void ChangeState(StateMachineB nextState);

private:
	X::Math::Vector2 mPosition{ 0.0f,0.0f };
	X::Math::Vector2 mEnemyPosition{ 0.0f,0.0f };

	std::unique_ptr<X::TextureId[]> mTextureIds;

	AnimationManager mAnimations;
	StateMachineB stateMachine = StateMachineB::IdleB;

	std::vector<int> mDamageData;

	std::string mPlayerName{ "" };
	int mHealth{ 50 };
	int mDamage{ 0 };
	float mSpeed{ 300 };

	bool mGetHurt{ false };
	bool mBlocking{ false };

	bool mDizzying{ false };
	bool mMove = false;
};
#endif // !INCLUDE_SECONDPLAYER_H