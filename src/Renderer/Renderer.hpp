/*
** EPITECH PROJECT, 2023
** tuto6
** File description:
** Window
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <memory>

#include <Mesh.hpp>

class Renderer {
public:
	Renderer(const std::vector<std::shared_ptr<Mesh>> meshs);
	~Renderer();

	void draw() const;
protected:
private:
	GLuint _meshbuffer = -1;
	GLuint _uvbuffer = -1;

	std::vector<GLfloat> _buffer;
	std::vector<GLfloat> _bufferUV;
};
