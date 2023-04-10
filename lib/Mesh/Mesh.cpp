/*
** EPITECH PROJECT, 2023
** opengl
** File description:
** Mesh
*/

#include "Mesh.hpp"
constexpr auto DEBUG_OBJ = false;

std::map<std::string, std::tuple<std::vector<GLfloat>, std::vector<GLfloat>>> Mesh::_inteliLoaderObj = {};

Mesh::Mesh(std::string pathOBJ, std::string PathShader, std::string PathTexture)
{
    //shader = std::make_shared<Shader>(PathShader);
    //shader->getTexture("myTextureSampler");
    _texture = std::make_shared<Texture>(PathTexture);
    auto load = inteliLoaderObj(pathOBJ);
    _buffer = std::get<0>(load);
    _bufferUV = std::get<1>(load);
    glGenBuffers(1, &_meshbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glBufferData(GL_ARRAY_BUFFER, _buffer.size() * sizeof(GLfloat), _buffer.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &_uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, _bufferUV.size() * sizeof(GLfloat), _bufferUV.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
}

Mesh::Mesh(const Mesh& other)
{

    _buffer = other._buffer;
	_bufferUV = other._bufferUV;
	glGenBuffers(1, &_meshbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
	glBufferData(GL_ARRAY_BUFFER, _buffer.size() * sizeof(GLfloat), _buffer.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, _bufferUV.size() * sizeof(GLfloat), _bufferUV.data(), GL_STATIC_DRAW);
	//shader->getTexture("myTextureSampler");
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &_meshbuffer);
    glDeleteBuffers(1, &_uvbuffer);
}

static bool _loadOBJ (const char * path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs,std::vector<glm::vec3> &out_normals)
{
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tmp_vertices; 
	std::vector<glm::vec2> tmp_uvs;
	std::vector<glm::vec3> tmp_normals;

    std::ifstream file(path);
	if( file.is_open() == false) {
        throw std::runtime_error("RuruEngine : can't load obj file");
	}

	while (1) {

        std::string line;
        if (!std::getline(file, line))
			break;
		std::istringstream iss(line);
		std::string trash;
		if (!(iss >> trash))
            continue;
        if (trash == "v") {
            glm::vec3 vertex{};
            iss >> vertex.x >> vertex.y >> vertex.z;
			tmp_vertices.push_back(vertex);
        } else if (trash == "vt") {
            glm::vec2 uv{};
            iss >> uv.x >> uv.y;
            uv.y = -uv.y;
            tmp_uvs.push_back(uv);
        } else if (trash == "vn") {
            glm::vec3 normal{};
            iss >> normal.x >> normal.y >> normal.z;
            tmp_normals.push_back(normal);
        } else if (trash == "f") {
            unsigned int vertexIndex[3] = {0}, uvIndex[3] = {0}, normalIndex[3] = {0};
            char trash = '0';
            for (int i = 0; i < 3; i++) {
                iss >> vertexIndex[i] >> trash >> uvIndex[i] >> trash >> normalIndex[i];
			    vertexIndices.push_back(vertexIndex[i]);
			    uvIndices.push_back(uvIndex[i]);
			    normalIndices.push_back(normalIndex[i]);
            }
        }
	}

	for( unsigned int i=0; i<vertexIndices.size(); i++ ){
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
        glm::vec3 vertex = tmp_vertices[static_cast<std::vector<glm::vec3, std::allocator<glm::vec3>>::size_type>(vertexIndex) - 1];
        glm::vec2 uv = tmp_uvs[static_cast<std::vector<glm::vec2, std::allocator<glm::vec2>>::size_type>(uvIndex) - 1];
        glm::vec3 normal = tmp_normals[static_cast<std::vector<glm::vec3, std::allocator<glm::vec3>>::size_type>(normalIndex) - 1];
		
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals .push_back(normal);
	}
	return true;
}

std::tuple<std::vector<GLfloat>, std::vector<GLfloat>> Mesh::loadObj(const std::string path)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    std::vector<GLfloat> buffer, bufferUV = {};

    _loadOBJ(path.c_str(), vertices, uvs, normals);

    for (int i = 0; i < vertices.size(); i++) {
        buffer.push_back(vertices[i].x);
        buffer.push_back(vertices[i].y);
        buffer.push_back(vertices[i].z);
    }

    for (int i = 0; i < uvs.size(); i++) {
        bufferUV.push_back(uvs[i].x);
        bufferUV.push_back(uvs[i].y);
	}

    return std::make_tuple(buffer, bufferUV);
}

void Mesh::generateColor(size_t size)
{
    _buffer_color.clear();
    for (int i = 0; i < size; i++) {
        float r = (float)rand() / (float)RAND_MAX;
        float g = (float)rand() / (float)RAND_MAX;
        float b = (float)rand() / (float)RAND_MAX;
        _buffer_color.push_back(r);
        _buffer_color.push_back(g);
        _buffer_color.push_back(b);
    }
    glGenBuffers(1, &_colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, _buffer_color.size() * sizeof(GLfloat), _buffer_color.data(), GL_STATIC_DRAW);
}

void Mesh::draw() const
{
    //shader->/*use();
    //shader->setMVP(Window::getCamera()->getMVP());
    //shader->setTexture(0);*/

    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_buffer.size()));
}

