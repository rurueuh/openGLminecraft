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

/*
* important de cherche une optimisation en cas de doublons de shader genre si le fichier est charger de le garde load et je dupplique pas
**/

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
	protected:
	private:
		GLuint _programID = -1;
		GLuint _matrixID = -1;
		GLuint _textureID = -1;
};
