#include "TileMap.h"
#include "Player.h"
#include "Camera.h"
#include "SpriteAnimation.h"
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

TileMap myMap;
Player myMario;
Camera myCamera;
std::string myMarioPics[4] = {"mario_walk_01.png", "mario_walk_02.png", "mario_jump_01.png", "mario_idle_01.png" };
bool debug = false;
SpriteAnimation myAnimation;

void GameInit()
{
	int screenWidth = X::GetScreenWidth();
	int screenHeight = X::GetScreenHeight();
	
	SpriteAnimation::Info info;
	info.fileName = "blood_effect.png";
	info.rows = 4;
	info.columns = 4;
	info.frameCount = 16;
	info.framePerSecond = 16.0f;

	myAnimation.Load(info);
	myMap.LoadMap("MarioLevel01.txt");
	myMap.LoadTextures("MarioMapSet.txt");

	
	myMario.Load(myMarioPics);
	myMario.SetPosition({ screenWidth * 0.5f, screenHeight * 0.4f });
}

bool GameLoop(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::GRAVE))
	{
		myMap.EnableEditor(!myMap.IsEditorEnable());
	}
	
	if (X::IsKeyPressed(X::Keys::MINUS))
	{
		debug = !debug;
	}

	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		myAnimation.SetPosition(myMario.GetPosition());
		myAnimation.Play();
	}

	myCamera.SetViewPosition(myMario.GetPosition());

	myAnimation.Update(deltaTime);
	myMap.Update(deltaTime, myCamera);
	myMario.Update(myMap,deltaTime);

	myMap.Render(myCamera);
	myMario.Render(myCamera, debug);
	myAnimation.Render(myCamera);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanUp()
{
	myMap.UnloadMap();
	myMap.UnloadTextures();

	myMario.Unload();
	myAnimation.Unload();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();
	X::Run(GameLoop);
	GameCleanUp();
	X::Stop();
	return 0;
}