#include "flappybird.hpp"

#include <random>
#include <cmath>

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

#include <iostream>

void FlappyBird::draw()
{
	getShader().write("xyoffset_tex", { background.offset,0.0f });
	getShader().draw(map, nullptr, nullptr, background);

	{
		getShader().write("xyoffset_tex", { 0.0f,0.0f });
		auto birdPos = bird.getPosition();
		std::array<float, 3> birdTrans = { birdPos.at(0), birdPos.at(1), 0.0f };
		//std::array<float, 4> birdRotate = { sin(birdPos.at(1) + 0.5f), 0.0f, 0.0f, 1.0f};
		//getShader().draw(map, &birdTrans, &birdRotate, bird);
		getShader().draw(map, &birdTrans, nullptr, bird);
	}

	for (auto& pipe : pipes)
	{
		getShader().write("xyoffset_tex", { 0.0f,0.0f });
		auto pos = pipe.getPosition();
		std::array<float, 3> trans = { pos.at(0), pos.at(1), 0.0f };
		getShader().draw(map, &trans, nullptr, pipe);
	}
}

void FlappyBird::tick()
{
	bird.onTick();
	background.onTick();

	for (auto& pipe : pipes)
	{
		pipe.onTick();
	}
}

void FlappyBird::initializeCustomSettings()
{
	map.boaderX = 1.0f;
	map.boaderY = 1.0f;

	int i = 3;
	for (auto& pipe : pipes)
	{
		pipe.id = i++;
		pipe.name = std::format("pipe{}", i - 3);
		pipe.reroll(i);
		//pipe.setPosition(i, 0.0f, 0.0f);
	}
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

Pipe::Pipe()
{
	writeVertexes({ 0.07f,1.0f,-0.1f,0.07f,-1.0f,-0.1f,-0.07f,-1.0f,-0.1f,-0.07f,1.0f,-0.1f });
	writeColors({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
	writeTexCoord({ 1.0f,1.0f, 1.0f,0.0f ,0.0f,0.0f,0.0f,1.0f });
	makeDrawMeta();

	loadNewAnimation("down", 1000, { "images\\pipe_down.png" });
	loadNewAnimation("up", 1000, { "images\\pipe_up.png" });
	loadAnimation("up");
}

Pipe::~Pipe()
{
}

void Pipe::onTick()
{
	if (getPosition().at(0) <= -1.5f)
		reroll(1.5f);
	auto oriPos = getPosition();
	setPosition(oriPos.at(0) - 0.01f, oriPos.at(1), oriPos.at(2));
}

void Pipe::reroll(float x)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> distrib1(-2.0f, 2.0f);//down: 0.75~2.0 up:-2.0~0.75
	float d = distrib1(gen);
	if (d <= 1.0f)
		loadAnimation("up");
	else
		loadAnimation("down");

	setPosition(x, d, 0.0f);
}
