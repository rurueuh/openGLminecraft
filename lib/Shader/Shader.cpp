#include "Shader.hpp"
constexpr auto DEBUG_SHADER = false;

std::map<std::string, GLuint> Shader::shadersInteligi = {};

GLuint Shader::LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else {
        std::string error = "error on loading Shader : " + (std::string)vertex_file_path + " file not found";
        throw std::runtime_error(error.c_str());
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

GLuint Shader::inteligiLoad(const std::string& path)
{
    return inteligiLoad(path.c_str());
}

GLuint Shader::inteligiLoad(const char* path)
{
    if (shadersInteligi.find(path) != shadersInteligi.end()) {
        if (DEBUG_SHADER)
            std::cout << "Shader already loaded: " << path << std::endl;
        return shadersInteligi[path];
    } else {
        std::string vert = path + (std::string)".vert";
        std::string frag = path + (std::string)".frag";
		shadersInteligi[path] = LoadShaders(vert.c_str(), frag.c_str());
        if (DEBUG_SHADER)
            std::cout << "Shader loaded: " << path << std::endl;
		return shadersInteligi[path];
	}
}

Shader::Shader(const char* path)
{
    _programID = inteligiLoad(path);
	_matrixID = glGetUniformLocation(_programID, "MVP");
    this->getTexture("myTextureSampler");
}

Shader::Shader(const std::string& path)
{
    _programID = inteligiLoad(path);
    _matrixID = glGetUniformLocation(_programID, "MVP");
    this->getTexture("myTextureSampler");
}

Shader::~Shader()
{
    glDeleteProgram(_programID);
}

void Shader::getTexture(const std::string& name)
{
    _textureID = glGetUniformLocation(_programID, name.c_str());
}

void Shader::use() const
{
    glUseProgram(_programID);
}

void Shader::setMVP(glm::mat4 matrix) const
{
    glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setTexture(int chan)
{
    glUniform1i(_textureID, chan);
}
