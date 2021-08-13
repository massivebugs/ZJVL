#ifndef ZJVL_ASSET_ASSET_CACHE_H
#define ZJVL_ASSET_ASSET_CACHE_H

#include "all.h"
#include "asset.h"
#include "image.h"
#include "texture.h"

// TODO: Use a string as set id, so you can reuse it
namespace ZJVL
{
	namespace Asset
	{
		class AssetCache
		{
		public:
			template <typename T>
			std::shared_ptr<T> get(std::string path)
			{
				std::shared_ptr<T> asset;

				if (!has(path)) {
					asset = std::make_shared<T>(path);
					m_assets[path] = asset;
				}

				return asset;
			};

			bool has(std::string path)
			{
				return (m_assets.find(path) == m_assets.end()) == false;
			};

			void remove(std::string path)
			{
				if (has(path))
					m_assets.erase(path);
			};

		private:
			std::unordered_map<std::string, std::shared_ptr<Asset>> m_assets;
		};
	}
}

#endif