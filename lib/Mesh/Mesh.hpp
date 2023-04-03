/*
** EPITECH PROJECT, 2023
** opengl
** File description:
** Mesh
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <Shader.hpp>
#include <Window.hpp>
#include <Texture.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>
#include <array>

class Mesh {
    public:
        Mesh(std::string pathOBJ, std::string PathShader, std::string PathTexture);
        ~Mesh();

        void draw() const;
        static std::tuple<std::vector<GLfloat>, std::vector<GLfloat>> loadObj(const std::string path);

        void translate(glm::vec3 vec);
        void rotate(glm::vec3 vec);
        void setPosition(glm::vec3 vec);

        glm::vec3 getPosition() const { return _position; };

        static std::tuple<std::vector<GLfloat>, std::vector<GLfloat>> inteliLoaderObj(std::string name);

    protected:
    private:
        static std::map<std::string, std::tuple<std::vector<GLfloat>, std::vector<GLfloat>>> _inteliLoaderObj;

        std::shared_ptr<Shader> shader = nullptr;
        std::shared_ptr<Texture> texture = nullptr;
        GLuint _Texture = -1;
        GLuint _meshbuffer;
        GLuint _uvbuffer;
        GLuint _colorbuffer;

        std::vector<GLfloat> _buffer;
        std::vector<GLfloat> _bufferUV;

        glm::vec3 _position = glm::vec3(0, 0, 0);
        glm::vec3 _translation = glm::vec3(0, 0, 0);

        glm::mat4 _model = glm::mat4(1.0f);

        void generateColor(size_t size);
        std::vector<GLfloat> _buffer_color = {};
};
