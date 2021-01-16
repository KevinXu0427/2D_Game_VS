#ifndef INCLUDED_SPRITEANIMATION_H
#define INCLUDED_SPRITEANIMATION_H

#include "XEngine.h"
#include "Camera.h"

class SpriteAnimation
{
public:
	struct Info
	{
		std::string fileName;
		int rows{ 0 };
		int columns{ 0 };
		int frameCount{ 0 };
		float framePerSecond{ 16.0f };
		bool looping{ false };

	};
	void Load(Info info);
	void Unload();
	void Update(float deltaTime);
	void Render(const Camera& camera) const;

	void Play();
	void Stop();

	void SetPosition(const X::Math::Vector2 position) { mPosition = position; }

private:
	X::Math::Vector2 mPosition{ 300.0f, 300.0f };
	X::TextureId mSpriteSheetId = 0;
	Info mInfo;
	float mTimer{ 0.0f };
	bool mActive{ false };

};

#endif // !INCLUDED_SPRITEANIMATION_H