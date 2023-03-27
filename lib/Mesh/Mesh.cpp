/*
** EPITECH PROJECT, 2023
** opengl
** File description:
** Mesh
*/

#include "Mesh.hpp"

Mesh::Mesh()
{
    loadObj("../assets/Epitech.obj");

    glGenBuffers(1, &_colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, _buffer_color.size() * sizeof(GLfloat), _buffer_color.data(), GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &_meshbuffer);
    glDeleteBuffers(1, &_colorbuffer);
}

static void fixLine(std::istringstream &iss)
{
    // remove all 'f'
    std::string line;
    std::getline(iss, line);
    line.erase(std::remove(line.begin(), line.end(), 'f'), line.end());
    line.erase(std::remove(line.begin(), line.end(), 'F'), line.end());

    // replace all ',' by ' '
    std::replace(line.begin(), line.end(), ',', ' ');
    iss.str(line);
    iss.clear();
}

static bool _loadOBJ (const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs,std::vector<glm::vec3> & out_normals)
{
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		} else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	
	}
	fclose(file);
	return true;
}

void Mesh::loadObj(const std::string path)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    _loadOBJ(path.c_str(), vertices, uvs, normals);
    this->generateColor(vertices.size() + 60);

    for (int i = 0; i < vertices.size(); i++) {
        _buffer.push_back(vertices[i].x);
        _buffer.push_back(vertices[i].y);
        _buffer.push_back(vertices[i].z);
    }

    glGenBuffers(1, &_meshbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glBufferData(GL_ARRAY_BUFFER, _buffer.size() * sizeof(GLfloat) + 3, _buffer.data(), GL_STATIC_DRAW);
}

void Mesh::generateColor(int size)
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
}

void Mesh::draw() const
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


    glDrawArrays(GL_TRIANGLES, 0, _buffer.size());
    glDisableVertexAttribArray(0);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _colorbuffer);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Mesh::translate(glm::vec3 vec)
{
    for (int i = 0; i < _buffer.size(); i += 3) {
        _buffer[i] += vec.x;
        _buffer[i + 1] += vec.y;
        _buffer[i + 2] += vec.z;
    }
    _position += vec;

    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glBufferData(GL_ARRAY_BUFFER, _buffer.size() * sizeof(GLfloat), _buffer.data(), GL_STATIC_DRAW);
}

void Mesh::rotate(glm::vec3 vec)
{
    glm::mat4 rot = glm::mat4(1.0f);
    glm::vec3 pos;

    for (int i = 0; i < _buffer.size(); i += 3) {
        pos.x += _buffer[i];
        pos.y += _buffer[i + 1];
        pos.z += _buffer[i + 2];
    }

    pos.x /= _buffer.size() / 3;
    pos.y /= _buffer.size() / 3;
    pos.z /= _buffer.size() / 3;

    rot = glm::rotate(rot, glm::radians(vec.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rot = glm::rotate(rot, glm::radians(vec.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rot = glm::rotate(rot, glm::radians(vec.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 new_pos = glm::vec3(0.0f);
    for (int i = 0; i < _buffer.size(); i += 3) {
        glm::vec4 tmp = rot * glm::vec4(_buffer[i] - pos.x, _buffer[i + 1] - pos.y, _buffer[i + 2] - pos.z, 1.0f);
        _buffer[i] = tmp.x + pos.x;
        _buffer[i + 1] = tmp.y + pos.y;
        _buffer[i + 2] = tmp.z + pos.z;
        new_pos.x += _buffer[i];
        new_pos.y += _buffer[i + 1];
        new_pos.z += _buffer[i + 2];
    }

    new_pos.x /= _buffer.size() / 3;
    new_pos.y /= _buffer.size() / 3;
    new_pos.z /= _buffer.size() / 3;

    glm::vec3 diff = pos - new_pos;
    std::cout << "pos: " << pos.x << " " << pos.y << " " << pos.z << std::endl;

    glDeleteBuffers(1, &_meshbuffer);
    glGenBuffers(1, &_meshbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _meshbuffer);
    glBufferData(GL_ARRAY_BUFFER, _buffer.size() * sizeof(GLfloat), _buffer.data(), GL_STATIC_DRAW);
}
