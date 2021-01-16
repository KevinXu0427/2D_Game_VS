#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <XEngine.h>
#include "AnimationManager.h"

enum class StateMachine
{
	Idle,
	Walk,
	WalkBack,
	PunchLeft,
	PunchRight,
	PunchUp,
	Blocking,
	Dizzy,
	Hurt,
	KO
};

class Player
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
	bool IsPunching() { return stateMachine == StateMachine::PunchLeft || stateMachine == StateMachine::PunchRight || stateMachine == StateMachine::PunchUp; }

	//X::Math::Rect GetDamageBox() const
	//{
	//	X::Math::Rect rect; // empty
	//	if (stateMachine == StateMachine::PunchLeft && frameIndex >= 7 && frameIndex <= 11)
	//		rect = { };
	//	if (stateMachine == StateMachine::PunchLeft && frameIndex >= 7 && frameIndex <= 11)
	//		rect = { };
	//	if (stateMachine == StateMachine::PunchLeft && frameIndex >= 7 && frameIndex <= 11)
	//		rect = { };
	//	if (stateMachine == StateMachine::PunchLeft && frameIndex >= 7 && frameIndex <= 11)
	//		rect = { };
	//	return rect;
	//}

	std::vector<int> GetDamageData() { return mDamageData; }

	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	X::Math::Vector2 GetPosition() const { return mPosition; }
	X::Math::Rect GetBoundary() const;
	void SetAnimationMap(AnimationManager animations) { mAnimations = animations; }

	void ChangeState(StateMachine nextState);

private:
	X::Math::Vector2 mPosition{ 0.0f,0.0f };
	X::Math::Vector2 mEnemyPosition{ 0.0f,0.0f };

	std::unique_ptr<X::TextureId[]> mTextureIds;

	AnimationManager mAnimations;
	StateMachine stateMachine = StateMachine::Idle;

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
#endif // !INCLUDE_PLAYER_H