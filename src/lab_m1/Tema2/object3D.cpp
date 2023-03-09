#include "object3D.h"
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#define DEG2RAD 3.14159/180.0


Mesh* object3D::CreateRectangle(const std::string &name, glm::vec3 center, float height, float width ,float depth ,glm::vec3 color) {


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(- width / 2, -height / 2, depth / 2), color),
		VertexFormat(center + glm::vec3(width / 2, -height / 2, depth / 2), color),
		VertexFormat(center + glm::vec3(-width / 2, height / 2, depth / 2), color),
		VertexFormat(center + glm::vec3(width / 2, height / 2, depth / 2), color),
		VertexFormat(center + glm::vec3(- width / 2, -height / 2, -depth / 2), color),
		VertexFormat(center + glm::vec3(width / 2, -height / 2, -depth / 2), color),
		VertexFormat(center + glm::vec3(-width / 2, height / 2, -depth / 2), color),
		VertexFormat(center + glm::vec3(width / 2, height / 2, -depth / 2), color),
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices =
        {
            0, 1, 2,   
            1, 3, 2,

            2, 3, 7,
            2, 7, 6,

            1, 7, 3,
            1, 5, 7,

            6, 7, 4, 
            7, 5, 4,

            0, 4, 1,
            1, 4, 5,

            2, 6, 4,
            0, 2, 4,

        };



	rectangle->InitFromData(vertices, indices);
	return rectangle;
}
Mesh* object3D::CreateMap(const std::string &name, glm::vec3 corner, float len, glm::vec3 color){
	std::vector<VertexFormat> vertices ;
	float dist=0.1;
	for(int i = 0;i <= len;i++)
		for(int j = 0;j <= len;j++)
			vertices.push_back(VertexFormat(corner + glm::vec3(j * dist, 0, i * dist), color));
	Mesh* map = new Mesh(name);
	std::vector<unsigned int> indices ;
	int multi;
	for(int i = 0;i < len;i++){
		multi = i * (len+1);
		for(int j = 0;j < len;j++){
			indices.push_back(j + multi);
			indices.push_back(j + 1 + multi);
			indices.push_back(j + multi + len + 1);

			indices.push_back(j + multi + len + 1);
			indices.push_back(j + 1 + multi);
			indices.push_back(j + 1 + multi + len + 1);


		}
	}
	map->InitFromData(vertices, indices);
	return map;
}
glm::vec3 object3D::punctsus(glm::vec3 punct1, glm::vec3 punct2, float dist){
	glm::vec3 D;
	D = punct2 - punct1;
	glm::vec3 P;
	P = cross( D , glm::vec3(0, 1, 0));
	P = glm::normalize(P);
	glm::vec3 R;
	R = punct1 + P * dist;
	
	return R; 
}
glm::vec3 object3D::punctjos(glm::vec3 punct1, glm::vec3 punct2, float dist){
	glm::vec3 D;
	D = punct2 - punct1;
	glm::vec3 P;
	P = cross( D , glm::vec3(0, 1, 0));
	P = glm::normalize(P);
	glm::vec3 R;
	R = punct1 - P * dist;
	return R; 
}
float object3D::arietriunghi(glm::vec3 P1,glm::vec3 P2,glm::vec3 P3){
	float A = sqrt((double)(P2.x-P1.x) * (P2.x-P1.x) + (P2.z-P1.z) * (P2.z-P1.z));
    float B = sqrt((double)(P2.x-P3.x) * (P2.x-P3.x) + (P2.z-P3.z) * (P2.z-P3.z));
    float C = sqrt((double)(P1.x-P3.x) * (P1.x-P3.x) + (P1.z-P3.z) * (P1.z-P3.z));
 
    float s = (A + B + C) / 2;
	float area;
    area = sqrt( s * (s-A) * (s-B) * (s-C));
  
    return area;

}
int object3D::vercoliziune(std::vector<glm::vec3> combinate,glm::vec3 pozacum){
	glm::vec3 P1;
	glm::vec3 P2;
	glm::vec3 P3;
	int i;

	int flag = 0;
	float artraseu = 0;
	//aria tringhimici cuu ajtoruul poz actuala
	float artrmici = 0;
	for(i = 0;i < 30;i++){
		P1 = combinate[i];
		P2 = combinate[i+1];
		P3 = combinate[i+2];
		artraseu = arietriunghi(P1,P2,P3);
		artrmici = arietriunghi(P1,P2,pozacum) + arietriunghi(P1,P3,pozacum) + arietriunghi(P2,P3,pozacum);
		artrmici =  roundf(artrmici * 1000) / 1000;
		artraseu =  roundf(artraseu * 1000) / 1000;
		if(artraseu == artrmici){
			flag = 1;
		}
	}
	return flag;

}

