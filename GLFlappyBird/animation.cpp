#include "animation.hpp"

#include <iostream>
#include <format>

#include <glad/glad.h>

extern "C"
{
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
}

flat::Animation::Animation()
{
	lastUpdate = std::chrono::high_resolution_clock::now();
}

flat::Animation::Animation(std::initializer_list<std::string_view>&& pathes)
{
	loadAnimation(pathes);
	Animation();
}

flat::Animation::~Animation()
{
	glDeleteTextures(textures.size(), &textures.at(0));
}

void flat::Animation::setIntervalMS(uint32_t interval)
{
	intervalMS = interval;
}

void flat::Animation::loadAnimation(std::initializer_list<std::string_view>& pathes)
{
	auto count = pathes.size();

	stbi_set_flip_vertically_on_load(true);
	textures.resize(count);
	glGenTextures(count, &textures.at(0));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h, channels;
	unsigned char* data;
	for (int i = 0; i < count; i++)
	{
		data = stbi_load((pathes.begin() + i)->data(), &w, &h, &channels, 0);
		if (!data)
		{
			std::cerr << std::format("[ERROR] flat::Animation::load > Can't load {}", (pathes.begin() + i)->data()) << std::endl;
			abort();
		}

		glBindTexture(GL_TEXTURE_2D, textures.at(i));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
}

void flat::Animation::loadAnimation(std::initializer_list<std::string_view>&& pathes)
{
	loadAnimation(pathes);
}

void flat::Animation::checkAnimationUpdate()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastUpdate).count() >= intervalMS)
	{
		lastUpdate = std::chrono::steady_clock::now();
		if (currentIndice + 01 == textures.size())
			currentIndice = 0;
		else
			++currentIndice;
	}
}

const uint32_t& flat::Animation::getCurrentTexture()
{
	return textures.at(currentIndice);
}

flat::AnimationObject::AnimationObject()
{

}

flat::AnimationObject::~AnimationObject()
{

}

void flat::AnimationObject::loadNewAnimation(std::string_view name, uint32_t intervalMS, std::initializer_list<std::string_view>&& pathes)
{
	auto ani = std::make_shared<flat::Animation>();
	ani->loadAnimation(pathes);
	ani->setIntervalMS(intervalMS);
	animations[std::string(name)] = ani;
}

void flat::AnimationObject::removeAnimation(std::string_view name)
{
	animations.erase(std::string(name));
}

void flat::AnimationObject::loadAnimation(std::string_view name)
{
	currentAnimation = animations.find(std::string(name));
}

void flat::AnimationObject::useTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, currentAnimation->second->getCurrentTexture());
	currentAnimation->second->checkAnimationUpdate();
}

size_t flat::AnimationObject::size()
{
	return animations.size();
}
