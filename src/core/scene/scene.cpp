#include "all.h"
#include "scene.h"
#include "map.h"
#include "splash.h"
#include "entity.h"

namespace ZJVL
{
	namespace Core
	{
		Scene::Scene(){};
		Scene::Scene(Map map, Player player, std::vector<Entity> entities) : map(map), player(player), entities(entities){};

		void Scene::load(){};
		void Scene::unload(){};
		void Scene::update(std::uint32_t dt){};
		void Scene::render(){};

		void Scene::load_splash(Splash splash_image)
		{
			this->splash_images.push_back(splash_image);
		};

		void Scene::sort_entities()
		{
			return sort(entities);
		}

		void Scene::sort(std::vector<Entity> &to_sort)
		{
			// Merge sort entities just for practice
			if (to_sort.size() == 1)
				return;

			std::size_t half_idx = std::ceil((float)to_sort.size() / 2);

			// The iterator pointing to the half element of the vector
			std::vector<Entity>::iterator half_iter = to_sort.end() - (to_sort.size() - half_idx);

			// Iterators in C++ by The Cherno https://www.youtube.com/watch?v=SgcHcbQ0RCQ
			std::vector<Entity> l_half(to_sort.begin(), half_iter);
			std::vector<Entity> r_half(half_iter, to_sort.end());

			sort(l_half);
			sort(r_half);

			merge(l_half, r_half, to_sort);
		}

		void Scene::merge(std::vector<Entity> &l_vect, std::vector<Entity> &r_vect, std::vector<Entity> &merged)
		{
			std::size_t merged_idx = 0;
			std::size_t l_size = l_vect.size();
			std::size_t r_size = r_vect.size();
			std::size_t l_idx = 0;
			std::size_t r_idx = 0;

			for (merged_idx; merged_idx < merged.size(); merged_idx++)
			{
				if (l_idx == l_size)
				{
					merged[merged_idx] = r_vect[r_idx];
					r_idx++;
					continue;
				}
				else if (r_idx == r_size)
				{
					merged[merged_idx] = l_vect[l_idx];
					l_idx++;
					continue;
				}

				// compare and add the smaller size to merged
				if (l_vect[l_idx] < r_vect[r_idx])
				{
					merged[merged_idx] = l_vect[l_idx];
					l_idx++;
				}
				else
				{
					merged[merged_idx] = r_vect[r_idx];
					r_idx++;
				}
			}
		}

	}
}