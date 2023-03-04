#include <iostream>
#include "gameplay.hpp"

class FlappyBird : public flat::Gameplay
{
private:
	flat::Drawable bird;
	flat::Drawable pipe;
	flat::Drawable background;
	flat::Animation birdAni;
	flat::Animation pipeDownAni;
	flat::Animation pipeUpAni;
	flat::Animation backgorundAni;
	flat::AudioSource birdSoundSource;
	flat::AudioSource backGroundSource;
	wava::WavAudio flySound;
	//wava::WavAudio hitSound;
	//wava::WavAudio scoredSound;
	//wava::WavAudio levelUpSound;
	//wava::WavAudio bgm;

	float backgroundX = 0.0f;
	float birdY = 0.0f;
	float birdVelocity = 0.0f;

	std::chrono::steady_clock::time_point lastFly;

	void initializeDraws()
	{
		bird.writeVertexes({ 0.07f,0.1f,0.0f,0.07f,-0.1f,0.0f,-0.07f,-0.1f,0.0f,-0.07f,0.1f,0.0f });
		bird.writeColors({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
		bird.writeTexCoord({ 1.0f,1.0f, 1.0f,0.0f ,0.0f,0.0f,0.0f,1.0f });
		bird.make();

		pipe.writeVertexes({ 0.07f,1.0f,-0.1f,0.07f,-1.0f,-0.1f,-0.07f,-1.0f,-0.1f,-0.07f,1.0f,-0.1f });
		pipe.writeColors({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
		pipe.writeTexCoord({ 1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f });
		pipe.make();

		background.writeVertexes({ 1.0f,1.0f,-0.5f,1.0f,-1.0f,-0.5f,-1.0f,-1.0f,-0.5f,-1.0f,1.0f,-0.5f });
		background.writeColors({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
		background.writeTexCoord({ 1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f });
		background.make();
	}

	void initializeAnimations()
	{
		birdAni.load({ "images\\bird0_0.png","images\\bird0_1.png","images\\bird0_2.png" });
		birdAni.setIntervalMS(500);

		pipeUpAni.load({ "images\\pipe_up.png" });
		pipeDownAni.load({ "images\\pipe_down.png" });

		backgorundAni.load({ "images\\bg_day.png" });
	}

	void initializeSounds()
	{
		flySound.load("sounds\\fly.wav");
	}

	void initializeAudioSources()
	{
		birdSoundSource.setLoopable(false);
		birdSoundSource.setPosition(0.5f, 0.0f, 0.0f);
		birdSoundSource.setVelocity(0.0f, 0.0f, 0.0f);
		birdSoundSource.initialize();

		backGroundSource.setLoopable(true);
		backGroundSource.setPosition(0.0f, 0.0f, -0.5f);
		backGroundSource.setVelocity(0.0f, 0.0f, 0.0f);
		backGroundSource.initialize();
	}

	void initializeCustomSettings()
	{
		lastFly = std::chrono::steady_clock::now();
	}

	void handleInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			exit();
		else if (glfwGetKey(window, GLFW_KEY_SPACE))
		{
			if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastFly).count() < 250)
				return;
			birdSoundSource.play(flySound.getBuffer());
			birdVelocity = 0.02f;
			lastFly = std::chrono::steady_clock::now();
		}
	}

	void draw()
	{
		// draw background
		getShader().write("xyoffset", { 0.0f,0.0f });
		getShader().write("xyoffset_tex", { backgroundX,0.0f });
		backgroundX += 0.0025f;
		if (backgroundX >= 1.0f)
			backgroundX = -1.0f;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, backgorundAni.getCurrentTexture());
		background.draw();

		// draw bird
		getShader().write("xyoffset", { -0.8f,birdY });
		getShader().write("xyoffset_tex", { 0.0f,0.0f });
		glActiveTexture(GL_TEXTURE0);
		birdAni.checkUpdate();
		glBindTexture(GL_TEXTURE_2D, birdAni.getCurrentTexture());
		bird.draw();

		// draw pipe up
		getShader().write("xyoffset", { -2.0f * backgroundX,-0.7f });
		getShader().write("xyoffset_tex", { 0.0f,0.0f });
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pipeUpAni.getCurrentTexture());
		pipe.draw();

	}

	void tick()
	{
		// anti-physics code
		birdVelocity -= 0.001f;
		birdY += birdVelocity;

		if (birdY <= -1.0f)
		{
			std::cout << "Game Over!" << std::endl;
			exit();
		}
	}

public:
	FlappyBird()
	{

	}

	~FlappyBird()
	{

	}
};

int main() noexcept
{
	std::cout << "hello\n";

	FlappyBird fb;
	fb.initialize();
	fb.mainLoop();

	return 0;
}