#pragma once

#include <array>

namespace flat
{
	class PhysicsObject
	{
	protected:
		float posX, posY, posZ;
		float velX, velY, velZ;
		//float weight;
	public:
		PhysicsObject();
		~PhysicsObject();
		void setPosition(float x, float y, float z);
		void setVelocity(float x, float y, float z);
		std::array<float, 3> getPosition();
		std::array<float, 3> getVelocity();
	};

	class Cameral : public PhysicsObject
	{

	};

	class TransformMap
	{
	public:
		float boaderX, boaderY;
		TransformMap();
		~TransformMap();
		std::array<float, 2> transform(float x, float y);
	};
}