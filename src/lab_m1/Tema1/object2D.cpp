#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#define DEG2RAD 3.14159/180.0

Mesh* object2D::CreateS(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
Mesh* object2D::CreateHead(const std::string &name, glm::vec3 center, float radiusX, float radiusY, glm::vec3 color)
{
	int i;
	std::vector<VertexFormat> vertices;

	for (i = 0; i < 360; i++) {
		float rad = i * DEG2RAD;
		vertices.push_back(VertexFormat(center + glm::vec3(cos(rad) * radiusX, sin(rad) * radiusY, 0), color));
	}
	Mesh* head = new Mesh(name);
	
	std::vector<unsigned int> indices;
	for (i = 0; i < 360; i++) {
		indices.push_back(i);
	}
	head->SetDrawMode(GL_TRIANGLE_FAN);
	head->InitFromData(vertices, indices);
	return head;
}
Mesh* object2D::CreateTriangle(const std::string &name, glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 color)
{
	//    A
	// 	/	\
	// B-----C	
	int i;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(A, color),
		VertexFormat(B, color),
		VertexFormat(C, color),
	};
	Mesh* triangle = new Mesh(name);

	std::vector<unsigned int> indices = { 0, 1, 2 };

	triangle->SetDrawMode(GL_TRIANGLES);
	triangle->InitFromData(vertices, indices);
	return triangle;
}
Mesh* object2D::CreateRectangle(const std::string &name, glm::vec3 center, float height, float width, glm::vec3 color, bool fill) {


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(- width / 2, -height / 2, 0), color),
		VertexFormat(center + glm::vec3(-width / 2, height / 2, 0), color),
		VertexFormat(center + glm::vec3(width / 2, height / 2, 0), color),
		VertexFormat(center + glm::vec3(width / 2, -height / 2, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		//  Ase adauga ult 2 indici dupa ce s au desenat 2 triunghiuri
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}