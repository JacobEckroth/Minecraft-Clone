#include "Chunk.h"
#include <iostream>
int Chunk::maxHeight = 128;
int Chunk::chunkXWidth = 16;
int Chunk::chunkZWidth = 16;
GLuint Chunk::textureName;
GLSLProgram* Chunk::Pattern;

unsigned char* Chunk::textureSheet;


#define RENDERSIDES true

unsigned char* BmpToTexture(char*, int*, int*);
short			ReadShort(FILE*);
void			HsvRgb(float[3], float[3]);
int				ReadInt(FILE*);


void Chunk::initTexture() {

	glGenTextures(1, &textureName);
	int nums, numt;
	textureSheet = BmpToTexture("spriteSheet.bmp", &nums, &numt);
	glBindTexture(GL_TEXTURE_2D, textureName);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, nums, numt, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSheet);

}

void Chunk::deleteCube(int x, int y, int z) {
	cubes[x][y][z].setType(0);
	createMesh();
}



void Chunk::initCubeShader() {
	Pattern = new GLSLProgram();
	bool valid = Pattern->Create("basic.vert", "basic.frag");
	if (!valid)
	{
		printf("AHHHHHH SHADERS FUCKED UP \n");
	}
}

Chunk::~Chunk() {
	for (int x = 0; x < chunkXWidth; x++) {
		for (int y = 0; y < maxHeight; y++) {
			delete[] cubes[x][y];
		}
	}
	for (int x = 0; x < chunkXWidth; x++) {
		delete[] cubes[x];
	}
	delete[] cubes;
}


//does not render faces at the side of the cube.
void Chunk::createMesh() {
	meshList = glGenLists(1);
	glNewList(meshList, GL_COMPILE);
	for (int x = 0; x < chunkXWidth; x++) {
		for (int y = 0; y < maxHeight; y++) {
			for (int z = 0; z < chunkZWidth; z++) {
				if (cubes[x][y][z].getCubeType() == 0) {
			
					continue;
				}
				else {
					if (RENDERSIDES) {
						if (y + 1 >= maxHeight || cubes[x][y + 1][z].getCubeType() == 0) {
							glCallList(cubes[x][y][z].getPositiveYFace());
						}
						if (y - 1 < 0 || cubes[x][y - 1][z].getCubeType() == 0) {
							glCallList(cubes[x][y][z].getNegativeYFace());
						}
						if (x + 1 >= chunkXWidth|| cubes[x+1][y][z].getCubeType() == 0) {
							glCallList(cubes[x][y][z].getPositiveXFace());
						}
						if (x - 1 < 0 || cubes[x-1][y][z].getCubeType() == 0) {
							glCallList(cubes[x][y][z].getNegativeXFace());
						}
						if (z+ 1 >= chunkZWidth || cubes[x][y][z+1].getCubeType() == 0) {
							glCallList(cubes[x][y][z].getPositiveZFace());
						}
						if (z - 1 < 0 || cubes[x][y][z-1].getCubeType() == 0) {
							glCallList(cubes[x][y][z].getNegativeZFace());
						}
						

					}
					else {
						if (y + 1 < maxHeight) {
							if (cubes[x][y + 1][z].getCubeType() == 0) {
								glCallList(cubes[x][y][z].getPositiveYFace());
							}
						}
						if (y - 1 >= 0) {
							if (cubes[x][y - 1][z].getCubeType() == 0) {
								glCallList(cubes[x][y][z].getNegativeYFace());
							}
						}
						if (x + 1 < chunkXWidth) {
							if (cubes[x + 1][y][z].getCubeType() == 0) {
								glCallList(cubes[x][y][z].getPositiveXFace());
							}
						}
						if (x - 1 >= 0) {
							if (cubes[x - 1][y][z].getCubeType() == 0) {
								glCallList(cubes[x][y][z].getNegativeXFace());
							}
						}
						if (z + 1 < chunkZWidth) {
							if (cubes[x][y][z + 1].getCubeType() == 0) {
								glCallList(cubes[x][y][z].getPositiveZFace());
							}
						}
						if (z - 1 >= 0) {
							if (cubes[x][y][z - 1].getCubeType() == 0) {
								glCallList(cubes[x][y][z].getNegativeZFace());
							}
						}
					}

				}



			}
		}
	}
	glEndList();


}

