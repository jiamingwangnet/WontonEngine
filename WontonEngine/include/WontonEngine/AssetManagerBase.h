#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "Error.h"
#include <iostream>

namespace won
{
	namespace priv
	{
		template<class AssetT, class ReturnT>
		class AssetManagerBase
		{
		public:
			template<class ...Args>
			ReturnT CreateAsset(const std::string& name, Args&&... args);
			ReturnT GetAsset(const std::string& name);

		private:
			std::unordered_map<std::string, std::unique_ptr<AssetT>> assets;
		};

		template<class AssetT, class ReturnT>
		template<class ...Args>
		inline ReturnT AssetManagerBase<AssetT, ReturnT>::CreateAsset(const std::string& name, Args&& ...args)
		{
			assets[name] = std::make_unique<AssetT>(std::forward<Args>(args)...);
			return (ReturnT)(assets[name].get());
		}

		template<class AssetT, class ReturnT>
		inline ReturnT AssetManagerBase<AssetT, ReturnT>::GetAsset(const std::string& name)
		{
			if (assets.find(name) == assets.end())
				Error::ThrowError("Asset does not exist.", std::cout, __LINE__, __FILE__);
			return (ReturnT)(assets[name].get());
		}
	}
}