Mesh* object3D::CreateLap(const std::string &name, glm::vec3 color){
	std::vector<glm::vec3> punctemij = {
		glm::vec3(- 7, 0.05f, 1), 
		glm::vec3(-5.45, 0.05f, 2.53),
		glm::vec3(- 3.51, 0.05f, 2.47), 
		glm::vec3(-2.05, 0.05f, 1.61), 
		glm::vec3(0.75, 0.05f, 1.71), 
		glm::vec3(2.41, 0.05f, 2.77), 
		glm::vec3(3.91, 0.05f, 2.69), 
		glm::vec3(4.91, 0.05f, 1.39), 
		glm::vec3(4.53, 0.05f, -1),
		glm::vec3(3.23, 0.05f, -1.93), 
		glm::vec3(1.39, 0.05f, -1.79), 
		glm::vec3(- 1, 0.05f, -1), 
		glm::vec3(-3.09, 0.05f, -1.85), 
		glm::vec3(- 5.27, 0.05f, -1.63), 
		glm::vec3(- 7, 0.05f, -1)
	};
	std::vector<VertexFormat> vertices ;
	for(int i=0 ;i < 14; i++){
		vertices.push_back(VertexFormat( punctsus(punctemij[i],punctemij[i+1],1), color));
		vertices.push_back(VertexFormat( punctjos(punctemij[i],punctemij[i+1],1), color));
	}
	vertices.push_back(VertexFormat( punctsus(punctemij[14],punctemij[0],1), color));
	vertices.push_back(VertexFormat( punctjos(punctemij[14],punctemij[0],1), color));

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices =
        {
            0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,0,1

        };
	rectangle->SetDrawMode(GL_TRIANGLE_STRIP);


	rectangle->InitFromData(vertices, indices);
	return rectangle;
}
Mesh* object3D::CreateLap1(const std::string &name,std::vector<glm::vec3>punctesus,std::vector<glm::vec3>punctejos, glm::vec3 color){

	std::vector<VertexFormat> vertices ;
	for(int i=0 ;i < 15; i++){
		vertices.push_back(VertexFormat( punctesus[i], color));
		vertices.push_back(VertexFormat( punctejos[i], color));
	}


	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices =
        {
            0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,0,1

        };
	rectangle->SetDrawMode(GL_TRIANGLE_STRIP);


	rectangle->InitFromData(vertices, indices);
	return rectangle;
}
Mesh* object3D::CreateLine(const std::string &name, glm::vec3 color){

	std::vector<VertexFormat> vertices =
	{
		VertexFormat( glm::vec3( -7, 0.05f, 1),  color),
		VertexFormat( glm::vec3( -5.45, 0.05f, 2.53), color),
		VertexFormat( glm::vec3( -3.51, 0.05f, 2.47), color),
		VertexFormat( glm::vec3( -2.05, 0.05f, 1.61), color),
		VertexFormat( glm::vec3( 0.75, 0.05f, 1.71), color),
		VertexFormat( glm::vec3( 2.41, 0.05f, 2.77),  color),
		VertexFormat( glm::vec3( 3.91, 0.05f, 2.69),  color),
		VertexFormat( glm::vec3( 4.91, 0.05f, 1.39), color),
		VertexFormat( glm::vec3( 4.53, 0.05f, -1), color),
		VertexFormat( glm::vec3( 3.23, 0.05f, -1.93), color),
		VertexFormat( glm::vec3( 1.39, 0.05f, -1.79), color),
		VertexFormat( glm::vec3( -1, 0.05f, -1), color),
		VertexFormat( glm::vec3( -3.09, 0.05f, -1.85), color),
		VertexFormat( glm::vec3( -5.27, 0.05f, -1.63),  color),
		VertexFormat( glm::vec3( -7, 0.05f, -1) , color)
	};
	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices =
        {
            0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,0
			//0,1,2,3,4,5,6,7,0
        };
	rectangle->SetDrawMode(GL_LINE_STRIP);


	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

float object3D::unghivectori(glm::vec3 A1, glm::vec3 A2,glm::vec3 B1 ,glm::vec3 B2){
	glm::vec3 A;
	glm::vec3 B;
	A = A2 - A1;
	B = B2 - B1;
	float modA,modB;
	float prodscalar;
	float alph;

	modA = sqrt(A.x * A.x + A.z * A.z);
	modB = sqrt(B.x * B.x + B.z * B.z);

	prodscalar = A.x * B.x + A.z * B.z;
	
	alph = acos (prodscalar / (modA * modB));

	if(A2.z < 0 || A1.z < 0){

		return 3.14 - alph;
	}
	return alph;

}
std::vector<glm::vec3> object3D::impartetraseupuncte(std::vector<glm::vec3> traseunpc,int densitatepct,int nrpct){
	std::vector<glm::vec3> vecnpc;
	glm::vec3 ajutori,ajutorj;
	for(int i = 0; i < nrpct - 1; i++){
		ajutori.x = (traseunpc[i+1].x - traseunpc[i].x)/densitatepct;
		ajutori.z = (traseunpc[i+1].z - traseunpc[i].z)/densitatepct;
		for(int j = 0; j < densitatepct; j++){
			ajutorj.x = traseunpc[i].x + j * ajutori.x;
			ajutorj.y = 0;
			ajutorj.z = traseunpc[i].z + j * ajutori.z;
			vecnpc.push_back(ajutorj);
		}
	}
	ajutori.x = (traseunpc[0].x - traseunpc[nrpct-1].x)/densitatepct;
	ajutori.z = (traseunpc[0].z - traseunpc[nrpct-1].z)/densitatepct;
	for(int j = 0; j < densitatepct; j++){
		ajutorj.x = traseunpc[nrpct-1].x + j * ajutori.x;
		ajutorj.y = 0.05;
		ajutorj.z = traseunpc[nrpct-1].z + j * ajutori.z;
		vecnpc.push_back(ajutorj);
	}
	return vecnpc;

}
std::vector<float> object3D::unghiurinpc(std::vector<glm::vec3> traseunpc,int nrpct){
	float ajutor;
	std::vector<float> unghiuri;
	for(int i = 0; i < nrpct-1; i++){
		//verificare glm
		ajutor = unghivectori(traseunpc[i],traseunpc[i+1],glm::vec3(0,0,0),glm::vec3(0,0,1));
		unghiuri.push_back(ajutor);
	}
	ajutor = unghivectori(traseunpc[nrpct-1],traseunpc[0],glm::vec3(0,0,0),glm::vec3(0,0,1));
	unghiuri.push_back(ajutor);

	return unghiuri;
}

Mesh* object3D::CreatetrTree(const std::string &name, glm::vec3 center, float height, float width ,float depth ,glm::vec3 colortrunchi,glm::vec3 colorsus) {


	std::vector<VertexFormat> vertices =
	{ 	//truunchi
		VertexFormat(center + glm::vec3(- width / 2, -height / 2, depth / 2), colortrunchi),
		VertexFormat(center + glm::vec3(width / 2, -height / 2, depth / 2), colortrunchi),
		VertexFormat(center + glm::vec3(-width / 2, height / 2, depth / 2), colortrunchi),
		VertexFormat(center + glm::vec3(width / 2, height / 2, depth / 2), colortrunchi),
		VertexFormat(center + glm::vec3(- width / 2, -height / 2, -depth / 2), colortrunchi),
		VertexFormat(center + glm::vec3(width / 2, -height / 2, -depth / 2), colortrunchi),
		VertexFormat(center + glm::vec3(-width / 2, height / 2, -depth / 2), colortrunchi),
		VertexFormat(center + glm::vec3(width / 2, height / 2, -depth / 2), colortrunchi),

		//partesus copac
		VertexFormat(center + glm::vec3(- width / 2 - 0.2, height / 2, depth / 2  + 0.2), colorsus),
		VertexFormat(center + glm::vec3(width / 2 + 0.2, height / 2, depth / 2  + 0.2), colorsus),
		VertexFormat(center + glm::vec3(-width / 2 - 0.2, height / 2 + 0.4, depth / 2 + 0.2), colorsus),
		VertexFormat(center + glm::vec3(width / 2 + 0.2, height / 2 + 0.4, depth / 2 + 0.2), colorsus),
		VertexFormat(center + glm::vec3(- width / 2 - 0.2, height / 2, -depth / 2 - 0.2), colorsus),
		VertexFormat(center + glm::vec3(width / 2 + 0.2, height / 2, -depth / 2 - 0.2), colorsus),
		VertexFormat(center + glm::vec3(-width / 2 - 0.2, height / 2 + 0.4, -depth / 2 - 0.2), colorsus),
		VertexFormat(center + glm::vec3(width / 2 + 0.2, height / 2 + 0.4, -depth / 2 - 0.2), colorsus),



	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices =
        {
            0, 1, 2,   
            1, 3, 2,

            2, 3, 7,
            2, 7, 6,

            1, 7, 3,
            1, 5, 7,

            6, 7, 4, 
            7, 5, 4,

            0, 4, 1,
            1, 4, 5,

            2, 6, 4,
            0, 2, 4,

			//parte sus
			8, 9, 10,   
            9, 11, 10,

            10, 11, 15,
            10, 15, 14,

            9, 15, 11,
            9, 13, 15,

            14, 15, 12, 
            15, 13, 12,

            8, 12, 9,
            9, 12, 13,

            10, 14, 12,
            8, 10, 12,




        };



	rectangle->InitFromData(vertices, indices);
	return rectangle;
}
Mesh* object3D::CreateLap2(const std::string &name,std::vector<glm::vec3>punctesus,std::vector<glm::vec3>punctejos,int densitatepct,int nrpct,glm::vec3 color){

	std::vector<VertexFormat> vertices ;
	int i;
	glm::vec3 ajutorisus,ajutorjsus;
	glm::vec3 ajutorijos,ajutorjjos;
	for(int i = 0; i < nrpct; i++){
		//puuncte sus
		ajutorisus.x = (punctesus[(i + 1) % nrpct].x - punctesus[i].x)/densitatepct;
		ajutorisus.z = (punctesus[(i + 1) % nrpct].z - punctesus[i].z)/densitatepct;

		//puncte jos
		ajutorijos.x = (punctejos[(i + 1) % nrpct].x - punctejos[i].x)/densitatepct;
		ajutorijos.z = (punctejos[(i + 1) % nrpct].z - punctejos[i].z)/densitatepct;
		for(int j = 0; j < densitatepct; j++){
			//puncte sus
			ajutorjsus.x = punctesus[i].x + j * ajutorisus.x;
			ajutorjsus.y = 0.05f;
			ajutorjsus.z = punctesus[i].z + j * ajutorisus.z;

			vertices.push_back(VertexFormat( ajutorjsus, color));

			//puncte jos
			ajutorjjos.x = punctejos[i].x + j * ajutorijos.x;
			ajutorjjos.y = 0.05f;
			ajutorjjos.z = punctejos[i].z + j * ajutorijos.z;

			vertices.push_back(VertexFormat( ajutorjjos, color));

		}
	}


	Mesh* rectangle = new Mesh(name);

	std::vector<unsigned int> indices ;
	for(i = 0;i < densitatepct * nrpct * 2; i++){
		indices.push_back(i);
	}
	indices.push_back(0);
	indices.push_back(1);

	rectangle->SetDrawMode(GL_TRIANGLE_STRIP);


	rectangle->InitFromData(vertices, indices);
	return rectangle;
}


int object3D::bummasina(glm::vec3 masina1,glm::vec3 masina2){

	if(masina1.x - masina2.x  < 0.3f && masina1.x - masina2.x  > -0.3f){
		if(masina1.z - masina2.z  < 0.3f && masina1.z - masina2.z  > -0.3f){
			return 1;
		
		}

	}
	return 0;

}

