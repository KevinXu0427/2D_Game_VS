#ifndef INCLUDED_CAMERA_H
#define INCLUDED_CAMERA_H

#include <XEngine.h>

class Camera
{
public:
	X::Math::Vector2 ConvertToScreenPosition(const X::Math::Vector2& worldPosition) const;
	X::Math::Vector2 ConvertToWorldPosition(const X::Math::Vector2& screenPosition) const;

	void Draw(X::TextureId textureId, const X::Math::Vector2& worldPosition) const;

	void SetViewPosition(const X::Math::Vector2& viewPosition) { mViewPosition = viewPosition; }

private:
	X::Math::Vector2 mViewPosition;
	X::Math::Vector2 mScreenPosition = { 0.0f,0.0f };
	X::Math::Vector2 mWorldPosition = { 0.0f,0.0f };
	
};

#endif // !INCLUDED_CAMERA_H