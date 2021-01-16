#ifndef INCLUDED_TILEMAP_H
#define INCLUDED_TILEMAP_H

#include "Camera.h"
#include <XEngine.h>

class TileMap
{
public:
	void LoadMap(const char* mapFileName);
	void SaveMap(const char* mapFileName);
	void UnloadMap();

	void LoadTextures(const char* textureListFileName);
	void UnloadTextures();

	void Update(float deltaTime, const Camera& camera);
	void Render(const Camera& camera);

	void EnableEditor(bool enable) { mEnableEditor = enable; }
	bool IsEditorEnable() const { return mEnableEditor; }

	bool CheckCollision(const X::Math::LineSegment& lineSegment) const;

private:
	void ShowEditor();

	std::vector<std::string> mMapName;
	std::unique_ptr<int[]> mTileMap; // auto delet after left the pointer array
	std::unique_ptr<X::TextureId[]> mTextureIds;
	int mRows = 0;
	int mColums = 0;
	int mTextureCount = 0;
	int mChange = 0;
	bool mEnableEditor = false;
};


#endif // !INCLUDED_TILEMAP_H