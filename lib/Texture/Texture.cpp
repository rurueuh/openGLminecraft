#include "Texture.hpp"
constexpr auto DEBUG_TEXTURE = false;

std::map<std::string, std::tuple<GLuint, int, int, int>> Texture::_texturesInteligi = {};
int Texture::_nbTextures = 0;

Texture::Texture(const std::string& path)
	: _texture(0), _width(0), _height(0), _nrChannels(0), _data(nullptr)
{
    std::tie(_texture, _width, _height, _nrChannels) = inteligiLoad(path);
    _idTexture = _nbTextures;
    _nbTextures++;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_texture);
}

void Texture::bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::tuple<GLuint, int, int, int> Texture::load(const char* imagepath) {

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(imagepath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::runtime_error("Failed to load texture");
    }
    stbi_image_free(data);
	return std::make_tuple(texture, width, height, nrChannels);
}

std::tuple<GLuint, int, int, int> Texture::inteligiLoad(const std::string& path)
{
    if (_texturesInteligi.find(path) != _texturesInteligi.end()) {
        if (DEBUG_TEXTURE) {
			std::cout << "Texture already loaded: " << path << std::endl;
        }
		return _texturesInteligi[path];
    } else {
        _texturesInteligi[path] = load(path.c_str());
        if (DEBUG_TEXTURE) {
            std::cout << "Texture loaded: " << path << std::endl;
        }
		return _texturesInteligi[path];
	}
}
