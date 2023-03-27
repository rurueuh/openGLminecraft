/*
** EPITECH PROJECT, 2023
** tuto6
** File description:
** Camera
*/

#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 target, 
                float fov,
                float width, float height,
                float near, float far
            )
{
    _projection = glm::perspective(fov, width / height, near, far);
    _cameraPos = position;
    _cameraTarget = target;
    _cameraUp = glm::vec3(0, 1, 0);
    calculateMVP();
}

Camera::~Camera()
{
}

void Camera::calculateDirection()
{
    _cameraDirection = glm::vec3(
        cos(_verticalAngle) * sin(_horizontalAngle),
        sin(_verticalAngle),
        cos(_verticalAngle) * cos(_horizontalAngle)
    );

    glm::vec3 right = glm::vec3(
        sin(_horizontalAngle - 3.14f/2.0f),
        0,
        cos(_horizontalAngle - 3.14f/2.0f)
    );

    glm::vec3 up = glm::cross(right, _cameraDirection);

    _view = glm::lookAt(
        _cameraPos,
        _cameraPos + _cameraDirection,
        up
    );
}

void Camera::calculateMVP()
{
    calculateDirection();
    _mvp = _projection * _view * _model;
}

void Camera::MoveForward(float speed)
{
    _cameraPos += _cameraDirection * speed;
    calculateMVP();
}

void Camera::MoveBackward(float speed)
{
    _cameraPos -= _cameraDirection * speed;
    calculateMVP();
}

void Camera::MoveLeft(float speed)
{
    _cameraPos -= glm::vec3(
        sin(_horizontalAngle - 3.14f/2.0f),
        0,
        cos(_horizontalAngle - 3.14f/2.0f)
    ) * speed;
    calculateMVP();
}

void Camera::MoveRight(float speed)
{
    _cameraPos += glm::vec3(
        sin(_horizontalAngle - 3.14f/2.0f),
        0,
        cos(_horizontalAngle - 3.14f/2.0f)
    ) * speed;
    calculateMVP();
}

void Camera::MoveUp(float speed)
{
    _cameraPos += glm::vec3(0, 1, 0) * speed;
    calculateMVP();
}

void Camera::MoveDown(float speed)
{
    _cameraPos -= glm::vec3(0, 1, 0) * speed;
    calculateMVP();
}

void Camera::RotateLeft(float speed)
{
    _horizontalAngle += speed / 60; // div 6=0 to make 90° is really 90°
    calculateMVP();
}

void Camera::RotateRight(float speed)
{
    _horizontalAngle -= speed / 60; // div 6=0 to make 90° is really 90°
    calculateMVP();
}

void Camera::RotateUp(float speed)
{
    _verticalAngle += speed / 60; // div 6=0 to make 90° is really 90°
    calculateMVP();
}

void Camera::RotateDown(float speed)
{
    _verticalAngle -= speed / 60; // div 6=0 to make 90° is really 90°
    calculateMVP();
}
