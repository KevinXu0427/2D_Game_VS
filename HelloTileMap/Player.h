#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "Camera.h"
#include "TileMap.h"
#include <XEngine.h>

class Player
{
public:

	void Load(std::string textures[]);
	void Unload();
	void Update(const TileMap& map,float deltaTime);
	void Render(const Camera& camera, bool debug);

	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	X::Math::Vector2 GetPosition() const { return mPosition; }
	X::Math::Rect GetBoundary() const;

private:
	X::Math::Vector2 mPosition{ 0.0f,0.0f };
	X::Math::Vector2 mVelocity{ 0.0f,0.0f };
	std::unique_ptr<X::TextureId[]> mTextureIds;
	int mFrameIndex{ 0 };
	float mSpeed{ 200 };
	bool mMove = false;
	float mFrameTime{ 0 };
	bool mJumping = false;
};



#endif // !INCLUDE_PLAYER_H