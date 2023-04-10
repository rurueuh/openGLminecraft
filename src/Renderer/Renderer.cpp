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
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, verticesUV.size() * sizeof(GLfloat), verticesUV.data(), GL_STATIC_DRAW);
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
