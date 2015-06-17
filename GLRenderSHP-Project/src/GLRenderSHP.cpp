/*
Simple ShapeFile OpenGL renderer.
Adapted from http://www.codeproject.com/Articles/32035/Rendering-Shapefile-in-OpenGL

Authors
-Tiago Augusto Engel (tengel@inf.ufsm.br)
-Cesar Pozzer		 (pozzer@inf.ufsm.br)

Using ShapeLib version 1.3
*/


#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

#include "shapefil.h"
#include <vector>

#include "ShapeFile.h"

using namespace std;

vec4 shpBoundaries;
vector<ShapeFile> g_Shapefiles;

void initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	//Assign Default Map Bounds to glOrtho
	//min
	shpBoundaries.x = -180.0f;
	shpBoundaries.y = -90.0f;
	//max
	shpBoundaries.z = 180.0f;
	shpBoundaries.w = 90.0f;
}

void resizeGL(int w, int h)
{
	if (h <= 0) h = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Assign Bounding Box Coordinates of Shapefile to glOrtho()
	glOrtho(shpBoundaries.x, shpBoundaries.z, shpBoundaries.y, shpBoundaries.w, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glLoadIdentity();

	/// render all shapes
	for (int i = 0; i < g_Shapefiles.size(); i++){
		g_Shapefiles[i].render();
	}
	glFlush();
}

void keyCB(unsigned char key, int x, int y){
	if (int(key) == 27){ // esc
		cout << "Viewer terminating..." << endl;
		g_Shapefiles.clear();
		exit(1);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("ShapeFile Viewer");
	initializeGL();

	g_Shapefiles.push_back(*(new ShapeFile("Shapefiles\\strassen"))); //line
	//g_Shapefiles.push_back(*(new ShapeFile("Shapefiles\\poi"))); //point
	//g_Shapefiles.push_back(*(new ShapeFile("Shapefiles\\gruenflaechen"))); //polygon
	//g_Shapefiles.push_back(*(new ShapeFile("Shapefiles\\polygon"))); //polygon
	shpBoundaries = g_Shapefiles[0].getBoundaries();

	glutKeyboardFunc(keyCB);
	glutReshapeFunc(resizeGL);
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}
