#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace won
{
	namespace priv
	{
		template<class AssetT, class ReturnT>
		class AssetManagerBase
		{
		public:
			ReturnT CreateAsset(const std::string& name, const AssetT& asset);
			ReturnT GetAsset(const std::string& name);

		private:
			std::unordered_map<std::string, std::unique_ptr<AssetT>> assets;
		};
	}
}