void Chunk::init(int blockType,int& mainWindow) {
	glm::vec3 newPosition(0, 0, 0);
	setPosition(newPosition);

	cubes = new Cube**[chunkXWidth];
	for (int x = 0; x < chunkXWidth; x++) {
	
		cubes[x] = new Cube* [maxHeight];
	}
	for (int x = 0; x < chunkXWidth; x++) {
		for (int y = 0; y < maxHeight; y++) {
		
			cubes[x][y] = new Cube  [chunkZWidth];
		}
	}
	for (int x = 0; x < chunkXWidth; x++) {
		for (int y = 0; y < maxHeight; y++) {
			for (int z = 0; z < chunkZWidth; z++) {
			
				cubes[x][y][z].setPosition(getPosition() + glm::vec3(x,y,z));
				cubes[x][y][z].initCubeList(mainWindow,rand() % 3);
			}
		}
	}
	

	createMesh();
}


void Chunk::printChunkLayer(int z) {
	for (int x = 0; x < chunkXWidth; x++) {
		for (int y = 0; y < maxHeight; y++) {
			std::cout << cubes[x][y][z].getCubeType() << ' ';
		}
		std::cout << std::endl;
	}
}

Chunk::Chunk() {

}

void Chunk::render() {

	Pattern->Use();

	glActiveTexture(GL_TEXTURE5);		//texture stuff
	glBindTexture(GL_TEXTURE_2D, textureName);
	Pattern->SetUniformVariable("uTexUnit", 5);
	float ambient = .3;					//lighting stuff
	float diffuse = .4;
	float specular = .3;
	float shininess = 3.;
	glm::vec3 objectColor(0, .7, .5);
	glm::vec3 uSpecularColor(.7, .3, .2);
	glm::vec3 LIGHT1POSITION(-1, 2., 0.);
	Pattern->SetUniformVariable("LIGHT1POSITION", LIGHT1POSITION);
	Pattern->SetUniformVariable("uKa", ambient);
	Pattern->SetUniformVariable("uKd", diffuse);
	Pattern->SetUniformVariable("uKs", specular);
	Pattern->SetUniformVariable("uShininess", shininess);
	
	Pattern->SetUniformVariable("uSpecularColor", uSpecularColor);
	Pattern->SetUniformVariable("CHUNKPOSITION", position);
	glCallList(meshList);
	Pattern->Use(0);


	
}

const int birgb = { 0 };
struct bmfh
{
	short bfType;
	int bfSize;
	short bfReserved1;
	short bfReserved2;
	int bfOffBits;
} FileHeader;

struct bmih
{
	int biSize;
	int biWidth;
	int biHeight;
	short biPlanes;
	short biBitCount;
	int biCompression;
	int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	int biClrUsed;
	int biClrImportant;
} InfoHeader;


