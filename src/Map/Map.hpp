/*
** EPITECH PROJECT, 2023
** openGLminecraft
** File description:
** Map
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

#include <Shader.hpp>
#include "Window.hpp"
#include "Mesh.hpp"
#include "Cube/Cube.h"
#include "Renderer/Renderer.h"

typedef int uint;

static std::map<uint, std::string>  _CUBE_TEXTURE = {
    {0, "dirt.jpg"},
    {1, "rock.jpg"},
    {2, "grass.jpg"},
};

class Map {
    public:
        Map(int x, int y, int z);
        ~Map();

        void draw(void);
        void reloadCollision();
        void reloadCollision(int x, int y, int z);
        std::shared_ptr<Cube> getCube(int x, int y, int z) const {
            if (x < 0 || y < 0 || z < 0 || x >= _sizex || z >= _sizez)
				return (nullptr);
            auto &cube = _cubes[x][z];
            int size = cube.size();
            if (size <= y)
                return (nullptr);
            return (_cubes[x][z][y]);
        }
        bool removeCube(const std::shared_ptr<Cube>& cube);

    protected:
    private:
        int _sizex;
        int _sizey;
        int _sizez;

        std::vector<std::vector<std::vector<std::shared_ptr<Cube>>>> _cubes;
        std::vector<std::shared_ptr<Cube>> _allcubes;

        std::map<int, std::shared_ptr<Texture>> _texture;
        std::map<int, std::shared_ptr<Shader>> _shader;
        std::map<int, Renderer> _renderer;
        Renderer _tmpRenderer;
        std::shared_ptr<Shader> _tmpShader;
        std::shared_ptr<Texture> _tmpTexture;
};
