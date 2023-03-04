#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>

#include "audio.hpp"
#include "shader.hpp"
#include "drawable.hpp"
#include "animation.hpp"

namespace flat
{
	class Gameplay : public AudioListener
	{
	private:
		flat::Shader shader;
		GLFWwindow* window = nullptr;

		void initializeShader();
		void initializeGLFW();
		void initializeGLAD();
		void bindFramebufferSizeCallback();
		void releaseGLFW();

	protected:
		flat::Shader& getShader();
		virtual void initializeCustomSettings();
		virtual void handleInput(GLFWwindow* window);
		virtual void draw();
		virtual void tick();

	public:
		Gameplay();
		~Gameplay();
		void initializeGamePlay();
		void mainLoop();
		void exit();
	};
}