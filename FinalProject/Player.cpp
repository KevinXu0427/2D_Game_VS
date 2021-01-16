#include "Player.h"

namespace
{
	AnimationName GetAnimationName(StateMachine stateMachine)
	{
		switch(stateMachine)
		{
			case StateMachine::Idle:			return AnimationName::Idle;
			case StateMachine::Walk:			return AnimationName::Walk;
			case StateMachine::WalkBack:		return AnimationName::WalkBack;
			case StateMachine::PunchLeft:		return AnimationName::PunchLeft;
			case StateMachine::PunchRight:		return AnimationName::PunchRight;
			case StateMachine::PunchUp:			return AnimationName::PunchUp;
			case StateMachine::Blocking:		return AnimationName::Blocking;
			case StateMachine::Dizzy:			return AnimationName::Dizzy;
			case StateMachine::Hurt:			return AnimationName::Hurt;
			case StateMachine::KO:				return AnimationName::KO;
			default:
				break;
		}
	}
}

void Player::Load(std::string textures[])
{
	mTextureIds = std::make_unique<X::TextureId[]>(textures->size());
	mTextureIds[0] = X::LoadTexture(textures[0].c_str());
	mTextureIds[1] = X::LoadTexture(textures[1].c_str());
}

void Player::Unload()
{
	mTextureIds.reset();
}

void Player::Update(float deltaTime)
{
	switch (stateMachine)
	{
	case StateMachine::Idle:
		UpdateIdle(deltaTime);
		break;
	case StateMachine::Walk:
		UpdateMovement(deltaTime);
		break;
	case StateMachine::WalkBack:
		UpdateMovement(deltaTime);
		break;
	case StateMachine::PunchLeft:
		UpdatePunch(deltaTime);
		break;
	case StateMachine::PunchRight:
		UpdatePunch(deltaTime);
		break;
	case StateMachine::PunchUp:
		UpdatePunch(deltaTime);
		break;
	case StateMachine::Blocking:
		UpdateBlocking(deltaTime);
		break;
	case StateMachine::Dizzy:
		UpdateDizzy(deltaTime);
		break; 
	case StateMachine::Hurt:
		UpdateHurt(deltaTime);
		break;
	case StateMachine::KO:
		UpdateKO(deltaTime);
		break;
	default:
		break;
	}
	

	mAnimations.Update(deltaTime, GetAnimationName(stateMachine));
}

void Player::Render(bool debug)
{
	mAnimations.Render(GetAnimationName(stateMachine));

	if (debug)
	{
		auto boudary = GetBoundary();
		X::Math::Vector2 topLeft = { boudary.left, boudary.top };
		X::Math::Vector2 rightBottom = { boudary.right, boudary.bottom };
		X::DrawScreenRect(topLeft.x, topLeft.y, rightBottom.x, rightBottom.y, X::Math::Vector4::Cyan());
	}
}

void Player::UpdateIdle(float deltaTime)
{
	if (X::IsKeyDown(X::Keys::A))
	{
		ChangeState(StateMachine::WalkBack);
	}
	else if (X::IsKeyDown(X::Keys::D))
	{
		ChangeState(StateMachine::Walk);
	}
	else if (X::IsKeyDown(X::Keys::S))
	{
		ChangeState(StateMachine::Blocking);
	}
	else if (X::IsKeyPressed(X::Keys::C))
	{
		ChangeState(StateMachine::PunchLeft);
	}
	else if (X::IsKeyPressed(X::Keys::V))
	{
		ChangeState(StateMachine::PunchRight);
	}
	else if (X::IsKeyPressed(X::Keys::B))
	{
		ChangeState(StateMachine::PunchUp);
	}
	else if (mDamage == 10 || mDamage == 6)
	{
		ChangeState(StateMachine::Dizzy);
	}
	else if (mGetHurt)
	{
		ChangeState(StateMachine::Hurt);
	}
	else if (mHealth == 0)
	{
		ChangeState(StateMachine::KO);
	}

	mBlocking = false;
	mGetHurt = false;
	mDizzying = false;
}

void Player::UpdateMovement(float deltaTime)
{
	auto boudary = GetBoundary();

	if (X::IsKeyDown(X::Keys::A) && boudary.left >= 0 && mDizzying == false)
	{
		mPosition.x -= mSpeed * deltaTime;
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	else if (X::IsKeyDown(X::Keys::D) && boudary.right <= 1280 && mDizzying == false)
	{
		mPosition.x += mSpeed * deltaTime;
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	else
	{
		ChangeState(StateMachine::Idle);
	}
}

void Player::UpdateBlocking(float deltaTime)
{
	if (X::IsKeyDown(X::Keys::S))
	{
		mBlocking = true;
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	else
	{
		ChangeState(StateMachine::Idle);
	}
}

void Player::UpdatePunch(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::C) && mDizzying == false)
	{
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	if (X::IsKeyPressed(X::Keys::V) && mDizzying == false)
	{
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	if (X::IsKeyPressed(X::Keys::B) && mDizzying == false)
	{
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	
	if (!mAnimations.IsPlaying())
	{
		ChangeState(StateMachine::Idle);
	}
}

void Player::UpdateDizzy(float deltaTime)
{
	mAnimations.Play(GetAnimationName(stateMachine), mPosition);

	if (!mAnimations.IsPlaying())
	{
		ChangeState(StateMachine::Idle);
	}
}


void Player::UpdateHurt(float deltaTime)
{
	mAnimations.Play(GetAnimationName(stateMachine), mPosition);

	if (!mAnimations.IsPlaying())
	{
		ChangeState(StateMachine::Idle);
	}
}


void Player::UpdateKO(float deltaTime)
{
	if (mHealth == 0)
	{
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}

	if (!mAnimations.IsPlaying())
	{
		ChangeState(StateMachine::Idle);
	}
}

void Player::GetHurt()
{
	if (GetAnimationName(stateMachine) == AnimationName::Hurt)
	{
		return;
	}

	mGetHurt = true;
	srand(time(NULL));
	mDamage = rand() % 10 + 1;
	mHealth -= mDamage;
	mDamageData.push_back(mDamage);
	if (mHealth < 0)
	{
		mHealth = 0;
	}
	ChangeState(StateMachine::Hurt);
}


X::Math::Rect Player::GetBoundary() const
{
	float width = X::GetSpriteWidth(mTextureIds[0]);
	float height = X::GetSpriteHeight(mTextureIds[0]);

	return {
	mPosition.x - (width * 0.1f),
	mPosition.y - (height * 0.25f),
	mPosition.x + (width * 0.45f),
	mPosition.y + (height * 0.35f)
	};
}

void Player::ChangeState(StateMachine nextState)
{
	stateMachine = nextState;
	mAnimations.Play(GetAnimationName(nextState), mPosition);
}
