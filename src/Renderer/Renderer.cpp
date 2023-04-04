#include "Renderer.hpp"

Renderer::Renderer(const std::vector<std::shared_ptr<Mesh>> meshs)
{
	for (auto& mesh : meshs) {
		_buffer.insert(_buffer.end(), mesh->_buffer.begin(), mesh->_buffer.end());
		_bufferUV.insert(_bufferUV.end(), mesh->_bufferUV.begin(), mesh->_bufferUV.end());
	}
	glGenBuffers(1, &_meshbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
	glBufferData(GL_ARRAY_BUFFER, _buffer.size() * sizeof(GLfloat), &_buffer[0], GL_STATIC_DRAW);
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, _bufferUV.size() * sizeof(GLfloat), &_bufferUV[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

Renderer::~Renderer()
{
}

void Renderer::draw() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, _buffer.size() / 3);
}