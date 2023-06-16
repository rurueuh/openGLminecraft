#include "main.h"

void setWireframe(const Window &window)
{
    static bool wireframe = false;
    if (window.isKeyPressed(GLFW_KEY_Z) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        wireframe = true;
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireframe = false;
    }
}

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    const char *severityString = "UNKNOWN";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         severityString = "HIGH";         break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severityString = "MEDIUM";       break;
        case GL_DEBUG_SEVERITY_LOW:          severityString = "LOW";          break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityString = "NOTIFICATION"; break;
    }
    const char *sourceString = "UNKNOWN";
    switch (source) {
        case GL_DEBUG_SOURCE_API:             sourceString = "API";             break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceString = "WINDOW SYSTEM";   break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceString = "SHADER COMPILER"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceString = "THIRD PARTY";     break;
        case GL_DEBUG_SOURCE_APPLICATION:     sourceString = "APPLICATION";     break;
        case GL_DEBUG_SOURCE_OTHER:           sourceString = "OTHER";           break;
    }
    const char *typeString = "UNKNOWN";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               typeString = "ERROR";               break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeString = "DEPRECATED BEHAVIOR"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeString = "UDEFINED BEHAVIOR";   break;
        case GL_DEBUG_TYPE_PORTABILITY:         typeString = "PORTABILITY";         break;
        case GL_DEBUG_TYPE_PERFORMANCE:         typeString = "PERFORMANCE";         break;
        case GL_DEBUG_TYPE_MARKER:              typeString = "MARKER";              break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          typeString = "PUSH GROUP";          break;
        case GL_DEBUG_TYPE_POP_GROUP:           typeString = "POP GROUP";           break;
        case GL_DEBUG_TYPE_OTHER:               typeString = "OTHER";               break;
    }
    fprintf( stderr, "GL CALLBACK: %s type = %s, severity = %s, message = %s\n",
        ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), typeString, severityString, message);
}

static void removeCube(Window& window, std::shared_ptr<Camera>& camera, Map &map)
{
    static bool do_once = false;
    if (window.isKeyPressed(GLFW_KEY_E) == GLFW_PRESS && do_once == false) {
        do_once = true;
        auto direction = camera->getCameraDirection();
        glm::vec3 pos = camera->getCameraPos();
        glm::vec3 ray = pos;
        std::shared_ptr<Cube> cube = nullptr;
        int range = 12;
        while (cube == nullptr && range != 0) {
            ray += direction;
            cube = map.getCube(ray.x, ray.y, ray.z);
            if (cube != nullptr)
                break;
            range--;
        }
        if (cube != nullptr) {
            int x = ray.x;
            int y = ray.y;
            int z = ray.z;
            std::cout << x << " " << y << " " << z << std::endl;
            map.removeCube(cube);
        }
        else {
            std::cout << "cube not found" << std::endl;
        }
    }
    else if (window.isKeyPressed(GLFW_KEY_E) == GLFW_RELEASE) {
		do_once = false;
    }

}

int main_(int ac, char** av)
{
    const int sizeX = 200;
    const int sizeY = 55;
    const int sizeZ = 200;
    srand(static_cast<unsigned int>(time(NULL)));
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3(sizeX / 2, sizeY + 2, sizeZ / 2), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 1920, 1080, 0.1f, 16000.0f
    );
    camera->RotateLeft(240.0f);
    camera->RotateDown(40.0f);
    Window window(1920, 1080, "OpenGL", camera);
    window.setFullscreen();
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    Map map(sizeX, sizeY, sizeZ);
    const float speed = 0.85f;
    bool ispressed = false;
    
    while (window.shouldClose() == false && window.isKeyPressed(GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        window.clear();

        map.draw();
        
        if (window.hasFocus()) {
            WindowMoveCamera(window, camera, speed);
            WindowMouseMoveCamera(window, camera);
            setWireframe(window);
            removeCube(window, camera, map);
        }

        double fps = window.getFPS();
        window.setTitle("OpenGL FPS: " + std::to_string(fps));

        window.render();
    }
    return 0;
}

void MoveCube(Window& window, bool& ispressed, Cube& cube)
{
    if (window.isKeyPressed(GLFW_KEY_LEFT) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(1, 0.0f, 0.0f));
    }
    if (window.isKeyPressed(GLFW_KEY_RIGHT) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(-1, 0.0f, 0.0f));
    }
    if (window.isKeyPressed(GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(0.0f, 1, 0.0f));
    }
    if (window.isKeyPressed(GLFW_KEY_PAGE_UP) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(0.0f, -1, 0.0f));
    }
    if (window.isKeyPressed(GLFW_KEY_UP) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(0.0f, 0.0f, 1));
    }
    if (window.isKeyPressed(GLFW_KEY_DOWN) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(0.0f, 0.0f, -1));
    }
    if (!window.isKeyPressed(GLFW_KEY_LEFT) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_RIGHT) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_UP) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_DOWN) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_PAGE_UP) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE) {
        ispressed = true;
    }
    else {
        if (ispressed == true) {
            ispressed = false;
        }
    }
}

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(NULL)));
    try {
        return main_(argc, argv);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
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
}

void WindowMoveCamera(Window& window, std::shared_ptr<Camera>& camera, const float&  speed)
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
}
