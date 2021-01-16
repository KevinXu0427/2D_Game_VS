#include "InfoList.h"

void Infolist::CreateList()
{
	SpriteAnimation::Info Dizzy;
	Dizzy.fileName = "Dizzy.png";
	Dizzy.rows = 3;
	Dizzy.columns = 3;
	Dizzy.frameCount = 8;
	Dizzy.framePerSecond = 6.0f;
	Dizzy.looping = true;
	mList.push_back(Dizzy);

	SpriteAnimation::Info Idle;
	Idle.fileName = "Idle.png";
	Idle.rows = 4;
	Idle.columns = 3;
	Idle.frameCount = 10;
	Idle.framePerSecond = 12.0f;
	Idle.looping = true;
	mList.push_back(Idle);

	SpriteAnimation::Info Walk;
	Walk.fileName = "Walk.png";
	Walk.rows = 4;
	Walk.columns = 3;
	Walk.frameCount = 10;
	Walk.framePerSecond = 12.0f;
	Walk.looping = true;
	mList.push_back(Walk);

	SpriteAnimation::Info WalkBack;
	WalkBack.fileName = "WalkBack.png";
	WalkBack.rows = 4;
	WalkBack.columns = 3;
	WalkBack.frameCount = 10;
	WalkBack.framePerSecond = 12.0f;
	WalkBack.looping = true;
	mList.push_back(WalkBack);

	SpriteAnimation::Info Blocking;
	Blocking.fileName = "Blocking.png";
	Blocking.rows = 4;
	Blocking.columns = 3;
	Blocking.frameCount = 10;
	Blocking.framePerSecond = 12.0f;
	Blocking.looping = true;
	mList.push_back(Blocking);

	SpriteAnimation::Info PunchLeft;
	PunchLeft.fileName = "PunchLeft.png";
	PunchLeft.rows = 2;
	PunchLeft.columns = 3;
	PunchLeft.frameCount = 6;
	PunchLeft.framePerSecond = 12.0f;
	PunchLeft.looping = false;
	mList.push_back(PunchLeft);

	SpriteAnimation::Info PunchRight;
	PunchRight.fileName = "PunchRight.png";
	PunchRight.rows = 2;
	PunchRight.columns = 3;
	PunchRight.frameCount = 6;
	PunchRight.framePerSecond = 12.0f;
	PunchRight.looping = false;
	mList.push_back(PunchRight);

	SpriteAnimation::Info PunchUp;
	PunchUp.fileName = "PunchUp.png";
	PunchUp.rows = 3;
	PunchUp.columns = 3;
	PunchUp.frameCount = 7;
	PunchUp.framePerSecond = 12.0f;
	PunchUp.looping = false;
	mList.push_back(PunchUp);

	SpriteAnimation::Info Hurt;
	Hurt.fileName = "Hurt.png";
	Hurt.rows = 3;
	Hurt.columns = 3;
	Hurt.frameCount = 8;
	Hurt.framePerSecond = 12.0f;
	Hurt.looping = false;
	mList.push_back(Hurt);

	SpriteAnimation::Info KO;
	KO.fileName = "KO.png";
	KO.rows = 4;
	KO.columns = 3;
	KO.frameCount = 10;
	KO.framePerSecond = 12.0f;
	KO.looping = false;
	mList.push_back(KO);
}

void Infolist::CreateSecondList()
{
	SpriteAnimation::Info Dizzy;
	Dizzy.fileName = "Dizzy2.png";
	Dizzy.rows = 3;
	Dizzy.columns = 3;
	Dizzy.frameCount = 8;
	Dizzy.framePerSecond = 6.0f;
	Dizzy.looping = true;
	mSecondList.push_back(Dizzy);

	SpriteAnimation::Info Idle;
	Idle.fileName = "Idle2.png";
	Idle.rows = 4;
	Idle.columns = 3;
	Idle.frameCount = 10;
	Idle.framePerSecond = 12.0f;
	Idle.looping = true;
	mSecondList.push_back(Idle);

	SpriteAnimation::Info Walk;
	Walk.fileName = "Walk2.png";
	Walk.rows = 4;
	Walk.columns = 3;
	Walk.frameCount = 10;
	Walk.framePerSecond = 12.0f;
	Walk.looping = true;
	mSecondList.push_back(Walk);

	SpriteAnimation::Info WalkBack;
	WalkBack.fileName = "WalkBack2.png";
	WalkBack.rows = 4;
	WalkBack.columns = 3;
	WalkBack.frameCount = 10;
	WalkBack.framePerSecond = 12.0f;
	WalkBack.looping = true;
	mSecondList.push_back(WalkBack);

	SpriteAnimation::Info Blocking;
	Blocking.fileName = "Blocking2.png";
	Blocking.rows = 4;
	Blocking.columns = 3;
	Blocking.frameCount = 10;
	Blocking.framePerSecond = 12.0f;
	Blocking.looping = true;
	mSecondList.push_back(Blocking);

	SpriteAnimation::Info PunchLeft;
	PunchLeft.fileName = "PunchLeft2.png";
	PunchLeft.rows = 2;
	PunchLeft.columns = 3;
	PunchLeft.frameCount = 6;
	PunchLeft.framePerSecond = 12.0f;
	PunchLeft.looping = false;
	mSecondList.push_back(PunchLeft);

	SpriteAnimation::Info PunchRight;
	PunchRight.fileName = "PunchRight2.png";
	PunchRight.rows = 2;
	PunchRight.columns = 3;
	PunchRight.frameCount = 6;
	PunchRight.framePerSecond = 12.0f;
	PunchRight.looping = false;
	mSecondList.push_back(PunchRight);

	SpriteAnimation::Info PunchUp;
	PunchUp.fileName = "PunchUp2.png";
	PunchUp.rows = 3;
	PunchUp.columns = 3;
	PunchUp.frameCount = 7;
	PunchUp.framePerSecond = 12.0f;
	PunchUp.looping = false;
	mSecondList.push_back(PunchUp);

	SpriteAnimation::Info Hurt;
	Hurt.fileName = "Hurt2.png";
	Hurt.rows = 3;
	Hurt.columns = 3;
	Hurt.frameCount = 8;
	Hurt.framePerSecond = 12.0f;
	Hurt.looping = false;
	mSecondList.push_back(Hurt);

	SpriteAnimation::Info KO;
	KO.fileName = "KO2.png";
	KO.rows = 4;
	KO.columns = 3;
	KO.frameCount = 10;
	KO.framePerSecond = 12.0f;
	KO.looping = false;
	mSecondList.push_back(KO);
}
