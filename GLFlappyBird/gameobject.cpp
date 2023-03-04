#include "gameobject.hpp"

flat::GameObject::GameObject()
{
	
}

flat::GameObject::~GameObject()
{

}

// draw basic image without position offset
void flat::GameObject::drawRaw()
{
	useTexture();
	drawElements();
}
