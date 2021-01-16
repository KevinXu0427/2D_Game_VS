#include "Player.h"

void Player::Load(std::string textures[])
{
	mTextureIds = std::make_unique<X::TextureId[]>(textures->size());
	mTextureIds[0] = X::LoadTexture(textures[0].c_str());
	mTextureIds[1] = X::LoadTexture(textures[1].c_str());
	mTextureIds[2] = X::LoadTexture(textures[2].c_str());
	mTextureIds[3] = X::LoadTexture(textures[3].c_str());

}

void Player::Unload()
{
	mTextureIds.reset();
}

void Player::Update(const TileMap& map, float deltaTime)
{
	const float gravity = 800.0f;

	// Check input for any displacement
	float displacementX = 0.0f;

	if (X::IsKeyDown(X::Keys::RIGHT))
	{
		
		displacementX = mSpeed * deltaTime;
		mMove = true;
	}
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		displacementX = -mSpeed * deltaTime;
		mMove = true;
	}

	// Check collision and adjust displacement if needed
	auto boudary = GetBoundary();
	if (displacementX > 0.0f)
	{
		X::Math::LineSegment rightEdge;
		rightEdge.from = { boudary.right + displacementX, boudary.top };
		rightEdge.to = { boudary.right + displacementX, boudary.bottom };
		if (map.CheckCollision(rightEdge))
		{
			displacementX = 0.0f;
		}
	}
	if (displacementX < 0.0f)
	{
		X::Math::LineSegment leftEdge;
		leftEdge.from = { boudary.left + displacementX, boudary.top };
		leftEdge.to = { boudary.left + displacementX, boudary.bottom };
		if (map.CheckCollision(leftEdge))
		{
			displacementX = 0.0f;
		}
	}
	// Update position
	mPosition.x += displacementX;

	float displacementY = 0.0f;
	/*if (X::IsKeyDown(X::Keys::UP))
	{
		displacementY = -mSpeed * deltaTime;
		mMove = true;
	}*/

	if (X::IsKeyDown(X::Keys::SPACE) && !mJumping)
	{
		mJumping = true;
		mVelocity.y = -550.0f;
		mMove = true;
	}
	mVelocity.y += gravity * deltaTime;
	displacementY = mVelocity.y * deltaTime;

	if (X::IsKeyDown(X::Keys::DOWN))
	{
		displacementY = mSpeed * deltaTime;
		mMove = true;
	}

	// Check collision and adjust displacement if needed
	//auto boudary = GetBoundary();
	if (displacementY < 0.0f)
	{
		X::Math::LineSegment topEdge;
		topEdge.from = { boudary.left, boudary.top + displacementY };
		topEdge.to = { boudary.right, boudary.top + displacementY };
		if (map.CheckCollision(topEdge))
		{
			displacementY = 0.0f;
			mVelocity.y = 0.0f;
			mJumping = false;
		}
	}
	if (displacementY > 0.0f)
	{
		X::Math::LineSegment botEdge;
		botEdge.from = { boudary.left, boudary.bottom + displacementY };
		botEdge.to = { boudary.right, boudary.bottom + displacementY };
		if (map.CheckCollision(botEdge))
		{
			displacementY = 0.0f;
			mVelocity.y = 0.0f;
			mJumping = false;
		}
	}

	// Update position
	mPosition.y += displacementY;


	if (mJumping)
	{
		mFrameIndex = 2;
	}
	else if (mMove)
	{
		if (mFrameIndex == 0)
		{
			mFrameIndex = 1;
		}
		else
		{
			mFrameIndex = 0;
		}

		mMove = false;
	}
	else
	{
		mFrameIndex = 3;
	}
}

void Player::Render(const Camera& camera, bool debug)
{
	auto drawPosition = mPosition + X::Math::Vector2
	{
		0.0f,
		X::GetSpriteHeight(mTextureIds[mFrameIndex]) * -0.5f
	};
	
	camera.Draw(mTextureIds[mFrameIndex], drawPosition);

	if (debug)
	{
		auto boudary = GetBoundary();
		auto topLeft = camera.ConvertToScreenPosition({ boudary.left, boudary.top });
		auto rightBottom = camera.ConvertToScreenPosition({ boudary.right, boudary.bottom });
		X::DrawScreenRect(topLeft.x, topLeft.y, rightBottom.x, rightBottom.y, X::Math::Vector4::Cyan());
	}
	
}

X::Math::Rect Player::GetBoundary() const
{
	float width = X::GetSpriteWidth(mTextureIds[mFrameIndex]);
	float height = X::GetSpriteHeight(mTextureIds[mFrameIndex]);

	return {
	mPosition.x - (width * 0.25f),
	mPosition.y - (height * 0.85f),
	mPosition.x + (width * 0.25f),
	mPosition.y
	};
}