unsigned char*
BmpToTexture(char* filename, int* width, int* height)
{
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		fprintf(stderr, "Cannot open Bmp file '%s'\n", filename);
		return NULL;
	}

	FileHeader.bfType = ReadShort(fp);


	// if bfType is not 0x4d42, the file is not a bmp:

	if (FileHeader.bfType != 0x4d42)
	{
		fprintf(stderr, "File '%s' is the wrong type of file: 0x%0x\n", filename, FileHeader.bfType);
		fclose(fp);
		return NULL;
	}

	FileHeader.bfSize = ReadInt(fp);
	FileHeader.bfReserved1 = ReadShort(fp);
	FileHeader.bfReserved2 = ReadShort(fp);
	FileHeader.bfOffBits = ReadInt(fp);

	InfoHeader.biSize = ReadInt(fp);
	InfoHeader.biWidth = ReadInt(fp);
	InfoHeader.biHeight = ReadInt(fp);

	int nums = InfoHeader.biWidth;
	int numt = InfoHeader.biHeight;

	InfoHeader.biPlanes = ReadShort(fp);
	InfoHeader.biBitCount = ReadShort(fp);
	InfoHeader.biCompression = ReadInt(fp);
	InfoHeader.biSizeImage = ReadInt(fp);
	InfoHeader.biXPelsPerMeter = ReadInt(fp);
	InfoHeader.biYPelsPerMeter = ReadInt(fp);
	InfoHeader.biClrUsed = ReadInt(fp);
	InfoHeader.biClrImportant = ReadInt(fp);

	fprintf(stderr, "Image size in file '%s' is: %d x %d\n", filename, nums, numt);

	unsigned char* texture = new unsigned char[3 * nums * numt];
	if (texture == NULL)
	{
		fprintf(stderr, "Cannot allocate the texture array!\b");
		return NULL;
	}

	// extra padding bytes:

	int numextra = 4 * (((3 * InfoHeader.biWidth) + 3) / 4) - 3 * InfoHeader.biWidth;

	// we do not support compression:

	if (InfoHeader.biCompression != birgb)
	{
		fprintf(stderr, "Image file '%s' has the wrong type of image compression: %d\n", filename, InfoHeader.biCompression);
		fclose(fp);
		return NULL;
	}

	rewind(fp);
	fseek(fp, 14 + 40, SEEK_SET);

	if (InfoHeader.biBitCount == 24)
	{
		unsigned char* tp = texture;
		for (int t = 0; t < numt; t++)
		{
			for (int s = 0; s < nums; s++, tp += 3)
			{
				*(tp + 2) = fgetc(fp);		// b
				*(tp + 1) = fgetc(fp);		// g
				*(tp + 0) = fgetc(fp);		// r
			}

			for (int e = 0; e < numextra; e++)
			{
				fgetc(fp);
			}
		}
	}

	fclose(fp);

	*width = nums;
	*height = numt;
	return texture;
}



// read a BMP file into a Texture:



int
ReadInt(FILE* fp)
{
	unsigned char b3, b2, b1, b0;
	b0 = fgetc(fp);
	b1 = fgetc(fp);
	b2 = fgetc(fp);
	b3 = fgetc(fp);
	return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}

short
ReadShort(FILE* fp)
{
	unsigned char b1, b0;
	b0 = fgetc(fp);
	b1 = fgetc(fp);
	return (b1 << 8) | b0;
}


// function to convert HSV to RGB
// 0.  <=  s, v, r, g, b  <=  1.
// 0.  <= h  <=  360.
// when this returns, call:
//		glColor3fv( rgb );

void
HsvRgb(float hsv[3], float rgb[3])
{
	// guarantee valid input:

	float h = hsv[0] / 60.f;
	while (h >= 6.)	h -= 6.;
	while (h < 0.) 	h += 6.;

	float s = hsv[1];
	if (s < 0.)
		s = 0.;
	if (s > 1.)
		s = 1.;

	float v = hsv[2];
	if (v < 0.)
		v = 0.;
	if (v > 1.)
		v = 1.;

	// if sat==0, then is a gray:

	if (s == 0.0)
	{
		rgb[0] = rgb[1] = rgb[2] = v;
		return;
	}

	// get an rgb from the hue itself:

	float i = (float)floor(h);
	float f = h - i;
	float p = v * (1.f - s);
	float q = v * (1.f - s * f);
	float t = v * (1.f - (s * (1.f - f)));

	float r = 0., g = 0., b = 0.;			// red, green, blue
	switch ((int)i)
	{
	case 0:
		r = v;	g = t;	b = p;
		break;

	case 1:
		r = q;	g = v;	b = p;
		break;

	case 2:
		r = p;	g = v;	b = t;
		break;

	case 3:
		r = p;	g = q;	b = v;
		break;

	case 4:
		r = t;	g = p;	b = v;
		break;

	case 5:
		r = v;	g = p;	b = q;
		break;
	}


	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}