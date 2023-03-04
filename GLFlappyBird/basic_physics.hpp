#pragma once

#include <array>

namespace flat
{
	class PhysicsObject
	{
	protected:
		float sizeW, sizeH;
		float posX, posY, posZ;
		float velX, velY, velZ;
		//float weight;
	public:
		PhysicsObject();
		~PhysicsObject();
		void setPosition(float x, float y, float z);
		void setVelocity(float x, float y, float z);
		void setSize(float w, float h);
		std::array<float, 3> getPosition();
		std::array<float, 3> getVelocity();
		std::array<float, 2> getSize();
		bool checkImpact(PhysicsObject& obj);
	};

	class Cameral : public PhysicsObject
	{

	};

	// abandoned (for now
	class TransformMap
	{
	public:
		float boaderX, boaderY;
		TransformMap();
		~TransformMap();
		std::array<float, 2> transform(float x, float y);
	};
}