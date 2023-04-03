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
#include <iostream>

class Camera {
    public:
        Camera(glm::vec3 position, glm::vec3 target, 
                float fov,
                int width, int height,
                float near, float far);
        ~Camera();

        void calculateDirection();
        void calculateMVP();

        // Movement functions
        void MoveForward(float speed);
        void MoveBackward(float speed);
        void MoveLeft(float speed);
        void MoveRight(float speed);
        void MoveUp(float speed);
        void MoveDown(float speed);

        // Rotation functions
        void RotateLeft(float speed);
        void RotateRight(float speed);
        void RotateUp(float speed);
        void RotateDown(float speed);

        glm::mat4 getMVP() const { return _mvp; };
    protected:
        glm::vec3 _cameraPos;
        glm::vec3 _cameraTarget;
        glm::vec3 _cameraDirection;
        glm::vec3 _cameraUp;

        float _horizontalAngle = 3.14f;
        float _verticalAngle = 0.0f;

        glm::mat4 _projection;
        glm::mat4 _view; // idk why but it doesn't work if it's not static
        glm::mat4 _mvp;
        const glm::mat4 _model = glm::mat4 (1.0f);
    private:
};

