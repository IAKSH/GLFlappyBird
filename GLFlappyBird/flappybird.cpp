#include "flappybird.hpp"

void FlappyBird::checkHit(bool up, float pipeY)
{
	if (up)
	{
		hit = pipeY + 1.0f >= birdY;
	}
	else
	{
		// can't work
		//hit = pipeY - 1.0f <= birdY
	}

	// play scoredSound
	if (!hit)
	{
		scoreAni.checkUpdate();
		scoreSource.play(scoredSound.getBuffer());
	}
	else
	{
		//scoreSource.play(hitSound.getBuffer());
	}
}

void FlappyBird::rerollPipeHeight()
{
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> distrib1(-1.5f, -0.25f);
	static std::uniform_real_distribution<float> distrib2(0.75f, 1.5f);
	for (auto& item : pipeOffsetY)
		item = distrib1(gen);
}

void FlappyBird::rerollPipeDistance()
{
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> distrib1(-1.5f, -0.25f);
	static std::uniform_real_distribution<float> distrib2(0.75f, 1.5f);
	for (auto& item : pipeOffsetX)
		item = distrib2(gen);
}

void FlappyBird::initializeDraws()
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

	score.writeVertexes({ 0.075f,0.1f,0.0f,0.075f,-0.1f,0.0f,-0.075f,-0.1f,0.0f,-0.075f,0.1f,0.0f });
	score.writeColors({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
	score.writeTexCoord({ 1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f });
	score.make();
}

void FlappyBird::initializeAnimations()
{
	birdAni.load({ "images\\bird0_0.png","images\\bird0_1.png","images\\bird0_2.png" });
	birdAni.setIntervalMS(500);

	pipeUpAni.load({ "images\\pipe_up.png" });
	pipeDownAni.load({ "images\\pipe_down.png" });

	backgorundAni.load({ "images\\bg_day.png" });

	scoreAni.load({ "images\\font_048.png","images\\font_049.png","images\\font_050.png","images\\font_051.png","images\\font_052.png","images\\font_053.png","images\\font_054.png","images\\font_055.png","images\\font_056.png","images\\font_057.png" });
}

void FlappyBird::initializeSounds()
{
	flySound.load("sounds\\fly.wav");
	//hitSound.load("sounds\\hit.wav");
	scoredSound.load("sounds\\scored.wav");
	//levelUpSound.load("sounds\\levelUp.wav");
	bgm.load("sounds\\bgm.wav");
}

void FlappyBird::initializeAudioSources()
{
	birdSoundSource.setLoopable(false);
	birdSoundSource.setPosition(0.5f, 0.0f, 0.0f);
	birdSoundSource.setVelocity(0.0f, 0.0f, 0.0f);
	birdSoundSource.initialize();

	backGroundSource.setLoopable(true);
	backGroundSource.setPosition(0.0f, 0.0f, -0.5f);
	backGroundSource.setVelocity(0.0f, 0.0f, 0.0f);
	backGroundSource.initialize();

	scoreSource.setLoopable(false);
	scoreSource.setPosition(0.0f, 0.0f, -0.2f);
	scoreSource.setVelocity(0.0f, 0.0f, 0.0f);
	scoreSource.initialize();
}

void FlappyBird::initializeCustomSettings()
{
	lastFly = std::chrono::steady_clock::now();
	rerollPipeDistance();
	rerollPipeHeight();
	backGroundSource.play(bgm.getBuffer());
}

void FlappyBird::handleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		exit();
	else if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastFly).count() < 125)
			return;
		birdSoundSource.play(flySound.getBuffer());
		birdVelocity = 0.025f;
		lastFly = std::chrono::steady_clock::now();
	}
}

void FlappyBird::draw()
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

	float x = pipeMarkX;
	// draw pipe up
	getShader().write("xyoffset_tex", { 0.0f,0.0f });
	glActiveTexture(GL_TEXTURE0);
	// pipe 1 (up)
	glBindTexture(GL_TEXTURE_2D, pipeUpAni.getCurrentTexture());
	getShader().write("xyoffset", { x,pipeOffsetY.at(0) });
	pipe.draw();
	if (-0.9f < x && x < -0.7f)
		checkHit(true, pipeOffsetY.at(0));
	// pipe 2 (up)
	glBindTexture(GL_TEXTURE_2D, pipeUpAni.getCurrentTexture());
	getShader().write("xyoffset", { x += pipeOffsetX.at(1),pipeOffsetY.at(1) });
	pipe.draw();
	if (-0.9f < x && x < -0.7f)
		checkHit(true, pipeOffsetY.at(1));
	// pipe 3 (down)
	glBindTexture(GL_TEXTURE_2D, pipeDownAni.getCurrentTexture());
	getShader().write("xyoffset", { x += pipeOffsetX.at(2),-1 * pipeOffsetY.at(2) });
	pipe.draw();
	if (-0.9f < x && x < -0.7f)
		checkHit(false, pipeOffsetY.at(2));
	// pipe 2 (up)
	glBindTexture(GL_TEXTURE_2D, pipeUpAni.getCurrentTexture());
	getShader().write("xyoffset", { x += pipeOffsetX.at(1),pipeOffsetY.at(1) });
	pipe.draw();
	if (-0.9f < x && x < -0.7f)
		checkHit(true, pipeOffsetY.at(1));
	// pipe 3 (down)
	glBindTexture(GL_TEXTURE_2D, pipeDownAni.getCurrentTexture());
	getShader().write("xyoffset", { x += pipeOffsetX.at(2),-1 * pipeOffsetY.at(2) });
	pipe.draw();
	if (-0.9f < x && x < -0.7f)
		checkHit(false, pipeOffsetY.at(2));

	// draw score
	getShader().write("xyoffset", { 0.0f,0.5f });
	getShader().write("xyoffset_tex", { 0.0f,0.0f });
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, scoreAni.getCurrentTexture());
	score.draw();
}

void FlappyBird::tick()
{
	// anti-physics code
	birdVelocity -= 0.001f;
	birdY += birdVelocity;

	if (birdY <= -1.0f)
	{
		std::cout << "Game Over!" << std::endl;
		exit();
	}

	// pipe move
	pipeMarkX -= 0.017f;
	if (pipeMarkX <= -6.5f)
	{
		pipeMarkX = 1.0f;
		rerollPipeDistance();
		rerollPipeHeight();
	}

	if (hit)
	{
		std::cout << "hit!\n";
		exit();
	}
}
