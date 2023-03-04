#include "basic_physics.hpp"

#include <cmath>

flat::PhysicsObject::PhysicsObject()
{

}

flat::PhysicsObject::~PhysicsObject()
{
}

void flat::PhysicsObject::setPosition(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;
}

void flat::PhysicsObject::setVelocity(float x, float y, float z)
{
	velX = x;
	velY = y;
	velZ = z;
}

void flat::PhysicsObject::setSize(float w, float h)
{
	sizeW = w;
	sizeH = h;
}

std::array<float, 3> flat::PhysicsObject::getPosition()
{
	return std::array<float, 3>{posX, posY, posZ};
}

std::array<float, 3> flat::PhysicsObject::getVelocity()
{
	return std::array<float, 3>{velX, velY, velZ};
}

std::array<float, 2> flat::PhysicsObject::getSize()
{
	return std::array<float, 2>{sizeW, sizeH};
}

bool flat::PhysicsObject::checkImpact(PhysicsObject& obj)
{
	auto posA = getPosition();
	auto posB = obj.getPosition();
	float l1, l2, h1, h2, theta, distance;

	distance = sqrt(pow(posA[0] - posB[0], 2) + pow(posA[1] - posB[1], 2));
	theta = atan(abs(posA[0] - posB[0]) / abs(posA[1] - posA[1]));

	return false;
}

flat::TransformMap::TransformMap()
{
}

flat::TransformMap::~TransformMap()
{
}

std::array<float, 2> flat::TransformMap::transform(float x, float y)
{
	return std::array<float, 2>{x / boaderX, y / boaderY};
}
