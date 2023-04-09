#include "Cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

std::vector<GLfloat> Cube::getVertices() const
{
	std::vector<GLfloat> vertices;
	int i = 0;
	for (auto &face : _faces) {
		if (_facesDraw[i] == false) {
			i += 1;
			continue;
		}
		std::vector<GLfloat> tmp = face;
		for (int i = 0; i < tmp.size(); i += 3) {
			glm::vec4 vertex = glm::vec4(tmp[i], tmp[i + 1], tmp[i + 2], 1.0f);
			vertex = _model * vertex;
			tmp[i] = vertex.x;
			tmp[i + 1] = vertex.y;
			tmp[i + 2] = vertex.z;
		}
		vertices.insert(vertices.end(), tmp.begin(), tmp.end());
		i += 1;
	}

	return vertices;
}

void Cube::calculateDraw(const Cube &other)
{
	glm::vec3 pos = glm::vec3(_model[3]);
	glm::vec3 otherPos = glm::vec3(other._model[3]);
	glm::vec3 diff = pos - otherPos;
	for (int i = 0; i < 6; i += 1)
		_facesDraw[i] = true;
	if (diff.x == 1.0f && diff.y == 0.0f && diff.z == 0.0f)
		_facesDraw[2] = false;
	else if (diff.x == -1.0f && diff.y == 0.0f && diff.z == 0.0f)
		_facesDraw[4] = false;
	if (diff.x == 0.0f && diff.y == 1.0f && diff.z == 0.0f)
		_facesDraw[3] = false;
	else if (diff.x == 0.0f && diff.y == -1.0f && diff.z == 0.0f)
		_facesDraw[0] = false;
	if (diff.x == 0.0f && diff.y == 0.0f && diff.z == 1.0f)
		_facesDraw[5] = false;
	else if (diff.x == 0.0f && diff.y == 0.0f && diff.z == -1.0f)
		_facesDraw[1] = false;
}
