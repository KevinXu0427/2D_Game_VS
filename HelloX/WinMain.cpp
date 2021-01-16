#include<XEngine.h>

X::Math::Vector2 position1;
X::Math::Vector2 position2;

X::TextureId textureId = 0;
X::TextureId textureId2 = 0;

float Vside1 = 1.0f;
float Hside1 = 1.0f;

float Vside2 = 1.0f;
float Hside2 = 1.0f;


X::Math::Circle GetBoundingCircle(X::Math::Vector2 vec, X::TextureId ttId)
{
	float radius = X::GetSpriteWidth(ttId) * 0.5f;
	return X::Math::Circle(vec, radius);
}

void CheckCollison(X::Math::Vector2 vec, X::TextureId ttId, X::Math::Vector2 vec2, X::TextureId ttId2)
{
	if (X::Math::Intersect(GetBoundingCircle(vec, ttId), GetBoundingCircle(vec2, ttId2)))
	{
		Vside1 = -Vside1;
		Hside1 = -Hside1;
				 
		Vside2 = -Vside2;
		Hside2 = -Hside2;
	}

}

bool CheckEdgeBoundaries(X::Math::Vector2 vec, X::TextureId ttId)
{
	bool collisionHappened = false;

	// colliding with left
	if (vec.x < (X::GetSpriteWidth(ttId) * 0.5f))
	{
		Hside1 = 1.0f;
		vec.x = vec.x;
		collisionHappened = true;
	}

	// colliding with right
	if (vec.x > (X::GetScreenWidth() - X::GetSpriteWidth(ttId) * 0.5f))
	{
		Hside1 = -1.0f;
		collisionHappened = true;
	}
	
	// colliding with top
	if (vec.y < (X::GetSpriteHeight(ttId) * 0.5f))
	{
		Vside1 = 1.0f;
		collisionHappened = true;
	}

	// colliding with bot
	if (vec.y > (X::GetScreenHeight() - X::GetSpriteHeight(ttId) * 0.5f))
	{
		Vside1 = -1.0f;
		collisionHappened = true;
	}

	return collisionHappened;
}

bool CheckEdgeBoundaries2(X::Math::Vector2 vec, X::TextureId ttId)
{
	bool collisionHappened = false;

	// colliding with left
	if (vec.x < (X::GetSpriteWidth(ttId) * 0.5f))
	{
		Hside2 = 1.0f;
		vec.x = vec.x;
		collisionHappened = true;
	}

	// colliding with right
	if (vec.x > (X::GetScreenWidth() - X::GetSpriteWidth(ttId) * 0.5f))
	{
		Hside2 = -1.0f;
		collisionHappened = true;
	}

	// colliding with top
	if (vec.y < (X::GetSpriteHeight(ttId) * 0.5f))
	{
		Vside2 = 1.0f;
		collisionHappened = true;
	}

	// colliding with bot
	if (vec.y > (X::GetScreenHeight() - X::GetSpriteHeight(ttId) * 0.5f))
	{
		Vside2 = -1.0f;
		collisionHappened = true;
	}

	return collisionHappened;
}


void updatePikachu(float deltaTime)
{
	const float	speed = 100.0f;
	position1.x += speed * deltaTime * Hside1;
	position1.y += speed * deltaTime * Vside1;
	CheckEdgeBoundaries(position1, textureId);
	CheckCollison(position1, textureId, position2, textureId2);
}




void updateMario(float deltaTime)
{
	const float	speed = 100.0f;
	position2.x += speed * deltaTime * Hside2;
	position2.y += speed * deltaTime * Vside2;
	CheckEdgeBoundaries2(position2, textureId2);
	CheckCollison(position1, textureId, position2, textureId2);
}

bool GameLoop(float deltaTime)
{
	/*
	if (X::IsKeyDown(X::Keys::RIGHT))
	{
		if (position1.x < (X::GetScreenWidth() - X::GetSpriteWidth(textureId) * 0.5f))
		{
			position1.x += speed * deltaTime;
		}
	}
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		if (position1.x > (X::GetSpriteWidth(textureId) * 0.5f))
		{
			position1.x -= speed * deltaTime;
			
		}
	}
	if (X::IsKeyDown(X::Keys::UP))
	{
		if (position1.y > (X::GetSpriteHeight(textureId) * 0.5f))
		{
			position1.y -= speed * deltaTime;
		}
	}
	if (X::IsKeyDown(X::Keys::DOWN))
	{
		if (position1.y < (X::GetScreenHeight() - X::GetSpriteHeight(textureId) * 0.5f))
		{
			position1.y += speed * deltaTime;
		}
	}*/


	updatePikachu(deltaTime);
	updateMario(deltaTime);

	X::DrawSprite(textureId, position1);
	X::DrawSprite(textureId2, position2);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}




int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	int ScreenWith = X::GetScreenHeight();
	int ScreenHeight = X::GetScreenHeight();

	textureId = X::LoadTexture("pikachu.png");
	textureId2 = X::LoadTexture("mario_jump_01.png");
	
	position1.y = ScreenHeight * 0.5f;
	position1.x = X::GetSpriteWidth(textureId) * 0.6f;

	position2.y = (float)ScreenWith - X::GetSpriteHeight(textureId2);
	position2.x = X::GetSpriteWidth(textureId2) * 0.5f;

	X::Run(GameLoop);
	X::Stop();
	return 0;
}