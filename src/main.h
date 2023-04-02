
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

#include <Shader.hpp>
#include "Window.hpp"
#include "Mesh.hpp"

void WindowMoveCamera(Window& window, std::shared_ptr<Camera>& camera, float& speed);

void WindowMouseMoveCamera(Window& window, std::shared_ptr<Camera>& camera);