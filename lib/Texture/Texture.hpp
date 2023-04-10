/*
** EPITECH PROJECT, 2023
** opengl
** File description:
** Texture
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <stb_image.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>

class Texture {

	public:
		Texture(const std::string& path);
		~Texture();
		void bind() const;
		void unbind() const;
		GLuint getID() const { return _texture; };
		int getWidth() const { return _width; };
		int getHeight() const { return _height; };
		int getChannels() const { return _nrChannels; };
		static std::tuple<GLuint, int, int, int> load(const char * imagepath);

		static std::tuple<GLuint, int, int, int> inteligiLoad(const std::string& path);
	protected:
	private:
		static std::map<std::string, std::tuple<GLuint, int, int, int>> _texturesInteligi;
		GLuint _texture;
		int _width;
		int _height;
		int _nrChannels;
		unsigned char *_data;
};;