#include "main.h"

int main_(int ac, char** av)
{
    srand(static_cast<unsigned int>(time(NULL)));
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 1920, 1080, 0.1f, 160.0f
    );
    camera->RotateLeft(40.0f);
    camera->RotateDown(40.0f);
    Window window(1920, 1080, "OpenGL", camera);

    GLfloat vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        // Back face
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        // Top face
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        // Right face
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,

         // Left face
         -0.5f, -0.5f, -0.5f,
         -0.5f,  0.5f, -0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f, -0.5f,  0.5f,
    };

    const float speed = 2.0f;
    while (window.shouldClose() == false && window.isKeyPressed(GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        window.clear();

		if (window.hasFocus()) {
			WindowMoveCamera(window, camera, speed);
			WindowMouseMoveCamera(window, camera);
		}

        double fps = window.getFPS();
        window.setTitle("OpenGL FPS: " + std::to_string(fps));

        window.render();
    }
    return 0;
}

#include <glm/gtc/type_ptr.hpp>

int main(int argc, char** argv)
{
	try {
		return main_(argc, argv);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
    srand(static_cast<unsigned int>(time(NULL)));
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
