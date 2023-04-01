/*
** EPITECH PROJECT, 2023
** tuto6
** File description:
** Window
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "../Camera/Camera.hpp"
#include "../Mesh/Mesh.hpp"

class Window {
    public:
        Window(int width, int height, const std::string &title, std::shared_ptr<Camera> &camera);
        ~Window();

        // Getters
        std::shared_ptr<GLFWwindow> getWindow() const { return _window; };
        std::shared_ptr<Camera> getCamera() const { return _camera; };
        glm::vec2 getMousePosition() const {
            double xpos, ypos;
            glfwGetCursorPos(_window.get(), &xpos, &ypos);
            return glm::vec2(xpos, ypos);
        };
        double getFPS(); // double call = bug
        bool isKeyPressed(int key) const { return glfwGetKey(_window.get(), key) == GLFW_PRESS; };
        bool shouldClose() const { return glfwWindowShouldClose(_window.get()); };

        // Setters
        void setMousePosition(const glm::vec2 &pos) const { glfwSetCursorPos(_window.get(), pos.x, pos.y); };
        void setTitle(const std::string& name);


        void clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); };
        void update();
        void draw(const Mesh &mesh) const;
        void render() const;

    protected:
        void initglfw();
        void initglew();
        std::shared_ptr<GLFWwindow> initWindow();
        std::shared_ptr<GLFWwindow> _window;

        std::shared_ptr<Camera> _camera;

        int _width;
        int _height;
        std::string _title;
    private:
};
