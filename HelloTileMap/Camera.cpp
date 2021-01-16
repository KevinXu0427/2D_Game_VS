#include "Camera.h"

X::Math::Vector2 Camera::ConvertToScreenPosition(const X::Math::Vector2& worldPosition) const
{
	X::Math::Vector2 screenPos;
	screenPos.x = worldPosition.x - mViewPosition.x + X::GetScreenWidth() / 2.0f;
	screenPos.y = worldPosition.y - mViewPosition.y + X::GetScreenHeight() / 2.0f;

	return screenPos;
}

X::Math::Vector2 Camera::ConvertToWorldPosition(const X::Math::Vector2& screenPosition) const
{
	X::Math::Vector2 worldPos;
	worldPos.x = mViewPosition.x - X::GetScreenWidth() / 2.0f + screenPosition.x;
	worldPos.y = mViewPosition.y - X::GetScreenHeight() / 2.0f + screenPosition.y;

	return worldPos;
}

void Camera::Draw(X::TextureId textureId, const X::Math::Vector2& worldPosition) const
{
	// To do
	// Add check here:
	// if screen position is outside of the screen
	// just return and do not call drawsprite
	// if(outside)
	//    return

	// all the render function
	// void render(const camera& camera)

	auto screenPosition = ConvertToScreenPosition(worldPosition);
	if (screenPosition.x >= (X::GetScreenWidth() * 2) || screenPosition.y >= (X::GetScreenHeight() * 2) || screenPosition.x <= 0  || screenPosition.y <= 0)
	{
		return;
	}

	X::DrawSprite(textureId, screenPosition);
}