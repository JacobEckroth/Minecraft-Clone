#pragma once
#include "WorldObject.h"
#include "Cube.h"
class Chunk: public WorldObject{


private:

	GLuint meshList;
	Cube*** cubes;
public:
	static unsigned char* textureSheet;
	static GLuint textureName;
	void deleteCube(int,int,int);
	static GLSLProgram* Pattern;
	static void initCubeShader();
	static void initTexture();
	static int maxHeight;
	static int chunkXWidth;
	static int chunkZWidth;

	
	void createMesh();

	void init(int,int&);
	Chunk();
	~Chunk();
	void render();


	void printChunkLayer(int z);
};

