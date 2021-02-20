#include "SecondPlayer.h"

namespace
{
	AnimationName GetAnimationName(StateMachineB stateMachine)
	{
		switch (stateMachine)
		{
		case StateMachineB::IdleB:			return AnimationName::Idle;
		case StateMachineB::WalkB:			return AnimationName::Walk;
		case StateMachineB::WalkBackB:		return AnimationName::WalkBack;
		case StateMachineB::PunchLeftB:		return AnimationName::PunchLeft;
		case StateMachineB::PunchRightB:		return AnimationName::PunchRight;
		case StateMachineB::PunchUpB:			return AnimationName::PunchUp;
		case StateMachineB::BlockingB:		return AnimationName::Blocking;
		case StateMachineB::DizzyB:			return AnimationName::Dizzy;
		case StateMachineB::HurtB:			return AnimationName::Hurt;
		case StateMachineB::KOB:				return AnimationName::KO;
		default:
			break;
		}
	}
}

void SecondPlayer::Load(std::string textures[])
{
	/*mTextureIds = std::make_unique<X::TextureId[]>(textures->size());
	mTextureIds[0] = X::LoadTexture(textures[0].c_str());
*/
	mTextureIds = std::make_unique<X::TextureId[]>(textures->size());
	mTextureIds[0] = X::LoadTexture(textures[0].c_str());
	mTextureIds[1] = X::LoadTexture(textures[1].c_str());
}

void SecondPlayer::Unload()
{
	mTextureIds.reset();
}

void SecondPlayer::Update(float deltaTime)
{
	// Make sure animation is updated first, so we know if we need to change state this frame
	mAnimations.Update(deltaTime, GetAnimationName(stateMachine));
	
	switch (stateMachine)
	{
	case StateMachineB::IdleB:
		UpdateIdle(deltaTime);
		break;
	case StateMachineB::WalkB:
		UpdateMovement(deltaTime);
		break;
	case StateMachineB::WalkBackB:
		UpdateMovement(deltaTime);
		break;
	case StateMachineB::PunchLeftB:
		UpdatePunch(deltaTime);
		break;
	case StateMachineB::PunchRightB:
		UpdatePunch(deltaTime);
		break;
	case StateMachineB::PunchUpB:
		UpdatePunch(deltaTime);
		break;
	case StateMachineB::BlockingB:
		UpdateBlocking(deltaTime);
		break;
	case StateMachineB::DizzyB:
		UpdateDizzy(deltaTime);
		break;
	case StateMachineB::HurtB:
		UpdateHurt(deltaTime);
		break;
	case StateMachineB::KOB:
		UpdateKO(deltaTime);
		break;
	default:
		break;
	}
}

void SecondPlayer::Render(bool debug)
{
	/*switch (stateMachine)
	{
	case StateMachineB::IdleB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::WalkB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::WalkBackB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::PunchLeftB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::PunchRightB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::PunchUpB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::BlockingB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::DizzyB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::HurtB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	case StateMachineB::KOB:
		mAnimations.Render(GetAnimationName(stateMachine));
		break;
	default:
		break;
	}*/

	mAnimations.Render(GetAnimationName(stateMachine));

	if (debug)
	{
		auto boudary = GetBoundary();
		X::Math::Vector2 topLeft = { boudary.left, boudary.top };
		X::Math::Vector2 rightBottom = { boudary.right, boudary.bottom };
		X::DrawScreenRect(topLeft.x, topLeft.y, rightBottom.x, rightBottom.y, X::Math::Vector4::Cyan());
	}
}

void SecondPlayer::UpdateIdle(float deltaTime)
{
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		ChangeState(StateMachineB::WalkBackB);
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		ChangeState(StateMachineB::WalkB);
	}
	else if (X::IsKeyDown(X::Keys::DOWN))
	{
		ChangeState(StateMachineB::BlockingB);
	}
	else if (X::IsKeyPressed(X::Keys::I))
	{
		ChangeState(StateMachineB::PunchLeftB);
	}
	else if (X::IsKeyPressed(X::Keys::O))
	{
		ChangeState(StateMachineB::PunchRightB);
	}
	else if (X::IsKeyPressed(X::Keys::P))
	{
		ChangeState(StateMachineB::PunchUpB);
	}
	else if (mDamage == 10 || mDamage == 6)
	{
		ChangeState(StateMachineB::DizzyB);
	}
	else if (mGetHurt)
	{
		ChangeState(StateMachineB::HurtB);
	}
	else if (mHealth == 0)
	{
		ChangeState(StateMachineB::KOB);
	}

	mBlocking = false;
	mGetHurt = false;
	mDizzying = false;
}

void SecondPlayer::UpdateMovement(float deltaTime)
{
	auto boudary = GetBoundary();

	if (X::IsKeyDown(X::Keys::LEFT) && boudary.left >= 0 && mDizzying == false)
	{
		mPosition.x -= mSpeed * deltaTime;
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	else if (X::IsKeyDown(X::Keys::RIGHT) && boudary.right <= 1280 && mDizzying == false)
	{
		mPosition.x += mSpeed * deltaTime;
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	else
	{
		ChangeState(StateMachineB::IdleB);
	}
}

void SecondPlayer::UpdateBlocking(float deltaTime)
{
	if (X::IsKeyDown(X::Keys::DOWN))
	{
		mBlocking = true;
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	else
	{
		ChangeState(StateMachineB::IdleB);
	}
	
}

void SecondPlayer::UpdatePunch(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::I) && mDizzying == false)
	{
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	if (X::IsKeyPressed(X::Keys::O) && mDizzying == false)
	{
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}
	if (X::IsKeyPressed(X::Keys::P) && mDizzying == false)
	{
		mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	}

	if (!mAnimations.IsPlaying())
	{
		ChangeState(StateMachineB::IdleB);
	}
}

void SecondPlayer::UpdateDizzy(float deltaTime)
{
	mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	if (!mAnimations.IsPlaying())
	{
		ChangeState(StateMachineB::IdleB);
	}
}

void SecondPlayer::UpdateHurt(float deltaTime)
{
	mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	
	if (!mAnimations.IsPlaying())
	{
		ChangeState(StateMachineB::IdleB);
	}
}

void SecondPlayer::UpdateKO(float deltaTime)
{
	mAnimations.Play(GetAnimationName(stateMachine), mPosition);
	if (!mAnimations.IsPlaying())
	{
		ChangeState(StateMachineB::IdleB);
	}
}


void SecondPlayer::GetHurt()
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
	ChangeState(StateMachineB::HurtB);

}

X::Math::Rect SecondPlayer::GetBoundary() const
{
	float width = (float)X::GetSpriteWidth(mTextureIds[0]);
	float height = (float)X::GetSpriteHeight(mTextureIds[0]);

	return {
	mPosition.x - (width * 0.4f),
	mPosition.y - (height * 0.25f),
	mPosition.x + (width * 0.15f),
	mPosition.y + (height * 0.35f)
	};
}

void SecondPlayer::ChangeState(StateMachineB nextState)
{
	stateMachine = nextState;
	mAnimations.Play(GetAnimationName(nextState), mPosition);
}