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
#include <bits/stdc++.h>
#include "../Camera/Camera.hpp"
#include "../Mesh/Mesh.hpp"

class Window {
    public:
        Window(float width, float height, const std::string &title);
        ~Window();

        std::shared_ptr<GLFWwindow> getWindow() const { return _window; };
        Camera * getCamera() const { return _camera; };

        bool shouldClose() const { return glfwWindowShouldClose(_window.get()); };
        bool isKeyPressed(int key) const { return glfwGetKey(_window.get(), key) == GLFW_PRESS; };

        void clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); };
        void update();
        void draw(const Mesh &mesh) const;
        void render() const;

    protected:
        void initglfw();
        void initglew();
        std::shared_ptr<GLFWwindow> initWindow();
        std::shared_ptr<GLFWwindow> _window;

        Camera * _camera;

        int _width;
        int _height;
        std::string _title;
    private:
};
