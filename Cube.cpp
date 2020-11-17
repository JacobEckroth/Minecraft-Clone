#include "Cube.h"
#include "glslprogram.h"
#include <iostream>
float Cube::CUBEWIDTH = 1.;

#define CUBEAMOUNT 2.



void Cube::initCubeList(int& MainWindow,int newCubeType) {

	glutSetWindow(MainWindow);
	cubeType = newCubeType;

	float initialS = (float(cubeType - 1)) / float(CUBEAMOUNT);

	float increase = 1 / (CUBEAMOUNT * 3.);		//divided by 3 because we do side bottom top
	// create the object:

	//cubeList = glGenLists(1);
	//glNewList(cubeList, GL_COMPILE);


	
	xNegativeFace = glGenLists(1);
	glNewList(xNegativeFace, GL_COMPILE);
	glBegin(GL_QUADS);
	glColor3f(0. , 1., 1.);

	
	glNormal3f(-1., 0., 0.);

	glTexCoord2f(initialS,0);
	glVertex3f(position.x,position.y,position.z);
	glTexCoord2f(initialS+increase,0);
	glVertex3f(position.x, position.y,position.z+ CUBEWIDTH);
	glTexCoord2f(initialS + increase,1);
	glVertex3f(position.x,position.y+ CUBEWIDTH, position.z+CUBEWIDTH);
	glTexCoord2f(initialS,1);
	glVertex3f(position.x, position.y+CUBEWIDTH, position.z);
	glEnd();
	glEndList();
	
	xPositiveFace = glGenLists(1);
	glNewList(xPositiveFace, GL_COMPILE);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(initialS + increase, 1);
	glVertex3f(position.x+CUBEWIDTH, position.y+CUBEWIDTH, position.z);
	glTexCoord2f(initialS + increase, 0);
	glVertex3f(position.x+CUBEWIDTH, position.y+CUBEWIDTH,position.z+ CUBEWIDTH);
	glTexCoord2f(initialS, 0);
	glVertex3f(position.x+CUBEWIDTH, position.y, position.z+CUBEWIDTH);
	glTexCoord2f(initialS, 1);
	glVertex3f(position.x+CUBEWIDTH, position.y, position.z);
	glEnd();
	glEndList();


	zNegativeFace = glGenLists(1);
	glNewList(zNegativeFace, GL_COMPILE);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(initialS + increase, 0);
	glVertex3f(position.x, position.y, position.z);
	glTexCoord2f(initialS + increase, 1);
	glVertex3f(position.x, position.y+CUBEWIDTH, position.z);
	glTexCoord2f(initialS, 1);
	glVertex3f(position.x+CUBEWIDTH,position.y+ CUBEWIDTH, position.z);
	glTexCoord2f(initialS, 0);
	glVertex3f(position.x+CUBEWIDTH, position.y, position.z);
	glEnd();
	glEndList();


	zPositiveFace = glGenLists(1);
	glNewList(zPositiveFace, GL_COMPILE);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(initialS + increase, 0);
	glVertex3f(position.x+CUBEWIDTH, position.y, position.z+CUBEWIDTH);
	glTexCoord2f(initialS + increase, 1);
	glVertex3f(position.x+CUBEWIDTH, position.y+CUBEWIDTH, position.z+CUBEWIDTH);
	glTexCoord2f(initialS, 1);
	glVertex3f(position.x,position.y + CUBEWIDTH,position.z+ CUBEWIDTH);
	glTexCoord2f(initialS, 0);
	glVertex3f(position.x, position.y,position.z+ CUBEWIDTH);
	glEnd();
	glEndList();
	

	yNegativeFace = glGenLists(1);
	glNewList(yNegativeFace, GL_COMPILE);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(initialS + increase , 1);
	glVertex3f(position.x+CUBEWIDTH, position.y, position.z);
	glTexCoord2f(initialS + increase*2, 1);
	glVertex3f(position.x+CUBEWIDTH, position.y, position.z+CUBEWIDTH);
	glTexCoord2f(initialS + increase * 2, 0);
	glVertex3f(position.x, position.y,position.z+ CUBEWIDTH);
	glTexCoord2f(initialS + increase, 0);
	glVertex3f(position.x, position.y, position.z);
	glEnd();
	glEndList();



	yPositiveFace = glGenLists(1);
	glNewList(yPositiveFace, GL_COMPILE);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(initialS + increase*2, 0);
	glVertex3f(position.x,position.y+ CUBEWIDTH, position.z);
	glTexCoord2f(initialS + increase * 3, 0);
	glVertex3f(position.x,position.y+ CUBEWIDTH,position.z+ CUBEWIDTH);
	glTexCoord2f(initialS + increase * 3, 1);
	glVertex3f(position.x+CUBEWIDTH, position.y+CUBEWIDTH,position.z+ CUBEWIDTH);
	glTexCoord2f(initialS + increase * 2, 1);
	glVertex3f(position.x+CUBEWIDTH, position.y+CUBEWIDTH, position.z);
	glEnd();
	glEndList();
	
	cubeList = glGenLists(1);
	glNewList(cubeList, GL_COMPILE);
	glCallList(yPositiveFace);
	glCallList(yNegativeFace);
	glCallList(xPositiveFace);
	glCallList(xNegativeFace);
	glCallList(zPositiveFace);
	glCallList(zNegativeFace);
	glEndList();
	
	
	






}



void Cube::render() {

}

GLuint Cube::getPositiveYFace() {
	return yPositiveFace;
}
GLuint Cube::getNegativeYFace() {
	return yNegativeFace;
}
GLuint Cube::getPositiveXFace() {
	return xPositiveFace;
}
GLuint Cube::getNegativeXFace() {
	return xNegativeFace;
}
GLuint Cube::getNegativeZFace() {
	return zNegativeFace;
}
GLuint Cube::getPositiveZFace() {
	return zPositiveFace;
}