void Mesh::translate(glm::vec3 vec)
{
    for (int i = 0; i < _buffer.size(); i += 3) {
        _buffer[i] += vec.x;
        _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 1] += vec.y;
        _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 2] += vec.z;
    }
    _position += vec;

    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glBufferData(GL_ARRAY_BUFFER, _buffer.size() * sizeof(GLfloat), _buffer.data(), GL_STATIC_DRAW);
}

void Mesh::rotate(glm::vec3 vec)
{
    glm::mat4 rot = glm::mat4(1.0f);
    glm::vec3 pos = glm::vec3(0.0f);

    for (int i = 0; i < _buffer.size(); i += 3) {
        pos.x += _buffer[i];
        pos.y += _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 1];
        pos.z += _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 2];
    }

    pos.x /= _buffer.size() / static_cast<float>(3);
    pos.y /= _buffer.size() / static_cast<float>(3);
    pos.z /= _buffer.size() / static_cast<float>(3);

    rot = glm::rotate(rot, glm::radians(vec.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rot = glm::rotate(rot, glm::radians(vec.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rot = glm::rotate(rot, glm::radians(vec.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 new_pos = glm::vec3(0.0f);
    for (int i = 0; i < _buffer.size(); i += 3) {
        glm::vec4 tmp = rot * glm::vec4(_buffer[i] - pos.x, _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 1] - pos.y, _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + + 2] - pos.z, 1.0f);
        _buffer[i] = tmp.x + pos.x;
        _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 1] = tmp.y + pos.y;
        _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 2] = tmp.z + pos.z;
        new_pos.x += _buffer[i];
        new_pos.y += _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 1];
        new_pos.z += _buffer[static_cast<std::vector<GLfloat, std::allocator<GLfloat>>::size_type>(i) + 2];
    }

    new_pos.x /= _buffer.size() / static_cast<float>(3);
    new_pos.y /= _buffer.size() / static_cast<float>(3);
    new_pos.z /= _buffer.size() / static_cast<float>(3);

    glm::vec3 diff = pos - new_pos;
    std::cout << "pos: " << pos.x << " " << pos.y << " " << pos.z << std::endl;

    glDeleteBuffers(1, &_meshbuffer);
    glGenBuffers(1, &_meshbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glBufferData(GL_ARRAY_BUFFER, _buffer.size() * sizeof(GLfloat), _buffer.data(), GL_STATIC_DRAW);
}

void Mesh::setPosition(glm::vec3 vec)
{
    glm::vec3 diff = vec - _position;
	translate(diff);
}

std::tuple<std::vector<GLfloat>, std::vector<GLfloat>> Mesh::inteliLoaderObj(std::string path)
{
    if (_inteliLoaderObj.find(path) != _inteliLoaderObj.end()) {
        if (DEBUG_OBJ)
            std::cout << "OBJ: " << path << " already loaded" << std::endl;
        return _inteliLoaderObj[path];
    }
    else {
        _inteliLoaderObj[path] = loadObj(path);
        if (DEBUG_OBJ)
            std::cout << "OBJ: " << path << " loaded" << std::endl;
        return _inteliLoaderObj[path];
    }
}
