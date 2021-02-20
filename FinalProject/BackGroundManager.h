#ifndef INCLUDE_BACKGROUNDMANAGER_H
#define INCLUDE_BACKGROUNDMANAGER_H

#include "XEngine.h"

class BgSetup
{
public:
	void Load(std::string textures[]);
	void Unload();
	void Update(float deltaTime);
	void Render();

	void SetScreenInfo(float width, float height);
	bool IsStartGame() { return mStart; }
	void SetScreenStart(bool value) { mLoadFinished = value; }
	void SetEndgame(bool value) { mIsEnd = value; }
	bool IsLoadFinished() { return mLoadFinished; }
	bool IsEndGame() { return mIsEnd; }
private:
	std::unique_ptr<X::TextureId[]> mTextureIds;
	X::Math::Vector2 mPositionBg{ 0,0 };
	X::Math::Vector2 mPositionBgRing{ 0,0 };
	float mNextFlashTime{ 0 };
	bool mStart{ false };
	bool mLoadFinished{ false };
	bool mIsEnd{ false };
};

#endif // !INCLUDE_BACKGROUNDMANAGER_H
