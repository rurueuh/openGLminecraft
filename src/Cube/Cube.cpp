#include "Cube.h"

std::vector<GLfloat> Cube::_upper = {
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
};
std::vector<GLfloat> Cube::_front = {
    0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
};
std::vector<GLfloat> Cube::_left = {
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
};
std::vector<GLfloat> Cube::_bottom = {
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
};
std::vector<GLfloat> Cube::_right = {
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
};
std::vector<GLfloat> Cube::_back = {
    -0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
};

std::vector<GLfloat> Cube::_upperUV = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
};

std::vector<GLfloat> Cube::_frontUV = {
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f
};

std::vector<GLfloat> Cube::_leftUV = {
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

std::vector<GLfloat> Cube::_bottomUV = {
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
};

std::vector<GLfloat> Cube::_rightUV = {
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f
};
std::vector<GLfloat> Cube::_backUV = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f
};

Cube::Cube()
{
}

Cube::~Cube()
{
}

std::vector<GLfloat> Cube::getVerticesUV() const
{
    std::vector<GLfloat> verticesUV = {};
    int i = 0;
    for (; i < 6; i += 1) {
        if (_facesDraw[i] == false) {
            continue;
        }
        std::vector<GLfloat> tmp = {};
        if (i == 0)
            tmp = Cube::_upperUV;
        if (i == 1)
            tmp = Cube::_frontUV;
        if (i == 2)
            tmp = Cube::_leftUV;
        if (i == 3)
            tmp = Cube::_bottomUV;
        if (i == 4)
            tmp = Cube::_rightUV;
        if (i == 5)
            tmp = Cube::_backUV;
        for (int i = 0; i < tmp.size(); i += 2) {
            glm::vec4 vertex = glm::vec4(tmp[i], tmp[i + 1], 0.0f, 1.0f);
            vertex = _model * vertex;
            tmp[i] = vertex.x;
            tmp[i + 1] = vertex.y;
        }
        verticesUV.insert(verticesUV.end(), tmp.begin(), tmp.end());
    }
    return verticesUV;
}

std::vector<GLfloat> Cube::getVertices() const
{
    std::vector<GLfloat> vertices = {};
    int i = 0;
    for (; i < 6; i += 1) {
        if (_facesDraw[i] == false) {
            continue;
        }
        std::vector<GLfloat> tmp = {};
        if (i == 0)
            tmp = Cube::_upper;
        if (i == 1)
            tmp = Cube::_front;
        if (i == 2)
            tmp = Cube::_left;
        if (i == 3)
            tmp = Cube::_bottom;
        if (i == 4)
            tmp = Cube::_right;
        if (i == 5)
            tmp = Cube::_back;
        for (int d = 0; d < tmp.size(); d += 3) {
            glm::vec4 vertex = glm::vec4(tmp[d], tmp[d + 1], tmp[d + 2], 1.0f);
            vertex = _model * vertex;
            tmp[d] = vertex.x;
            tmp[d + 1] = vertex.y;
            tmp[d + 2] = vertex.z;
        }
        vertices.insert(vertices.end(), tmp.begin(), tmp.end());
    }
    return vertices;
}

void Cube::resetDraw()
{
    for (int i = 0; i < 6; i += 1)
        _facesDraw[i] = true;
}

void Cube::calculateDraw(const std::shared_ptr<Cube> &other)
{
    glm::vec3 pos = glm::vec3(_model[3]);
    glm::vec3 otherPos = glm::vec3(other->_model[3]);
    glm::vec3 diff = pos - otherPos;
    if (diff.x == 1.0f && diff.y == 0.0f && diff.z == 0.0f && _facesDraw[2] == true)
        _facesDraw[2] = false;
    else if (diff.x == -1.0f && diff.y == 0.0f && diff.z == 0.0f && _facesDraw[4] == true)
        _facesDraw[4] = false;
    if (diff.x == 0.0f && diff.y == 1.0f && diff.z == 0.0f && _facesDraw[3] == true)
        _facesDraw[3] = false;
    else if (diff.x == 0.0f && diff.y == -1.0f && diff.z == 0.0f && _facesDraw[0] == true)
        _facesDraw[0] = false;
    if (diff.x == 0.0f && diff.y == 0.0f && diff.z == 1.0f && _facesDraw[5] == true)
        _facesDraw[5] = false;
    else if (diff.x == 0.0f && diff.y == 0.0f && diff.z == -1.0f && _facesDraw[1] == true)
        _facesDraw[1] = false;
}
