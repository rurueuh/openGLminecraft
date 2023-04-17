#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <time.h>
#include <memory>
#include <array>
#include <map>

class Cube {
public:
    Cube(int id);
    ~Cube();

    void calculateDraw(const std::shared_ptr<Cube> &other);
    void resetDraw();
    int getId() const { return _id; }
    std::vector<GLfloat> getVertices() const;
    std::vector<GLfloat> getVerticesUV() const;
    void setPos(const glm::vec3& pos) { _model = glm::translate(glm::mat4(1.0f), pos); }
    /**
     * @brief upper, front, left, bottom, right, back
     */
    glm::vec3 getPos() const { return glm::vec3(_model[3]); }
    void move(const glm::vec3& dir) { _model = glm::translate(_model, dir); }
    bool _facesDraw[6] = { true, true, true, true, true, true};
protected:
private:
    int _id;

    glm::mat4 _model = glm::mat4(1.0f);
    static std::vector<GLfloat> _upper;
    static std::vector<GLfloat> _front;
    static std::vector<GLfloat> _left;
    static std::vector<GLfloat> _bottom;
    static std::vector<GLfloat> _right;
    static std::vector<GLfloat> _back;

    static std::vector<GLfloat> _upperUV;
    static std::vector<GLfloat> _frontUV;
    static std::vector<GLfloat> _leftUV;
    static std::vector<GLfloat> _bottomUV;
    static std::vector<GLfloat> _rightUV;
    static std::vector<GLfloat> _backUV;
};
