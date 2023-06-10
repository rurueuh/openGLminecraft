/*
** EPITECH PROJECT, 2023
** openGLminecraft
** File description:
** Renderer
*/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <time.h>

#include "Cube.h"

class Renderer {
    public:
        Renderer();
        ~Renderer();
        void render();
        void calculateDraw(const std::vector<std::shared_ptr<Cube>> &cubes);
        void recalculateCube(const std::shared_ptr<Cube>& cube);
        void removeToBuffer(std::vector<GLfloat> verticesToRemove, std::vector<GLfloat> verticesUVToRemove);
        void calculate() {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
            glBufferData(GL_ARRAY_BUFFER, verticesUV.size() * sizeof(GLfloat), verticesUV.data(), GL_STATIC_DRAW);
        }
    protected:
    private:
        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint vbo_uv = 0;

        std::vector<GLfloat> vertices = {};
        std::vector<GLfloat> verticesUV = {};
};