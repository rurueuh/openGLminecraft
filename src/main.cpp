#include "main.h"

int main_(int ac, char** av)
{
    srand(static_cast<unsigned int>(time(NULL)));
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 1920, 1080, 0.1f, 10000.0f
    );
    camera->RotateLeft(40.0f);
    camera->RotateDown(40.0f);
    Window window(1920, 1080, "OpenGL", camera);

    GLuint VertexArrayID; // TODO: understand what this is
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

	const int PLATFORM_SIZE = 150;
	std::vector<std::shared_ptr<Mesh>> mesh = {};
	const std::string prefixPath = "../../../assets/";
	std::shared_ptr<Shader> sh = std::make_shared<Shader>(prefixPath + "shader");

	for (int x = 0; x < PLATFORM_SIZE; x++) {
		for (int y = 0; y < PLATFORM_SIZE; y++) {
			auto m = std::make_shared<Mesh>(prefixPath + "untitled.obj", prefixPath + "shader", prefixPath + "dirt.png");
			m->setPosition(glm::vec3(y, 0 , x));
			mesh.push_back(m);
		}
	}

    float speedMove = 0.01f;
    std::vector<double> fpsList;
    double averageFps=0;

    while (window.shouldClose() == false && window.isKeyPressed(GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        window.clear();

		sh->use();
		sh->setMVP(Window::getCamera()->getMVP());
		sh->setTexture(0);

        for (int i = 0; i < PLATFORM_SIZE * PLATFORM_SIZE; i++) {
            mesh[i]->draw();
        }
        window.update();

		if (window.hasFocus()) {
			WindowMoveCamera(window, camera, speedMove);
			WindowMouseMoveCamera(window, camera);
		}

        double fps = window.getFPS();
        fpsList.push_back(fps);
        window.setTitle("OpenGL FPS: " + std::to_string(fps));

        window.render();
    }
    averageFps = std::accumulate(fpsList.begin(), fpsList.end(), 0.0) / fpsList.size();
    std::cout << "Average FPS: " << averageFps << std::endl;

    glDeleteVertexArrays(1, &VertexArrayID);
    return 0;
}

int main(int argc, char** argv)
{
	try {
		return main_(argc, argv);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	/* {
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			return -1;
		}
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(1024, 768, "Tutorial 05 - Textured Cube", NULL, NULL);
		if (window == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			return -1;
		}
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);
		GLuint programID = Shader::LoadShaders("../../../assets/shader.vert", "../../../assets/shader.frag");
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			 1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,
			 1.0f,-1.0f,-1.0f,
			 1.0f, 1.0f,-1.0f,
			 1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			 1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			 1.0f,-1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
			 1.0f,-1.0f,-1.0f,
			 1.0f, 1.0f,-1.0f,
			 1.0f,-1.0f,-1.0f,
			 1.0f, 1.0f, 1.0f,
			 1.0f,-1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			 1.0f,-1.0f, 1.0f
		};
		static const GLfloat g_uv_buffer_data[] = {
			0.000059f, 1.0f - 0.000004f,
			0.000103f, 1.0f - 0.336048f,
			0.335973f, 1.0f - 0.335903f,
			1.000023f, 1.0f - 0.000013f,
			0.667979f, 1.0f - 0.335851f,
			0.999958f, 1.0f - 0.336064f,
			0.667979f, 1.0f - 0.335851f,
			0.336024f, 1.0f - 0.671877f,
			0.667969f, 1.0f - 0.671889f,
			1.000023f, 1.0f - 0.000013f,
			0.668104f, 1.0f - 0.000013f,
			0.667979f, 1.0f - 0.335851f,
			0.000059f, 1.0f - 0.000004f,
			0.335973f, 1.0f - 0.335903f,
			0.336098f, 1.0f - 0.000071f,
			0.667979f, 1.0f - 0.335851f,
			0.335973f, 1.0f - 0.335903f,
			0.336024f, 1.0f - 0.671877f,
			1.000004f, 1.0f - 0.671847f,
			0.999958f, 1.0f - 0.336064f,
			0.667979f, 1.0f - 0.335851f,
			0.668104f, 1.0f - 0.000013f,
			0.335973f, 1.0f - 0.335903f,
			0.667979f, 1.0f - 0.335851f,
			0.335973f, 1.0f - 0.335903f,
			0.668104f, 1.0f - 0.000013f,
			0.336098f, 1.0f - 0.000071f,
			0.000103f, 1.0f - 0.336048f,
			0.000004f, 1.0f - 0.671870f,
			0.336024f, 1.0f - 0.671877f,
			0.000103f, 1.0f - 0.336048f,
			0.336024f, 1.0f - 0.671877f,
			0.335973f, 1.0f - 0.335903f,
			0.667969f, 1.0f - 0.671889f,
			1.000004f, 1.0f - 0.671847f,
			0.667979f, 1.0f - 0.335851f
		};

		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		GLuint uvbuffer;
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

		do {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(programID);

			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

			glActiveTexture(GL_TEXTURE0);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			glfwSwapBuffers(window);
			glfwPollEvents();

		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteProgram(programID);
		glDeleteTextures(1, &Texture);
		glDeleteVertexArrays(1, &VertexArrayID);
		glfwTerminate();
	}*/
	return 0;
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

    if (window.isKeyPressed(GLFW_KEY_Q) == GLFW_PRESS)
        camera->RotateLeft(0.5f);
    if (window.isKeyPressed(GLFW_KEY_E) == GLFW_PRESS)
        camera->RotateRight(0.5f);
}

void WindowMoveCamera(Window& window, std::shared_ptr<Camera>& camera, float& speed)
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

    if (window.isKeyPressed(GLFW_KEY_LEFT) == GLFW_PRESS)
        speed -= 0.001f;
    if (window.isKeyPressed(GLFW_KEY_RIGHT) == GLFW_PRESS)
        speed += 0.001f;
}
