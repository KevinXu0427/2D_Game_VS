#include "AnimationManager.h"

void AnimationManager::CreateAnimationlist(int index)
{
	if (index == 1)
	{
		mInfoList.CreateList();
		auto& infolist = mInfoList.Getlist();
		for (int i = 0; i < infolist.size(); i++)
		{
			SpriteAnimation& animation = mAnimations[static_cast<AnimationName>(i)];
			animation.Load(infolist[i]);
		}
	}
	else if (index == 2)
	{
		mInfoList.CreateSecondList();
		auto& infolist = mInfoList.GetSecondlist();
		for (int i = 0; i < infolist.size(); i++)
		{
			SpriteAnimation& animation = mAnimations[static_cast<AnimationName>(i)];
			animation.Load(infolist[i]);
		}
	}
}

void AnimationManager::Play(AnimationName Name, X::Math::Vector2 position)
{
	auto search = mAnimations.find(Name);
	if (search != mAnimations.end())
	{
		search->second.SetPosition(position);
		mPlaying = search->second.IsPlaying();
		if (!mPlaying)
		{
			search->second.Play();
		}
	}

}

void AnimationManager::Update(float deltaTime, AnimationName Name)
{
	auto search = mAnimations.find(Name);
	if (search != mAnimations.end())
	{
		search->second.Update(deltaTime);
		mPlaying = search->second.IsPlaying();
	}
}

void AnimationManager::Stop(AnimationName Name)
{
	auto search = mAnimations.find(Name);
	if (search != mAnimations.end())
	{
		search->second.Stop();
	}
}

void AnimationManager::Render(AnimationName Name)
{
	auto search = mAnimations.find(Name);
	if (search != mAnimations.end())
	{
		search->second.Render();
	}
}
