/*
Simple ShapeFile OpenGL renderer.
Adapted from http://www.codeproject.com/Articles/32035/Rendering-Shapefile-in-OpenGL

Authors
-Tiago Augusto Engel (tengel@inf.ufsm.br)
-Cesar Pozzer		 (pozzer@inf.ufsm.br)

Using ShapeLib version 1.3
*/

#include "shapefil.h"
#include "Vectors.h"
#include <vector>
#include <string>

using namespace std;

struct Entity{
	vector<vec3> points;
};

class ShapeFile {
public:
	ShapeFile(const char* filename);
	~ShapeFile();

	void printDBFHeader(int nFirstItems);
	void render();
	static const char* typeStr(int type);
	vec4 getBoundaries();

	static int shpCount;
private:
	vec2 boundBoxMin, boundBoxMax;
	int nEntities, shpType;
	string filename;
	SHPHandle hSHP;
	DBFHandle hDBF;
	vector<Entity> entities;

	void init();
	void beginPrimitive(int shpType);

	int shpID;
};