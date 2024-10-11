#pragma once

#define M_WON_MAX_LIGHTS 1024
#define S_WON_MAX_LIGHTS "1024"

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif


namespace won
{
	using EntId = unsigned int;
	static constexpr unsigned int MAX_COMPONENTS = 256;
	static constexpr unsigned int MAX_ENTITIES = 65536;
	static constexpr unsigned int INVALID_ENTITY = 0xFFFFFFFF;
	static constexpr unsigned int MAX_LIGHTS = M_WON_MAX_LIGHTS;
}