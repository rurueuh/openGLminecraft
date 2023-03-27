/*
** EPITECH PROJECT, 2023
** tuto6
** File description:
** Camera
*/

#include "Camera.hpp"

glm::vec3 Camera::_position = glm::vec3(0,0,0);
glm::vec3 Camera::_target = glm::vec3(0,0,0);

glm::mat4 Camera::_view = glm::lookAt(
    Camera::_position, // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
);


Camera::Camera(glm::vec3 position, glm::vec3 target, 
                float fov,
                float width, float height,
                float near, float far
            )
{
    _projection = glm::perspective(glm::radians(fov), (float) width / height, near, far);
    _view = glm::lookAt(
        position,
        target,
        glm::vec3(0, 1, 0)
    );
    _position = position;
    _target = target;
    update();
}

Camera::~Camera()
{
}
