/*
** EPITECH PROJECT, 2023
** tuto6
** File description:
** Camera
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <bits/stdc++.h>

class Camera {
    public:
        Camera(glm::vec3 position, glm::vec3 target, 
                float fov,
                float width, float height,
                float near, float far);
        ~Camera();

        glm::mat4 getProjection() const { return _projection; };
        glm::mat4 getView() const { return _view; };
        glm::mat4 getModel() const { return _model; };
        glm::mat4 getMVP() const { return MVP; };
        glm::vec3 getPosition() const { return _position; };
        glm::vec3 getTarget() const { return _target; };
        float getHorizontalAngle() const { return horizontalAngle; };
        float getVerticalAngle() const { return verticalAngle; };

        void setProjection(glm::mat4 projection) { _projection = projection; };
        void setView(glm::mat4 view) { _view = view; };
        void setModel(glm::mat4 model) { _model = model; };
        void setMVP(glm::mat4 mvp) { MVP = mvp; };
        void setPosition(glm::vec3 position) { _position = position; };
        void setTarget(glm::vec3 target) { _target = target; };
        void setHorizontalAngle(float angle) { horizontalAngle = angle; };
        void setVerticalAngle(float angle) { verticalAngle = angle; };

        void lookAt(glm::vec3 target) {
            _view = glm::lookAt(
                _position, // Camera is at (4,3,3), in World Space
                _target, // and looks at the origin
                glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
            );
            update();
        };

        void update() {MVP = _projection * _view * _model;};

    protected:
        glm::mat4 _projection = glm::perspective(glm::radians(45.0f), (float) 1024 / 768, 0.1f, 100.0f);
        static glm::mat4 _view; // idk why but it doesn't work if it's not static
        glm::mat4 _model = glm::mat4 (
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
        glm::mat4 MVP = _projection * _view * _model;
        static glm::vec3 _position;
        static glm::vec3 _target;
        float horizontalAngle = M_PI;
        float verticalAngle = 0.0f;
    private:
};

