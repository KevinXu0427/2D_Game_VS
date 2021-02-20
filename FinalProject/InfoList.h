#ifndef INCLUDED_INFOLIST_H
#define INCLUDED_INFOLIST_H

#include <XEngine.h>
#include "SpriteAnimation.h"

class Infolist
{
public:
	void CreateList();
	void CreateSecondList();

	const std::vector<SpriteAnimation::Info>& Getlist() const { return mList; }
	const std::vector<SpriteAnimation::Info>& GetSecondlist() const { return mSecondList; }

private:
	// TODO - Change to using a map that you can look up by character name
	//std::map<std::string, std::vector<SpriteAnimation::Info>> mInfoMap;
	std::vector<SpriteAnimation::Info> mList;
	std::vector<SpriteAnimation::Info> mSecondList;
};

#endif // !INCLUDED_INFOLIST_H