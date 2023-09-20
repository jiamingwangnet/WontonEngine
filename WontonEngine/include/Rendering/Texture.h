#pragma once

#include <string>
#include "../AssetManagerBase.h"

namespace won
{
	enum class TextureWrap
	{
		Repeat,
		MirroredRepeat,
		ClampToEdge
	};

	enum class TextureFilter
	{
		Nearest = 0b0001,
		Linear = 0b0010,
		MipmapNearest = 0b0100,
		MipmapLinear = 0b1000
	};

	namespace priv
	{
		class TextureBase
		{
		public:
			TextureBase(unsigned int id);

			unsigned int GetId() const;
			unsigned int GetUnit() const;

			void BindTexture();
			void UnbindTexture();

		private:
			unsigned int id;

			static unsigned int unitCounter; // TODO: FIND BETTER SOLUTION THAN A COUNTER
			unsigned int unit = (unsigned int)-1;
		};
	}

	using Texture = priv::TextureBase*;

	class TextureManager
	{
	public:
		static Texture CreateTexture(const std::string& name, const std::string& path,
			bool mipmap = true,
			TextureWrap wrapMethod =
			TextureWrap::Repeat,
			TextureFilter magFilter = TextureFilter::Linear,
			TextureFilter minFilter = TextureFilter::MipmapNearest);

		static Texture GetTexture(const std::string& name);

	private:
		static priv::AssetManagerBase<priv::TextureBase, Texture> assetManager;
	};
}