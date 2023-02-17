#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
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
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length / 2, length,0),color),
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2};

	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}
	/*else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}*/

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));
	float nrvertex = 180.0;
	for (int i = 0; i <= nrvertex + 1; i++) {
		vertices.push_back(VertexFormat(glm::vec3(cos(i / nrvertex * 2 * 3.14), sin(i / nrvertex * 2 * 3.14), 0), color));
	}

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices;
	for (int i = 0; i <= nrvertex + 1; i++) {
		indices.push_back(0); indices.push_back(i + 1); indices.push_back(i);
	}

	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}