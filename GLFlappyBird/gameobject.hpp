#pragma once

#include <cinttypes>
#include <string>
#include <map>

#include "animation.hpp"
#include "drawable.hpp"
#include "audio.hpp"

namespace flat
{
	class GameObject : public flat::AnimationObject, public flat::AudioSource, public Drawable
	{
	protected:
		
	public:
		uint32_t id;
		std::string name;
		GameObject();
		~GameObject();
		void drawRaw();
	};
}