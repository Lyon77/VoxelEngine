#pragma once

namespace Voxel
{
	class Chunk;

	void makeFlatTerrain(Chunk* chunk);
	void makeStepTerrain(Chunk* chunk);
	void makeRandomTerrain(Chunk* chunk);

	void makeNaturalTerrain(Chunk* chunk);
}
