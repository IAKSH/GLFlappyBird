#pragma once

#include <string_view>
#include <cinttypes>
#include <chrono>
#include <memory>
#include <deque>
#include <map>

namespace flat
{
	// Animation & AnimationObject manage texture, not render.

	class Animation
	{
	private:
		std::deque<uint32_t> textures;
		uint32_t intervalMS = 1000;
		std::chrono::steady_clock::time_point lastUpdate;
		uint32_t currentIndice = 0;
	public:
		Animation();
		Animation(std::initializer_list<std::string_view>&& pathes);
		~Animation();
		void checkAnimationUpdate();
		void loadAnimation(std::initializer_list<std::string_view>& pathes);
		void loadAnimation(std::initializer_list<std::string_view>&& pathes);
		void setIntervalMS(uint32_t interval);
		const uint32_t& getCurrentTexture();
	};

	class AnimationObject
	{
	private:
		std::map<std::string, std::shared_ptr<flat::Animation>> animations;
		std::map<std::string, std::shared_ptr<flat::Animation>>::iterator currentAnimation;
	protected:
		AnimationObject();
		~AnimationObject();
		void loadNewAnimation(std::string_view name, uint32_t intervalMS, std::initializer_list<std::string_view>&& pathes);
		void removeAnimation(std::string_view name);
		void loadAnimation(std::string_view name);
		void useTexture();
		size_t size();
	};
}