#pragma once

#include <array>

#include "basic_physics.hpp"

namespace flat
{
	class Drawable
	{
	private:
		std::array<std::array<float, 3>, 4> vertexes;
		std::array<std::array<float, 3>, 4> colors{ 0.0f };
		std::array<std::array<float, 2>, 4> texCoords{ 1.0f,1.0f, 1.0f,0.0f ,0.0f,0.0f,0.0f,1.0f };
		uint32_t vbo, ebo, vao;
		void createVBO();
		void createEBO();
	protected:
		Drawable();
		~Drawable();
		void makeDrawMeta(std::array<float,2> size);
		void drawElements();
		void writeVertexes(std::initializer_list<float> vals);
		void writeTexCoord(std::initializer_list<float> vals);
		void writeColors(std::initializer_list<float> vals);
	};
}