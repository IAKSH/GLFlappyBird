#include "basic_physics.hpp"

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

std::array<float, 3> flat::PhysicsObject::getPosition()
{
	return std::array<float, 3>{posX, posY, posZ};
}

std::array<float, 3> flat::PhysicsObject::getVelocity()
{
	return std::array<float, 3>{velX, velY, velZ};
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
