#include "Cube.h"

Cube::Cube()
{
    std::vector<GLfloat> upperTexCoords = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };
    std::vector<GLfloat> frontTexCoords = {
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f
    };
    std::vector<GLfloat> leftTexCoords = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };
    std::vector<GLfloat> bottomTexCoords = {
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
    std::vector<GLfloat> rightTexCoords = {
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f
    };
    std::vector<GLfloat> backTexCoords = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f
    };
    _uv[0] = upperTexCoords;
    _uv[1] = frontTexCoords;
    _uv[2] = leftTexCoords;
    _uv[3] = bottomTexCoords;
    _uv[4] = rightTexCoords;
    _uv[5] = backTexCoords;
}

Cube::~Cube()
{
}

std::vector<GLfloat> Cube::getVerticesUV() const
{
    std::vector<GLfloat> verticesUV = {};
    int i = 0;
    for (auto &face : _faces) {
        if (_facesDraw[i] == false) {
            i += 1;
            continue;
        }
        std::vector<GLfloat> tmp = _uv[i];
        for (int i = 0; i < tmp.size(); i += 2) {
            glm::vec4 vertex = glm::vec4(tmp[i], tmp[i + 1], 0.0f, 1.0f);
            vertex = _model * vertex;
            tmp[i] = vertex.x;
            tmp[i + 1] = vertex.y;
        }
        verticesUV.insert(verticesUV.end(), tmp.begin(), tmp.end());
        i += 1;
    }
    return verticesUV;
}

std::vector<GLfloat> Cube::getVertices() const
{
    std::vector<GLfloat> vertices = {};
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
