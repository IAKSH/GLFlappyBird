#pragma once

#include <array>
#include <random>

#include "gameplay.hpp"

class FlappyBird : public flat::Gameplay
{
private:
	flat::Drawable bird;
	flat::Drawable pipe;
	flat::Drawable score;
	flat::Drawable background;
	flat::Animation birdAni;
	flat::Animation pipeDownAni;
	flat::Animation pipeUpAni;
	flat::Animation backgorundAni;
	flat::Animation scoreAni;
	flat::AudioSource birdSoundSource;
	flat::AudioSource backGroundSource;
	flat::AudioSource scoreSource;
	wava::WavAudio flySound;
	wava::WavAudio hitSound;
	wava::WavAudio scoredSound;
	wava::WavAudio levelUpSound;
	wava::WavAudio bgm;

	bool hit = false;
	float backgroundX = 0.0f;
	float birdY = 0.0f;
	float birdVelocity = 0.0f;
	float pipeMarkX = 1.0f;
	std::array<float, 6> pipeOffsetX{ 0 };
	std::array<float, 6> pipeOffsetY{ 0 };
	std::chrono::steady_clock::time_point lastFly;
	std::random_device rd;

	void checkHit(bool up, float pipeY);
	void rerollPipeHeight();
	void rerollPipeDistance();
	void initializeDraws();
	void initializeAnimations();
	void initializeSounds();
	void initializeAudioSources();
	void initializeCustomSettings();
	void handleInput(GLFWwindow* window);
	void draw();
	void tick();

public:
	FlappyBird()
	{

	}

	~FlappyBird()
	{

	}
};
