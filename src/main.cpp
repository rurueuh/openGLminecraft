#include "main.h"
constexpr bool WIREFRAM = true;

void setWireframe(const Window &window)
{
    static bool wireframe = false;
    if (window.isKeyPressed(GLFW_KEY_Z) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        wireframe = true;
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireframe = false;
    }
}

int main_(int ac, char** av)
{
    srand(static_cast<unsigned int>(time(NULL)));
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 1920, 1080, 0.1f, 160.0f
    );
    camera->RotateLeft(40.0f);
    camera->RotateDown(40.0f);
    Window window(1920, 1080, "OpenGL", camera);

    Cube cube;
    Cube cube2;
    cube.setPos(glm::vec3(0.0f, 0.0f, 0.0f));
    cube2.setPos(glm::vec3(1.0f, 0.0f, 0.0f));
    
    std::vector<GLfloat> vertex = cube.getVertices();
    std::vector<GLfloat> vertex2 = cube2.getVertices();
    std::vector<GLfloat> vertexuv = {
        0.875, -0.5,
        0.625, -0.75,
        0.625, -0.5,
        0.625, -0.75,
        0.375, -1,
        0.375, -0.75,
        0.625, -0,
        0.375, -0.25,
        0.375, -0,
        0.375, -0.5,
        0.125, -0.75,
        0.125, -0.5,
        0.625, -0.5,
        0.375, -0.75,
        0.375, -0.5,
        0.625, -0.25,
        0.375, -0.5,
        0.375, -0.25,
        0.875, -0.5,
        0.875, -0.75,
        0.625, -0.75,
        0.625, -0.75,
        0.625, -1,
        0.375, -1,
        0.625, -0,
        0.625, -0.25,
        0.375, -0.25,
        0.375, -0.5,
        0.375, -0.75,
        0.125, -0.75,
        0.625, -0.5,
        0.625, -0.75,
        0.375, -0.75,
        0.625, -0.25,
        0.625, -0.5,
        0.375, -0.5,
    };

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);

    GLuint vbo_uv = 0;
    glGenBuffers(1, &vbo_uv);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, vertexuv.size() * sizeof(GLfloat), vertexuv.data(), GL_STATIC_DRAW);

    Shader sh = Shader("../assets/shader");
    Texture tex = Texture("../assets/text.png");
    sh.setTexture(0);
    const float speed = 0.15f;
    bool ispressed = false;
    while (window.shouldClose() == false && window.isKeyPressed(GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        window.clear();
        
        sh.setMVP(Window::getCamera()->getMVP());
        sh.use();

		if (window.hasFocus()) {
			WindowMoveCamera(window, camera, speed);
			WindowMouseMoveCamera(window, camera);
            setWireframe(window);
            MoveCube(window, ispressed, cube, cube2);
		}

        drawCube(vertex, cube, vertex2, cube2, vbo);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glDrawArrays(GL_TRIANGLES, 0, vertex.size());
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        double fps = window.getFPS();
        window.setTitle("OpenGL FPS: " + std::to_string(fps));

        window.render();
    }
    return 0;
}

void drawCube(std::vector<GLfloat>& vertex, Cube& cube, std::vector<GLfloat>& vertex2, Cube& cube2, const GLuint& vbo)
{
    vertex = cube.getVertices();
    vertex2 = cube2.getVertices();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    vertex.insert(vertex.end(), vertex2.begin(), vertex2.end());
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);
}

void MoveCube(Window& window, bool& ispressed, Cube& cube, Cube& cube2)
{
    if (window.isKeyPressed(GLFW_KEY_LEFT) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(1, 0.0f, 0.0f));
    }
    if (window.isKeyPressed(GLFW_KEY_RIGHT) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(-1, 0.0f, 0.0f));
    }
    if (window.isKeyPressed(GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(0.0f, 1, 0.0f));
    }
    if (window.isKeyPressed(GLFW_KEY_PAGE_UP) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(0.0f, -1, 0.0f));
    }
    if (window.isKeyPressed(GLFW_KEY_UP) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(0.0f, 0.0f, 1));
    }
    if (window.isKeyPressed(GLFW_KEY_DOWN) == GLFW_RELEASE && ispressed == false) {
        cube.move(glm::vec3(0.0f, 0.0f, -1));
    }
    if (!window.isKeyPressed(GLFW_KEY_LEFT) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_RIGHT) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_UP) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_DOWN) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_PAGE_UP) == GLFW_RELEASE || !window.isKeyPressed(GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE) {
        ispressed = true;
    }
    else {
        if (ispressed == true) {
            ispressed = false;
            cube.calculateDraw(cube2);
            cube2.calculateDraw(cube);
        }
    }
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
