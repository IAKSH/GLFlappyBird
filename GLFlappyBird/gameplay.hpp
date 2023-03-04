#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <array>

#include "audio.hpp"
#include "shader.hpp"
#include "drawable.hpp"
#include "animation.hpp"

namespace flat
{
	class Gameplay
	{
	private:
		flat::Shader shader;
		GLFWwindow* window = nullptr;
		ALCdevice* device = nullptr;
		ALCcontext* context = nullptr;

		void initializeShader();
		void initializeGLFW();
		void initializeGLAD();
		void initializeOpenAL();
		void bindFramebufferSizeCallback();
		void releaseGLFW();
		void releaseOpenAL();

	protected:
		flat::Shader& getShader();
		virtual void initializeDraws();
		virtual void initializeSounds();
		virtual void initializeAnimations();
		virtual void initializeAudioSources();
		virtual void initializeCustomSettings();
		virtual void handleInput(GLFWwindow* window);
		virtual void draw();
		virtual void tick();

	public:
		Gameplay();
		~Gameplay();
		void initialize();
		void mainLoop();
		void exit();
	};
}