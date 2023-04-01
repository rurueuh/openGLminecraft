#include "main.h"

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } else {
        std::string error = "error on loading Shader : " + (std::string)vertex_file_path + " file not found";
        throw std::runtime_error(error.c_str());
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
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
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

int main(int argc, char** argv)
{
    srand(static_cast<time_t>(time(NULL)));
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 1920, 1080, 0.1f, 10000.0f
    );
    camera->RotateLeft(40.0f);
    camera->RotateDown(40.0f);
    Window window(1920, 1080, "OpenGL", camera);

    GLuint VertexArrayID; // TODO: understand what this is
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "../../../assets/SimpleVertexShader.vertexshader", "../../../assets/SimpleFragmentShader.fragmentshader" );
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("../../../assets/box.obj");

    float speedMove = 0.01f;

    while (window.shouldClose() == false && window.isKeyPressed(GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        window.clear();
        glUseProgram(programID);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &window.getCamera()->getMVP()[0][0]);

        mesh->draw();
        window.update();

        WindowMoveCamera(window, camera, speedMove);
        WindowMouseMoveCamera(window, camera);

        double fps = window.getFPS();
        window.setTitle("OpenGL FPS: " + std::to_string(fps));

        window.render();
    }
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
}

void WindowMouseMoveCamera(Window& window, std::shared_ptr<Camera>& camera)
{
    auto mousePos = window.getMousePosition();
    glm::vec2 diff = mousePos - glm::vec2(1920 / 2, 1080 / 2);

    if (diff.x != 0)
        camera->RotateRight(diff.x * 0.1f);
    if (diff.y != 0)
        camera->RotateUp(diff.y * -0.1f);
    window.setMousePosition(glm::vec2(1920 / 2, 1080 / 2));

    if (window.isKeyPressed(GLFW_KEY_Q) == GLFW_PRESS)
        camera->RotateLeft(0.5f);
    if (window.isKeyPressed(GLFW_KEY_E) == GLFW_PRESS)
        camera->RotateRight(0.5f);
}

void WindowMoveCamera(Window& window, std::shared_ptr<Camera>& camera, float& speed)
{
    if (window.isKeyPressed(GLFW_KEY_W) == GLFW_PRESS)
        camera->MoveForward(speed);
    if (window.isKeyPressed(GLFW_KEY_S) == GLFW_PRESS)
        camera->MoveBackward(speed);
    if (window.isKeyPressed(GLFW_KEY_A) == GLFW_PRESS)
        camera->MoveLeft(speed);
    if (window.isKeyPressed(GLFW_KEY_D) == GLFW_PRESS)
        camera->MoveRight(speed);
    if (window.isKeyPressed(GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->MoveUp(speed);
    if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera->MoveDown(speed);

    if (window.isKeyPressed(GLFW_KEY_LEFT) == GLFW_PRESS)
        speed -= 0.001f;
    if (window.isKeyPressed(GLFW_KEY_RIGHT) == GLFW_PRESS)
        speed += 0.001f;
}
