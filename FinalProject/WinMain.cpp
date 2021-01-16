#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "BackGroundManager.h"
#include "Player.h"
#include "SecondPlayer.h"
#include "SpriteAnimation.h"
#include "AnimationManager.h"

int screenWidth = 0;
int screenHeight = 0;
bool debug = false;

std::string myBackground[2] = { "audience.png", "boxing_ring.png"};
std::string myPlayer[2] = { "Boxing_Idle.png", "KO_1.png" };

// to fix collision problem
// bool mIsHitting = false
//	if (!mIsHitting)
//		if (collision)
//			mIsHitting = true
//			deal damage
//	else
//		if (!collision)
//			mIsHitting = false

BgSetup bgsetup;
Player playerA;
SecondPlayer playerB;

AnimationManager myAnimationManager;
AnimationManager myAnimationManager2;

std::vector<int> playerAData;
std::vector<int> playerBData;


int player1Health;
int player2Health;

char playerName1[1024]{};
char playerName2[1024]{};
std::string winnerName;


void ShowInfo(); 

enum class GameState
{
	StartScreen,
	Gameplay,
	GameOver
};

GameState gameState = GameState::StartScreen;

void GameInit()
{
	screenWidth = X::GetScreenWidth();
	screenHeight = X::GetScreenHeight();

	bgsetup.Load(myBackground);
	bgsetup.SetScreenInfo((float)screenWidth, (float)screenHeight);

	myAnimationManager.CreateAnimationlist(1);
	myAnimationManager.Play(AnimationName::Dizzy, { 200.0f,450.0f });

	myAnimationManager2.CreateAnimationlist(2);
	myAnimationManager2.Play(AnimationName::Dizzy, { 1100.0f,450.0f });

	playerA.Load(myPlayer);
	playerA.SetPosition({ 200.0f,450.0f });
	playerA.SetAnimationMap(myAnimationManager);

	playerB.Load(myPlayer);
	playerB.SetPosition({ 1100.0f,450.0f });
	playerB.SetAnimationMap(myAnimationManager2);
}

void GameLoopStart(float deltaTime)
{
	ShowInfo();
	
	if (bgsetup.IsStartGame())
	{
		gameState = GameState::Gameplay;
	}


	// Update
	bgsetup.Update(deltaTime);
	myAnimationManager.Update(deltaTime, AnimationName::Dizzy);
	myAnimationManager2.Update(deltaTime, AnimationName::Dizzy);

	
	// Render
	bgsetup.Render();
	myAnimationManager.Render(AnimationName::Dizzy);
	myAnimationManager2.Render(AnimationName::Dizzy);

}

void GameLoopEnd(float deltaTime)
{
	ShowInfo();
	
}

void ShowInfo()
{
	switch (gameState)
	{
	case GameState::StartScreen:
	{
		float xPos = screenWidth * 0.4f;
		float yPos = screenHeight * 0.5f;
		ImGui::SetNextWindowPos({ xPos, yPos });
		ImGui::Begin("Enter Player Name", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::InputText(":Player A", playerName1, std::size(playerName1));
		ImGui::InputText(":Player B", playerName2, std::size(playerName2));
		if (ImGui::Button("Start Game"))
		{
			playerA.SetPlayerName(playerName1);
			bgsetup.SetScreenStart(true);
			myAnimationManager.Stop(AnimationName::Dizzy);
			myAnimationManager2.Stop(AnimationName::Dizzy);
			playerA.ChangeState(StateMachine::Idle);
			playerB.ChangeState(StateMachineB::IdleB);
		}
		ImGui::End();

		ImGui::SetNextWindowPos({ xPos, yPos + 110.0f });
		ImGui::Begin("Game Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Player A: \nA(move left) S(Blocking) D(move right)\n C(punch left) V(Punch right) B(punch Up)");
		ImGui::Text("Player B: \nLeft(move left) Down(Blocking) Right(move right)\n I(punch left) O(punch right) P(punch Up)");

		ImGui::End();
		break;
	}
	case GameState::Gameplay:
	{
		ImGui::SetNextWindowPos({ 20.0f,20.0f });
		player1Health = playerA.GetHealth();
		ImGui::Begin("PlayerA Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Player Name: %s", playerName1);
		ImGui::Text("Player Health: %i", player1Health);
		ImGui::End();

		ImGui::SetNextWindowPos({ 1100.0f,20.0f });
		player2Health = playerB.GetHealth();
		ImGui::Begin("PlayerB Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Player Name: %s", playerName2);
		ImGui::Text("Player Health: %i", player2Health);
		ImGui::End();
		break;
	}
	case GameState::GameOver:
	{
		ImGui::SetNextWindowPos({ 20.0f,20.0f });
		ImGui::Begin("PlayerA Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Player Name: %s", playerName1);
		ImGui::Text("Player Health: %i", player1Health);
		playerAData = playerB.GetDamageData();
		ImGui::Text("Total Punching Times: %i", playerAData.size());
		for (int i = 0; i < playerAData.size(); i++)
		{
			ImGui::Text("Punching Damage: %i", playerAData[i]);
		}
		ImGui::End();

		ImGui::SetNextWindowPos({ 1100.0f,20.0f });
		ImGui::Begin("PlayerB Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Player Name: %s", playerName2);
		ImGui::Text("Player Health: %i", player2Health);
		playerAData = playerA.GetDamageData();
		ImGui::Text("Total Punching Times: %i", playerAData.size());
		for (int i = 0; i < playerAData.size(); i++)
		{
			ImGui::Text("Punching Damage: %i", playerAData[i]);
		}
		ImGui::End();

		X::DrawScreenText(winnerName.c_str(), 420, 250, 80, X::Math::Vector4::LightRed());
		X::DrawScreenText("is Winner", 420, 350, 120, X::Math::Vector4::LightRed());

		break;
	}
	default:
		break;
	}
	
}

void CheckCollision()
{
	auto playerAPos = playerA.GetBoundary();
	auto playerBPos = playerB.GetBoundary();
	if (X::Math::Intersect(playerAPos,playerBPos))
	{
		if (playerA.IsPunching())
		{
			if (!playerB.IsBlocking())
			{
				playerB.GetHurt();
			}
		}
		else if (playerB.IsPunching())
		{
			if (!playerA.IsBlocking())
			{
				playerA.GetHurt();
			}
		}
	}
}

void CheckPlayerHealth()
{
	if (player1Health == 0)
	{
		winnerName = playerName2;
		gameState = GameState::GameOver;
	}
	if (player2Health == 0)
	{
		winnerName = playerName1;
		gameState = GameState::GameOver;
	}
}

void GameLoop(float deltaTime)
{
	ShowInfo();

	if (X::IsKeyPressed(X::Keys::MINUS))
	{
		debug = !debug;
	}

	// Update
	bgsetup.Update(deltaTime);
	playerA.Update(deltaTime);
	playerB.Update(deltaTime);


	//Render
	bgsetup.Render();
	playerA.Render(debug);
	playerB.Render(debug);

	CheckCollision();
	CheckPlayerHealth();
}



bool MainLoop(float deltaTime)
{
	switch (gameState)
	{
	case GameState::StartScreen:
		GameLoopStart(deltaTime);
		break;
	case GameState::Gameplay:
		GameLoop(deltaTime);
		break;
	case GameState::GameOver:
		GameLoopEnd(deltaTime);
		break;
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}



int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();
	X::Run(MainLoop);
	X::Stop();
	return 0;
}