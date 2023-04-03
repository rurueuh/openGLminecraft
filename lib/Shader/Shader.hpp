/*
** EPITECH PROJECT, 2023
** opengl
** File description:
** Shader
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>

class Shader {
	public:
		Shader(const char* path);
		Shader(const std::string& path);
		~Shader();

		void getTexture(const std::string &name);
		void use() const;
		void setMVP(glm::mat4 matrix) const;
		void setTexture(int chan);

		static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
		static GLuint inteligiLoad(const std::string &path);
		static GLuint inteligiLoad(const char *path);
	protected:
	private:
		static std::map<std::string, GLuint> shadersInteligi;
		GLuint _programID = -1;
		GLuint _matrixID = -1;
		GLuint _textureID = -1;
};
