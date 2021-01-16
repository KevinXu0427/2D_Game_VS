#ifndef INCLUDE_BACKGROUNDMANAGER_H
#define INCLUDE_BACKGROUNDMANAGER_H

#include "XEngine.h"

class BgSetup
{
public:
	void Load(std::string textureName, std::string textureName2);
	void Unload();
	void Update(float deltaTime);
	void Render();

	bool IsActive1() const { return mActive; }
	void SetScreenInfo(float width, float height);

private:
	X::Math::Vector2 mPosition{ 0.0f,0.0f };
	X::Math::Vector2 mPosition2{ 0.0f,0.0f };
	X::TextureId mTextureId{ 0 };
	X::TextureId mTextureId2{ 0 };
	bool mActive{ false };
	bool mActive2{ false };
	float mSpeed{ 400 };
	float mBgImageWidth;
	float mBgImageHeight;
	float mScreenHeight;
	float mScreenWidth;
};

#endif // !INCLUDE_BACKGROUNDMANAGER_H
