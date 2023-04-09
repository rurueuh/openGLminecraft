
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#define STB_IMAGE_IMPLEMENTATION

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

#include <Shader.hpp>
#include "Window.hpp"
#include "Mesh.hpp"
#include "Cube/Cube.h"

void WindowMoveCamera(Window& window, std::shared_ptr<Camera>& camera, const float& speed);
void WindowMouseMoveCamera(Window& window, std::shared_ptr<Camera>& camera);

void MoveCube(Window& window, bool& ispressed, Cube& cube, Cube& cube2);

void drawCube(std::vector<GLfloat>& vertex, Cube& cube, std::vector<GLfloat>& vertex2, Cube& cube2, const GLuint& vbo);
