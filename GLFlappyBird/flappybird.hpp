#pragma once

#include <array>
#include <random>

#include "gameplay.hpp"
#include "gameobject.hpp"

class Bird : public flat::GameObject
{
private:
	wava::WavAudio flySound;
public:
	Bird();
	~Bird();
	void onTick();
	void playFlySound();
};

class Background : public flat::GameObject
{
public:
	float offset;
	Background();
	~Background();
	void onTick();
};

class Pipe : public flat::GameObject
{
public:
	Pipe();
	~Pipe();
	void onTick();
	void reroll(float x);
};

class FlappyBird : public flat::Gameplay
{
private:
	flat::TransformMap map;
	Bird bird;
	Background background;
	Pipe pipes[3];

	void handleInput(GLFWwindow* window);
	void draw();
	void tick();
	void initializeCustomSettings();

public:
	FlappyBird()
	{
		initializeCustomSettings();
	}

	~FlappyBird()
	{

	}
};
