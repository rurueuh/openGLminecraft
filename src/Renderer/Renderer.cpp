/*
** EPITECH PROJECT, 2023
** openGLminecraft
** File description:
** Renderer
*/

#include "Renderer.h"

Renderer::Renderer()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &vbo_uv);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vbo_uv);
    glDeleteVertexArrays(1, &vao);
}

void Renderer::calculateDraw(const std::vector<std::shared_ptr<Cube>> &cubes)
{
    vertices.clear();
    verticesUV.clear();
    for (int i = 0; i < cubes.size(); i += 1) {
        if (cubes[i] == nullptr)
			continue;
        std::vector<GLfloat> tmp = cubes[i]->getVertices();
        std::vector<GLfloat> tmpUV = cubes[i]->getVerticesUV();
        vertices.insert(vertices.end(), tmp.begin(), tmp.end());
        verticesUV.insert(verticesUV.end(), tmpUV.begin(), tmpUV.end());
    }
    calculate();
}

void Renderer::removeCube(const std::shared_ptr<Cube>& cube)
{
    if (cube == nullptr)
        return;
    std::vector<GLfloat> tmp = cube->getVertices();
    std::vector<GLfloat> tmpUV = cube->getVerticesUV();
    removeToBuffer(tmp, tmpUV);
}

void Renderer::addCube(const std::shared_ptr<Cube>& cube)
{
    if (cube == nullptr)
		return;
    std::vector<GLfloat> tmp = cube->getVertices();
	std::vector<GLfloat> tmpUV = cube->getVerticesUV();
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	verticesUV.insert(verticesUV.end(), tmpUV.begin(), tmpUV.end());
}

void Renderer::removeToBuffer(const std::vector<GLfloat>& verticesToRemove, const std::vector<GLfloat>& verticesUVToRemove)
{
    if (verticesToRemove.empty() || verticesUVToRemove.empty())
        return;
    

    for (int i = 0; i < vertices.size(); i++) {
        bool found = true;
        int index = i;
        for (int j = 0; j < verticesToRemove.size(); j++, index++) {
            if (index >= vertices.size() || !(vertices[index] == verticesToRemove[j])) {
                found = false;
                break;
            }
        }
        if (found) {
			vertices.erase(vertices.begin() + i, vertices.begin() + i + verticesToRemove.size());
            i *= 2.f / 3.f;
            verticesUV.erase(verticesUV.begin() + i, verticesUV.begin() + i + verticesUVToRemove.size());
            break;
		}
    }
    calculate();
}

void Renderer::render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
