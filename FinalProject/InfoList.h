#ifndef INCLUDED_INFOLIST_H
#define INCLUDED_INFOLIST_H

#include <XEngine.h>
#include "SpriteAnimation.h"

class Infolist
{
public:
	void CreateList();
	void CreateSecondList();
	std::vector<SpriteAnimation::Info> Getlist() { return mList; }
	std::vector<SpriteAnimation::Info> GetSecondlist() { return mSecondList; }


private:
	std::vector<SpriteAnimation::Info> mList;
	std::vector<SpriteAnimation::Info> mSecondList;

};

#endif // !INCLUDED_INFOLIST_H