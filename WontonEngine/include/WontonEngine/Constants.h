#pragma once

#define M_WON_MAX_LIGHTS 128
#define S_WON_MAX_LIGHTS "128"

namespace won
{
	using EntId = unsigned int;
	static constexpr unsigned int MAX_COMPONENTS = 256;
	static constexpr unsigned int MAX_ENTITIES = 65536;
	static constexpr unsigned int INVALID_ENTITY = 0xFFFFFFFF;
	static constexpr unsigned int MAX_LIGHTS = M_WON_MAX_LIGHTS;
}