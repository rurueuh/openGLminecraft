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
                std::shared_ptr<Cube> cube = std::make_shared<Cube>(0);
                cube->setPos(glm::vec3(x, y, z));
                cubesZ.push_back(cube);
                _allcubes.push_back(cube);
            }
            cubesX.push_back(cubesZ);
        }
        _cubes.push_back(cubesX);
    }

    // for (int y = 0; y < _sizey; y++) {
    //     std::vector<std::vector<std::shared_ptr<Cube>>> cubesY = std::vector<std::vector<std::shared_ptr<Cube>>>();
    //     for (int x = 0; x < _sizex; x++) {
    //         std::vector<std::shared_ptr<Cube>> cubesX = std::vector<std::shared_ptr<Cube>>();
    //         for (int z = 0; z < _sizey; z++) {
    //             std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    //             cube->setPos(glm::vec3(x, y, z));
    //             cubesX.push_back(cube);
    //             _allcubes.push_back(cube);
    //         }
    //         cubesY.push_back(cubesX);
    //     }
    //     _cubes.push_back(cubesY);
    // }

    reloadCollision();
    _renderer.calculateDraw(_allcubes);

    const std::string PATH = "../assets/";
    _shader = std::make_shared<Shader>(PATH + "shader");
    _texture = std::make_shared<Texture>(PATH + "dirt.jpg");
    _texture->bind();
    _shader->use();
    _shader->setTexture(0);
}

Map::~Map()
{
}

void Map::reloadCollision()
{

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
    _renderer.calculateDraw(_allcubes);
}

void Map::draw()
{
    _shader->setMVP(Window::getCamera()->getMVP());
    _shader->use();
    _renderer.render();
}
