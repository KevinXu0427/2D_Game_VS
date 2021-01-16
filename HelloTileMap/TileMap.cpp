#include "TileMap.h"
#include <ImGui/Inc/imgui.h>

void TileMap::LoadMap(const char* mapFileName)
{
	FILE* file = nullptr;
	fopen_s(&file, mapFileName, "r");
	if (file == nullptr)
	{
		return;
	}

	fscanf_s(file, "Rows: %d\n", &mRows);
	fscanf_s(file, "Colums: %d\n", &mColums);

	mTileMap = std::make_unique<int[]>(mRows * mColums);

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColums; ++x)
		{
			int index = x + (y * mColums);
			mTileMap[index] = fgetc(file) - '0';
		}
		fgetc(file);
	}

	fclose(file);
}

void TileMap::SaveMap(const char* mapFileName)
{
	FILE* file = nullptr;
	fopen_s(&file, mapFileName, "w");
	if (file == nullptr)
	{
		return;
	}

	fprintf_s(file, "Rows: %d\n", mRows);
	fprintf_s(file, "Colums: %d\n", mColums);

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColums; ++x)
		{
			int index = x + (y * mColums);
			fprintf_s(file, "%d", mTileMap[index]);
			
		}
		fprintf_s(file, "\n");
	}

	fclose(file);
}

void TileMap::UnloadMap()
{
	mTileMap.reset();
}

void TileMap::LoadTextures(const char* textureListFileName)
{
	FILE* file = nullptr;
	fopen_s(&file, textureListFileName, "r");
	if (file == nullptr)
	{
		return;
	}

	fscanf_s(file, "TextureCount: %d\n", &mTextureCount);

	mTextureIds = std::make_unique<X::TextureId[]>(mTextureCount);

	for (size_t i = 0; i < mTextureCount; ++i)
	{
		char textureName[1024];
		fscanf_s(file, "%s\n", textureName,std::size(textureName));
		mMapName.push_back(textureName);
		mTextureIds[i] = X::LoadTexture(textureName);
	}

	fclose(file);
}

void TileMap::UnloadTextures()
{
	mTextureIds.reset();
}


void TileMap::Update(float deltaTime, const Camera& camera)
{
	float tileWidth = (float)(X::GetSpriteWidth(mTextureIds[0]));
	float tileHeight = (float)(X::GetSpriteHeight(mTextureIds[0]));

	if (IsEditorEnable())
	{
		ShowEditor();

		if (X::IsKeyPressed(X::Keys::C))
		{
			if (mChange < mTextureCount-1)
			{
				mChange++;
			}
			else
			{
				mChange = 0;
			}
		}

		if (X::IsMouseDown(X::Mouse::LBUTTON))
		{
			X::Math::Vector2 mousePos;
			mousePos.x = X::GetMouseScreenX();
			mousePos.y = X::GetMouseScreenY();
			mousePos = camera.ConvertToWorldPosition(mousePos);

			//int colum = (int)(X::GetMouseScreenX() / tileWidth);
			//int row = (int)(X::GetMouseScreenY() / tileHeight);

			int colum = (int)(mousePos.x / tileWidth);
			int row = (int)(mousePos.y / tileHeight);

			int index = colum + (row * mColums);
			mTileMap[index] = mChange;

			/*if (mTileMap[index] < 5)
			{
				mTileMap[index]++;
			}
			else
			{
				mTileMap[index] = 0;
			}*/

		}
	}
}

void TileMap::Render(const Camera& camera)
{
	float tileWidth = (float)(X::GetSpriteWidth(mTextureIds[0]));
	float tileHeight = (float)(X::GetSpriteHeight(mTextureIds[0]));

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColums; ++x)
		{
			int index = x + (y * mColums);
			int tile = std::min(mTileMap[index], mTextureCount - 1); 
			float posX = (x + 0.5f) * tileWidth;
			float posY = (y + 0.5f) * tileHeight;
			//X::DrawSprite(mTextureIds[tile], { posX, posY });
			camera.Draw(mTextureIds[tile], { posX,posY });
		}
	}
}

bool TileMap::CheckCollision(const X::Math::LineSegment & lineSegment) const
{
	float tileWidth = (float)(X::GetSpriteWidth(mTextureIds[0]));
	float tileHeight = (float)(X::GetSpriteHeight(mTextureIds[0]));

	int startX = (int)(lineSegment.from.x / tileWidth);
	int startY = (int)(lineSegment.from.y / tileHeight);
	int endX = (int)(lineSegment.to.x / tileHeight);
	int endY = (int)(lineSegment.to.y / tileHeight);

	if (startX < 0 || startX >= mColums || endX < 0 || endX >= mColums ||
		startY < 0 || startY >= mRows || endY < 0 || endY >= mRows)
	{
		return false;
	}
	
	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)
		{
			int index = x + (y * mColums);
			int tile = mTileMap[index];
			if (tile != 0) // not always true
			{
				return true;
			}
		}
	}

	return false;
}

void TileMap::ShowEditor()
{
	ImGui::Begin("Tile Map Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	std::string mapName = mMapName[mChange];
	ImGui::Text("Current Tile Name: %s",mapName.c_str());

	if (ImGui::Button("Load Tile Set 1"))
	{
		char fileName[MAX_PATH] = {};
		if (X::SaveFileDialog(fileName, "Load Tile"))
		{
			UnloadTextures();
			LoadTextures(fileName);
		}
	}

	if (ImGui::Button("Load Tile Set 2"))
	{
		char fileName[MAX_PATH] = {};
		if (X::SaveFileDialog(fileName, "Load Tile"))
		{
			UnloadTextures();
			LoadTextures(fileName);
		}

	}

	if (ImGui::Button("Save Map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::SaveFileDialog(fileName, "Save Map"))
		{
			SaveMap(fileName);
		}
	}
	ImGui::End();
}
