/*
** EPITECH PROJECT, 2023
** openGLminecraft
** File description:
** Map
*/

#include "Map.hpp"
#include "PerlinNoise.hpp"

Map::Map(int sizex, int sizey, int sizez)
    : _sizex(sizex), _sizey(sizey), _sizez(sizez)
{
    const siv::PerlinNoise::seed_type seed = /*std::random_device{}()*/ 0;
	const siv::PerlinNoise perlin{ seed };
	for (int x = 0; x < _sizex; x++) {
        std::vector<std::vector<std::shared_ptr<Cube>>> cubesX = std::vector<std::vector<std::shared_ptr<Cube>>>();
        for (int z = 0; z < _sizez; z++) {
            std::vector<std::shared_ptr<Cube>> cubesZ = std::vector<std::shared_ptr<Cube>>();
			const double noise = perlin.octave2D_01((x * 0.003), (z * 0.003), 4);
            const int height = static_cast<int>(noise * _sizey);
            for (int y = 0; y < height; y++) {
                std::shared_ptr<Cube> cube = nullptr;
                if (y + 3 < height) {
                    cube = std::make_shared<Cube>(1);
                } else if (y + 1 == height) {
                    cube = std::make_shared<Cube>(2);
                } else {
                    cube = std::make_shared<Cube>(0);
                }
                cube->setPos(glm::vec3(x, y, z));
                cubesZ.push_back(cube);
                _allcubes.push_back(cube);
            }
            cubesX.push_back(cubesZ);
        }
        _cubes.push_back(cubesX);
    }

    reloadCollision();

    const std::string PATH = "../assets/";
    
    for (int i = 0; i < _CUBE_TEXTURE.size(); i++) {
        std::vector<std::shared_ptr<Cube>> cubes = std::vector<std::shared_ptr<Cube>>();
        for (auto cube : _allcubes) {
            int id = cube->getId();
            if (cube->getId() == i) {
                cubes.push_back(cube);
            }
        }
        _renderer[i].calculateDraw(cubes);
        _shader[i] = std::make_shared<Shader>(PATH + "shader");
        _texture[i] = std::make_shared<Texture>(PATH + _CUBE_TEXTURE[i]);
        _shader[i]->use();
        _shader[i]->setTexture(0);
    }

}

Map::~Map()
{
}

void Map::reloadCollision()
{
    for (auto& cube : _allcubes) {
        if (cube == nullptr)
            continue;
        for (int i = 0; i < 6; i++) {
            cube->_facesDraw[i] = true;
        }
    }
    for (int x = 0; x < _sizex; x++) {
        for (int z = 0; z < _sizez; z++) {
            for (int y = 0; y < _cubes[x][z].size(); y++) {
                std::shared_ptr<Cube> cube = _cubes[x][z][y];
                if (cube == nullptr) {
					continue;
                }
                std::shared_ptr<Cube> cubeUp = nullptr;
                std::shared_ptr<Cube> cubeDown = nullptr;
                std::shared_ptr<Cube> cubeLeft = nullptr;
                std::shared_ptr<Cube> cubeRight = nullptr;
                std::shared_ptr<Cube> cubeFront = nullptr;
                std::shared_ptr<Cube> cubeBack = nullptr;

                if (y + 1 < _cubes[x][z].size()) {
                    cubeUp = _cubes[x][z][y + 1];
                }
                if (y - 1 >= 0) {
                    cubeDown = _cubes[x][z][y - 1];
                }

                if (x - 1 >= 0) {
                    if (_cubes[x - 1][z].size() > y)
                        cubeLeft = _cubes[x - 1][z][y];
                }
                if (x + 1 < _sizex) {
                    if (_cubes[x + 1][z].size() > y)
                        cubeRight = _cubes[x + 1][z][y];
                }
                if (z - 1 >= 0) {
                    if (_cubes[x][z - 1].size() > y)
                        cubeFront = _cubes[x][z - 1][y];
                }
                if (z + 1 < _sizez) {
                    if (_cubes[x][z + 1].size() > y)
                        cubeBack = _cubes[x][z + 1][y];
                }
                if (cubeUp != nullptr)
                    cube->calculateDraw(cubeUp);
                if (cubeDown != nullptr)
                    cube->calculateDraw(cubeDown);
                if (cubeLeft != nullptr)
                    cube->calculateDraw(cubeLeft);
                if (cubeRight != nullptr)
                    cube->calculateDraw(cubeRight);
                if (cubeFront != nullptr)
                    cube->calculateDraw(cubeFront);
                if (cubeBack != nullptr)
                    cube->calculateDraw(cubeBack);
            }
		}
	}
    
    const std::string PATH = "../assets/";

    for (int i = 0; i < _CUBE_TEXTURE.size(); i++) {
        std::vector<std::shared_ptr<Cube>> cubes = std::vector<std::shared_ptr<Cube>>();
        for (auto cube : _allcubes) {
            if (cube == nullptr)
				continue;
            int id = cube->getId();
            if (cube->getId() == i) {
                cubes.push_back(cube);
            }
        }
        _renderer[i].calculateDraw(cubes);
        /*_shader[i] = std::make_shared<Shader>(PATH + "shader");
        _texture[i] = std::make_shared<Texture>(PATH + _CUBE_TEXTURE[i]);
        _shader[i]->use();
        _shader[i]->setTexture(0);*/
    }
}

