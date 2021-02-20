#ifndef INCLUDED_ANIMATIONMANAGER_H
#define INCLUDED_ANIMATIONMANAGER_H

#include <XEngine.h>
#include "SpriteAnimation.h"
#include "InfoList.h"

enum AnimationName
{
	Dizzy,
	Idle,
	Walk,
	WalkBack,
	Blocking,
	PunchLeft,
	PunchRight,
	PunchUp,
	Hurt,
	KO,
};

class AnimationManager
{
public:
	void CreateAnimationlist(int index);
	void Play(AnimationName Name, X::Math::Vector2 position);
	void Update(float deltaTime, AnimationName Name);
	void Stop(AnimationName Name);
	void Render(AnimationName Name);
	std::unordered_map<AnimationName, SpriteAnimation> GetAnimationMap() { return mAnimations; }
	bool IsPlaying() const { return mPlaying; }

private:
	Infolist mInfoList;
	std::unordered_map<AnimationName,SpriteAnimation> mAnimations;
	bool mPlaying = false;
};

#endif // !INCLUDED_ANIMATIONMANAGER_H