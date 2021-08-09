#include "all.h"
#include <SDL2/SDL.h>
#include "core/scene/scene.h"
#include "core/scene/map.h"
#include "core/scene/player.h"
#include "core/scene/entity.h"

class GameScene : public ZJVL::Core::Scene
{
public:
	GameScene(SDL_Renderer &renderer) : ZJVL::Core::Scene(renderer){};

	virtual void load()
	{
		std::cout << "Loading Game Scene" << std::endl;
	};

	virtual void unload()
	{
		std::cout << "Loading Game Scene" << std::endl;
	};

	virtual void update(std::uint32_t dt)
	{
		sort_entities(*entities);
	};

	virtual void render() {}

public:
	SDL_Texture *texture;
	std::shared_ptr<ZJVL::Core::Map> map;
	std::shared_ptr<ZJVL::Core::Player> player;
	std::shared_ptr<std::vector<ZJVL::Core::Entity>> entities;

private:
	void sort_entities(std::vector<ZJVL::Core::Entity> &to_sort)
	{
		// Merge sort entities just for practice
		if (to_sort.size() == 1)
			return;

		std::size_t half_idx = std::ceil((float)to_sort.size() / 2);

		// The iterator pointing to the half element of the vector
		std::vector<ZJVL::Core::Entity>::iterator half_iter = to_sort.end() - (to_sort.size() - half_idx);

		// Iterators in C++ by The Cherno https://www.youtube.com/watch?v=SgcHcbQ0RCQ
		std::vector<ZJVL::Core::Entity> l_half(to_sort.begin(), half_iter);
		std::vector<ZJVL::Core::Entity> r_half(half_iter, to_sort.end());

		sort_entities(l_half);
		sort_entities(r_half);

		merge(l_half, r_half, to_sort);
	}

	void merge(std::vector<ZJVL::Core::Entity> &l_vect, std::vector<ZJVL::Core::Entity> &r_vect, std::vector<ZJVL::Core::Entity> &merged)
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
};