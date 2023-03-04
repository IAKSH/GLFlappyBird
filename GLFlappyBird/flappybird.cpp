#include "flappybird.hpp"

void FlappyBird::handleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		exit();
	else if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		auto oriVelocity = bird.getVelocity();
		bird.setVelocity(oriVelocity.at(0), 0.05f, oriVelocity.at(2));
		bird.playFlySound();
	}
}

void FlappyBird::draw()
{
	getShader().write("xyoffset_tex", { background.offset,0.0f });
	getShader().draw(map, background);
	getShader().write("xyoffset_tex", { 0.0f,0.0f });
	getShader().draw(map, bird);
}

void FlappyBird::tick()
{
	bird.onTick();
	background.onTick();
}

void FlappyBird::initializeCustomSettings()
{
	map.boaderX = 1.0f;
	map.boaderY = 1.0f;
}

Bird::Bird()
{
	id = 1;
	name = "bird";

	writeVertexes({ 0.07f,0.1f,0.0f,0.07f,-0.1f,0.0f,-0.07f,-0.1f,0.0f,-0.07f,0.1f,0.0f });
	writeColors({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
	writeTexCoord({ 1.0f,1.0f, 1.0f,0.0f ,0.0f,0.0f,0.0f,1.0f });
	makeDrawMeta();

	loadNewAnimation("fly", 250, { "images\\bird0_0.png","images\\bird0_1.png","images\\bird0_2.png" });
	loadAnimation("fly");

	flySound.load("sounds\\fly.wav");
	setLoopable(false);
	updateSoundPhysics();

	setPosition(-0.8f, 0.0f, 0.0f);
}

Bird::~Bird()
{
}

void Bird::onTick()
{
	auto oriPosition = getPosition();
	auto velocity = getVelocity();
	setPosition(oriPosition.at(0), oriPosition.at(1) + velocity.at(1), oriPosition.at(2));
	setVelocity(velocity.at(0), velocity.at(1) - 0.005f, velocity.at(2));
}

void Bird::playFlySound()
{
	playSound(flySound.getBuffer());
}

Background::Background()
{
	id = 2;
	name = "background";

	writeVertexes({ 1.0f,1.0f,-0.5f,1.0f,-1.0f,-0.5f,-1.0f,-1.0f,-0.5f,-1.0f,1.0f,-0.5f });
	writeColors({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
	writeTexCoord({ 1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f });
	makeDrawMeta();

	loadNewAnimation("day", 250, { "images\\bg_day.png" });
	loadAnimation("day");
}

Background::~Background()
{
}

void Background::onTick()
{
	offset += 0.005f;
	if (offset <= -1.0f)
		offset = 1.0f;
}
