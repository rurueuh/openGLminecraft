/*
** EPITECH PROJECT, 2023
** tuto6
** File description:
** Window
*/

#include "Window.hpp"

std::shared_ptr<Camera> Window::_camera = nullptr;

Window::Window(int width, int height, const std::string &title, std::shared_ptr<Camera> &camera)
    : _width(width), _height(height), _title(title)
{
    _window = initWindow();
    glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(_window.get(), _width / 2, _height / 2);
    _camera = camera;
    initglew();
}

Window::~Window()
{
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
    glfwSwapInterval(0);
    initglew();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    return window;
}

void Window::render() const
{
    glfwSwapBuffers(_window.get());
    glfwPollEvents();
}

double Window::getFPS()
{
    double currentTime = glfwGetTime();
    static double lastTime = 0.0;
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return (1.0 / deltaTime);
}

void Window::setTitle(const std::string& name)
{
    glfwSetWindowTitle(_window.get(), name.c_str());
}

void Window::update()
{
    if (isKeyPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(_window.get(), GL_TRUE);
    }
    _camera->calculateMVP();
}