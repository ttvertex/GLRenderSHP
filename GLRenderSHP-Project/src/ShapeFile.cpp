/*
Simple ShapeFile OpenGL renderer.
Adapted from http://www.codeproject.com/Articles/32035/Rendering-Shapefile-in-OpenGL

Authors
-Tiago Augusto Engel (tengel@inf.ufsm.br)
-Cesar Pozzer		 (pozzer@inf.ufsm.br)

Using ShapeLib version 1.3
*/

#include "ShapeFile.h"
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

int ShapeFile::shpCount = 0;

ShapeFile::ShapeFile(const char* fileName){
	this->filename = string(fileName);
	init();

	shpID = ShapeFile::shpCount;
}

ShapeFile::~ShapeFile(){
	cout << "Closing SHP: " << filename << endl << endl;
	entities.clear();
}

/*
	Open, read the shapefile data to an array of Entities, then close the files.
*/
void ShapeFile::init(){
	ShapeFile::shpCount++;
	cout << ShapeFile::shpCount << endl;

	//////////// OPEN SHP
	hSHP = SHPOpen((filename + ".shp").c_str(), "rb");
	if (hSHP == NULL)
	{
		printf("error reading hSHP file");
		system("pause");
		exit(1);
	}
	/////////////// OPEN DBF
	hDBF = DBFOpen((filename + ".dbf").c_str(), "rb");
	if (hDBF == NULL)
	{
		printf("error reading hDBF file");
		system("pause");
		exit(1);
	}

	//////////// Get SHP info
	double padMinBound[4], padMaxBound[4]; // XYZM max and min values
	SHPGetInfo(hSHP, &nEntities, &shpType, padMinBound, padMaxBound);
	//Read Bounding Box of Shapefile
	boundBoxMax = vec2(padMaxBound[0], padMaxBound[1]);
	boundBoxMin = vec2(padMinBound[0], padMinBound[1]);

	cout << endl << "Reading " << filename << endl;
	cout << "#entities= " << nEntities << endl;
	cout << "ShapeType= " << typeStr(shpType) << endl;
	cout << "boundaries= " << boundBoxMin << ", " << boundBoxMax << endl;

	//printDBFHeader(10);

	//read entities and store them into a Vector
	cout << "Reading entities...." << endl;
	SHPObject *psShape;
	for (int i = 0; i < nEntities; i++)
	{
		psShape = SHPReadObject(hSHP, i); // le do arquivo
		if (psShape == NULL)
			return;

		//Pozzer
		//informacoes de cada shape
		//printf("\nEntities = %d\n", psShape->nVertices);
		//printf("\nParts = %d\n", psShape->nParts);

		//
		if (shpType == SHPT_POINT || shpType == SHPT_POINTZ){
			Entity e;
			e.points.push_back(vec3(psShape->padfX[0], psShape->padfY[0], psShape->padfZ[0]));
			entities.push_back(e);
		}
		else{
			//Pozzer
			//indice do vetor de shapes. Faz a leitura de traz para frente
			int idx = psShape->nVertices - 1;
			//Pozzer
			//para cada parte que compoe cada shape, determina o numero de primitivas (nParts)
			for (int i = psShape->nParts - 1; i >= 0; i--)
			{
				Entity e;
				//printf("\nPart[%d] = %d ",i, psShape->panPartStart[i]);
				for (; idx >= psShape->panPartStart[i]; idx--)
				{
					//printf("\n %f %f %f %f", psShape->padfX[j], psShape->padfY[j], psShape->padfZ[j], psShape->padfM );
					e.points.push_back(vec3(psShape->padfX[idx], psShape->padfY[idx], psShape->padfZ[idx]));
				}
				entities.push_back(e);
			}
			SHPDestroyObject(psShape); // deleta o objeto
		}
	}
	cout << "Entities successfully read: " << entities.size() << endl << endl;

	/// All data is already read, so we can close the files
	SHPClose(hSHP);
	DBFClose(hDBF);
	hSHP = NULL;
	hDBF = NULL;
}

/*
	De acordo com o tipo da primitva da Shape, aciona o glBegin correspondente.
	*/