static void reloadCollisione(const std::shared_ptr<Cube>& cube, std::map<int, Renderer> &_renderer)
{
    if (cube == nullptr)
		return;
    int rendererID = cube->getId();
    auto& renderer = _renderer[rendererID];

    renderer.recalculateCube(cube);
}

void Map::reloadCollision(int x, int y, int z)
{
    std::shared_ptr<Cube> cube = _cubes[x][z][y];
    std::shared_ptr<Cube> cubeUp = nullptr;
    std::shared_ptr<Cube> cubeDown = nullptr;
    std::shared_ptr<Cube> cubeLeft = nullptr;
    std::shared_ptr<Cube> cubeRight = nullptr;
    std::shared_ptr<Cube> cubeFront = nullptr;
    std::shared_ptr<Cube> cubeBack = nullptr;

    if (y + 1 < _cubes[x][z].size()) {
        cubeUp = _cubes[x][z][y + 1];
    }
    if (y - 1 >= 0) {
        cubeDown = _cubes[x][z][y - 1];
    }

    if (x - 1 >= 0) {
        if (_cubes[x - 1][z].size() > y)
            cubeLeft = _cubes[x - 1][z][y];
    }
    if (x + 1 < _sizex) {
        if (_cubes[x + 1][z].size() > y)
            cubeRight = _cubes[x + 1][z][y];
    }
    if (z - 1 >= 0) {
        if (_cubes[x][z - 1].size() > y)
            cubeFront = _cubes[x][z - 1][y];
    }
    if (z + 1 < _sizez) {
        if (_cubes[x][z + 1].size() > y)
            cubeBack = _cubes[x][z + 1][y];
    }
    // upper, front, left, bottom, right, back
    if (cubeUp != nullptr)
        cubeUp->_facesDraw[3] = true;
    if (cubeDown != nullptr)
        cubeDown->_facesDraw[0] = true;
    if (cubeLeft != nullptr)
        cubeLeft->_facesDraw[4] = true;
    if (cubeRight != nullptr)
        cubeRight->_facesDraw[2] = true;
    if (cubeFront != nullptr)
        cubeFront->_facesDraw[1] = true;
    if (cubeBack != nullptr)
        cubeBack->_facesDraw[5] = true;

    int rendererID = cube->getId();
    auto &renderer = _renderer[rendererID];

    for (int i = 0; i < _CUBE_TEXTURE.size(); i++) {
        std::vector<std::shared_ptr<Cube>> cubes = std::vector<std::shared_ptr<Cube>>();
        for (auto cube : _allcubes) {
            if (cube == nullptr)
                continue;
            int id = cube->getId();
            if (cube->getId() == i) {
                cubes.push_back(cube);
            }
        }
        _renderer[i].calculateDraw(cubes);
    }
}

bool Map::removeCube(const std::shared_ptr<Cube>& cube)
{
    for (auto& cube1 : _allcubes) {
        if (cube1 == cube) {
			cube1 = nullptr;
		}
	}
    for (int x = 0; x < _sizex; x++) {
        for (int z = 0; z < _sizez; z++) {
            for (int y = 0; y < _cubes[x][z].size(); y++) {
                if (_cubes[x][z][y] == cube) {
					reloadCollision(x, y, z);
					_cubes[x][z][y] = nullptr;
					return true;
				}
			}
		}
	}
    return false;
}

void Map::draw()
{
    const std::string PATH = "../assets/";
    for (int i = 0; i < _CUBE_TEXTURE.size(); i++) {
        _shader[i]->setMVP(Window::getCamera()->getMVP());
        _shader[i]->use();
        _texture[i]->bind();
        _renderer[i].render();
    }
}
