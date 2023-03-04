#include "gameplay.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gameplay.hpp"

void flat::Gameplay::initializeShader()
{
	shader.loadAnimation("vertexshader.glsl", "fragmentshader.glsl");
	shader.use();
}

flat::Shader& flat::Gameplay::getShader()
{
	return shader;
}

void flat::Gameplay::initializeGLFW()
{
	glfwInit();
	glfwInitHint(GLFW_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Hello OpenGL!", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "[ERROR] Can't create window!" << std::endl;
		abort();
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(3);
}

void flat::Gameplay::initializeGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "[ERROR] Can't initialize GLAD" << std::endl;
		abort();
	}
}

void flat::Gameplay::bindFramebufferSizeCallback()
{
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });
}

void flat::Gameplay::draw()
{

}

void flat::Gameplay::mainLoop()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		handleInput(window);
		tick();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);// clear last frame
		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

flat::Gameplay::Gameplay()
{
	initializeGamePlay();
}

flat::Gameplay::~Gameplay()
{
	releaseGLFW();
}


void flat::Gameplay::releaseGLFW()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void flat::Gameplay::initializeCustomSettings()
{

}

void flat::Gameplay::handleInput(GLFWwindow* window)
{
	/*
	if (key == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	*/
}

void flat::Gameplay::exit()
{
	glfwSetWindowShouldClose(window, true);
}

void flat::Gameplay::tick()
{

}

void flat::Gameplay::initializeGamePlay()
{
	initializeGLFW();
	initializeGLAD();
	initializeShader();
	initializeListener();
	initializeCustomSettings();
}