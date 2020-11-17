#pragma once
#include "WorldObject.h"
#include "glslprogram.h"
#include "glew.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
class Cube: public WorldObject
{
public:
	static float CUBEWIDTH;
	
	
	int getCubeType() {
		return cubeType;
	}
	void setType(int newType) {
		cubeType = newType;
	}

	void render();
	void initCubeList(int&,int);
	GLuint getPositiveYFace();
	GLuint getPositiveXFace();
	GLuint getPositiveZFace();
	GLuint getNegativeYFace();
	GLuint getNegativeXFace();
	GLuint getNegativeZFace();
private:
	GLuint cubeList;

	
	GLuint zPositiveFace;
	GLuint zNegativeFace;
	GLuint yPositiveFace;
	GLuint yNegativeFace;
	GLuint xPositiveFace;
	GLuint xNegativeFace;
	int cubeType;
};