void ShapeFile::beginPrimitive(int shpType){
	if (shpID == 1)
		glColor3f(1.0f, 0.0f, 0.0f);
	else if (shpID == 2)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 1.0f);
	if (shpType == SHPT_POINT || shpType == SHPT_POINTZ){ //Point | PointZ
		glColor3f(0.0, 0.0, 1.0);
		glEnable(GL_POINT_SMOOTH);
		glPointSize(5.0);
		glBegin(GL_POINTS);
	}
	else if (shpType == SHPT_ARC || shpType == SHPT_ARCZ){ //PolyLine | PolyLineZ
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINE_STRIP);
	}
	else if (shpType == SHPT_POLYGON || shpType == SHPT_POLYGONZ){ //Polygon | PolygonZ
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
	}
	else{ /// panic case
		cout << "Type not yet supported for rendering!" << endl;
		system("pause");
		exit(1);
	}
}

void ShapeFile::render(){
	// render each entity
	for (int i = 0; i < entities.size(); i++)
	{
		beginPrimitive(shpType);
		for (int j = 0; j < entities.at(i).points.size(); j++)
		{
			glVertex3fv(&entities.at(i).points.at(j)[0]);
		}
		glEnd();
	}
}

vec4 ShapeFile::getBoundaries(){
	return vec4(boundBoxMin.x, boundBoxMin.y, boundBoxMax.x, boundBoxMax.y);
}

/*
	Print the DBF header in format TYPE: ATTRIBUTE
	*/
void ShapeFile::printDBFHeader(int nFirstItems){
	char fieldName[12];
	int pnWidth, pnDecimals; // width in chars, number of decimal places of precision
	//// Field names and types
	cout << endl << "--------BEGIN DBF HEADER--------" << endl;
	for (int j = 0; j < DBFGetFieldCount(hDBF); j++){
		DBFFieldType field = DBFGetFieldInfo(hDBF, j, fieldName, &pnWidth, &pnDecimals);

		switch (field){
		case FTString:
			cout << "FTString:\t" << fieldName << endl;
			break;
		case FTInteger:
			cout << "FTInteger:\t" << fieldName << endl;
			break;
		case FTDouble:
			cout << "FTDouble:\t" << fieldName << endl;
			break;
		case FTLogical:
			cout << "FTLogical:\t" << fieldName << endl;
			break;
		case FTInvalid:
			cout << "FTInvalid:\t" << fieldName << endl;
			break;
		}
	}
	//// Field values
	/// pra imprimir no maximo as N primeiras entradas
	int upTo = (DBFGetRecordCount(hDBF) < nFirstItems) ? DBFGetRecordCount(hDBF) : nFirstItems;
	for (int i = 0; i < upTo; i++)
	{
		cout << endl;
		for (int j = 0; j < DBFGetFieldCount(hDBF); j++)
		{
			DBFFieldType field = DBFGetFieldInfo(hDBF, j, fieldName, &pnWidth, &pnDecimals);
			switch (field){
			case FTString:
				cout << DBFReadStringAttribute(hDBF, i, j) << "\t";
				break;
			case FTInteger:
				cout << DBFReadIntegerAttribute(hDBF, i, j) << "\t";
				break;
			case FTDouble:
				cout << DBFReadDoubleAttribute(hDBF, i, j) << "\t";
				break;
			case FTLogical:
				cout << DBFReadLogicalAttribute(hDBF, i, j) << "\t";
				break;
			case FTInvalid:
				cout << "null";
				break;
			}
		}
	}
	cout << endl;
	cout << "--------END DBF HEADER--------" << endl << endl;
}

const char* ShapeFile::typeStr(int def){
	switch (def){
	case SHPT_NULL:
		return "SHPT_NULL";
	case SHPT_POINT:
		return "SHPT_POINT";
	case SHPT_ARC:
		return "SHPT_ARC";
	case SHPT_POLYGON:
		return "SHPT_POLYGON";
	case SHPT_MULTIPOINT:
		return "SHPT_MULTIPOINT";
	case SHPT_POINTZ:
		return "SHPT_POINTZ";
	case SHPT_ARCZ:
		return "SHPT_ARCZ";
	case SHPT_POLYGONZ:
		return "SHPT_POLYGONZ";
	case SHPT_MULTIPOINTZ:
		return "SHPT_MULTIPOINTZ";
	case SHPT_POINTM:
		return "SHPT_POINTM";
	case SHPT_ARCM:
		return "SHPT_ARCM";
	case SHPT_POLYGONM:
		return "SHPT_POLYGONM";
	case SHPT_MULTIPOINTM:
		return "SHPT_MULTIPOINTM";
	case SHPT_MULTIPATCH:
		return "SHPT_MULTIPATCH";
	default:
		return "NOT RECOGNIZED";
	}
}
