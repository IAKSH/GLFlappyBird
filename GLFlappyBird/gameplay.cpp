#include "gameplay.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gameplay.hpp"

void flat::Gameplay::initializeAnimations()
{
	/*/
	ani.load({ "idk.png","idk1.png" });
	ani.setIntervalMS(1000);
	*/
}

void flat::Gameplay::initializeShader()
{
	shader.load("vertexshader.glsl", "fragmentshader.glsl");
	shader.use();
}

flat::Shader& flat::Gameplay::getShader()
{
	return shader;
}

void flat::Gameplay::initializeDraws()
{
	/*
	meme.writeVertexes({ 0.5f,0.5f,0.0f,0.5f,-0.5f,0.0f,-0.5f,-0.5f,0.0f,-0.5f,0.5f,0.0f });
	meme.writeColors({ 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f });
	meme.writeTexCoord({ 1.0f,1.0f, 1.0f,0.0f ,0.0f,0.0f,0.0f,1.0f });
	meme.make();

	meme2.writeVertexes({ 1.0f,1.0f,0.0f,0.0f,-0.36f,0.0f,-0.5f,-0.5f,0.0f,-0.5f,0.5f,0.0f });
	meme2.writeColors({ 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f });
	meme2.writeTexCoord({ 1.0f,1.0f, 1.0f,0.0f ,0.0f,0.0f,0.0f,1.0f });
	meme2.make();
	*/
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
	/*
	// update uniform
	shader.write("xyoffset", { static_cast<float>(sin(glfwGetTime())), static_cast<float>(cos(glfwGetTime())) });
	// transform!!!
	glm::mat4 trans(1.0f);
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.getShaderProgram(), "transform"), 1, GL_FALSE, glm::value_ptr(trans));

	ani.checkUpdate();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ani.getCurrentTexture());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ani.getCurrentTexture());

	meme.draw();
	meme2.draw();
	*/
}

void flat::Gameplay::mainLoop()
{
	// test
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	while (!glfwWindowShouldClose(window))
	{
		// input
		handleInput(window);

		// update
		tick();

		// draw
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

}

flat::Gameplay::~Gameplay()
{
	releaseGLFW();
	releaseOpenAL();
}

void flat::Gameplay::initialize()
{
	initializeGLFW();
	initializeGLAD();
	bindFramebufferSizeCallback();
	initializeOpenAL();
	initializeShader();
	
	initializeDraws();
	initializeAnimations();
	initializeSounds();
	initializeAudioSources();

	initializeCustomSettings();
}

void flat::Gameplay::initializeOpenAL()
{
	// open defeault device
	device = alcOpenDevice(nullptr);
	context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);
}

void flat::Gameplay::releaseGLFW()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void flat::Gameplay::releaseOpenAL()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void flat::Gameplay::initializeSounds()
{
	/*
	footStep.load("a.wav");
	*/
}

void flat::Gameplay::initializeAudioSources()
{
	/*
	footStepSource.initialize();
	footStepSource.setBuffer(footStep.getBuffer());
	footStepSource.setPosition(0.0f, 0.0f, 0.0f);
	footStepSource.setVelocity(0.0f, 0.0f, 0.0f);
	footStepSource.setLoopable(true);

	//test
	footStepSource.play();
	*/
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