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
    protected:
    private:
        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint vbo_uv = 0;

        std::vector<GLfloat> vertices = {};
        std::vector<GLfloat> verticesUV = {};
};