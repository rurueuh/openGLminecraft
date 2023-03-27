/*
** EPITECH PROJECT, 2023
** tuto6
** File description:
** Window
*/

#include "Window.hpp"

Window::Window(float width, float height, const std::string &title)
    : _width(width), _height(height), _title(title)
{
    _window = initWindow();
    glEnable(GL_CULL_FACE);
    glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    _camera = new Camera(glm::vec3(5, 5, 50), glm::vec3(0, 0, 0), 45.0f, width, height, 0.1f, 10000.0f); // near and far, good to remember
}

Window::~Window()
{
    delete _camera;
}

void Window::initglfw()
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

void Window::initglew()
{
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }
}
        
std::shared_ptr<GLFWwindow> Window::initWindow()
{
    initglfw();
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // We force OpenGL 3.3
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    std::shared_ptr<GLFWwindow> window(glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL), [](GLFWwindow *window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    });

    glfwMakeContextCurrent(window.get());
    glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);

    initglew();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    return window;
}

void Window::draw(const Mesh &mesh) const
{
    mesh.draw();
}

void Window::render() const
{
    glfwSwapBuffers(_window.get());
    glfwPollEvents();
}

void Window::update()
{
    if (isKeyPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(_window.get(), GL_TRUE);
    }

    glm::vec3 target = _camera->getTarget();
    glm::vec3 position = _camera->getPosition();

    float horizontalAngle = _camera->getHorizontalAngle();
    float verticalAngle = _camera->getVerticalAngle();

    const float SPEED = 10.0f;
    const float MOUSE_SPEED = 0.03f;

    double xpos, ypos;
    glfwGetCursorPos(_window.get(), &xpos, &ypos);
    glfwSetCursorPos(_window.get(), _width / 2, _height / 2);

    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    lastTime = currentTime;
    std::cout << "deltaTime: " << deltaTime << std::endl;

    horizontalAngle += MOUSE_SPEED * deltaTime * float(_width / 2 - xpos);
    verticalAngle += MOUSE_SPEED * deltaTime * float(_height / 2 - ypos);
    std::cout << "horizontalAngle: " << horizontalAngle << std::endl;
    std::cout << "verticalAngle: " << verticalAngle << std::endl;

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - M_PI / 2.0f),
        0,
        cos(horizontalAngle - M_PI / 2.0f)
    );

    glm::vec3 up = glm::cross(right, direction);

    if (glfwGetKey(_window.get(), GLFW_KEY_W ) == GLFW_PRESS){
        position += direction * deltaTime * SPEED;
    }
    if (glfwGetKey(_window.get(), GLFW_KEY_S ) == GLFW_PRESS){
        position -= direction * deltaTime * SPEED;
    }
    if (glfwGetKey(_window.get(), GLFW_KEY_D ) == GLFW_PRESS){
        position += right * deltaTime * SPEED;
    }
    if (glfwGetKey(_window.get(), GLFW_KEY_A ) == GLFW_PRESS){
        position -= right * deltaTime * SPEED;
    }
    if (glfwGetKey(_window.get(), GLFW_KEY_SPACE ) == GLFW_PRESS){
        position += up * deltaTime * SPEED;
    }
    if (glfwGetKey(_window.get(), GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
        position -= up * deltaTime * SPEED;
    }
    
    _camera->setView(glm::lookAt(
        position,
        position + direction,
        up
    ));
    _camera->setPosition(position);
    _camera->setTarget(target);
    _camera->setHorizontalAngle(horizontalAngle);
    _camera->setVerticalAngle(verticalAngle);
    _camera->update();

}