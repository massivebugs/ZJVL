#include "all.h"
#include "algorithms.h"
#include "scene/game_object.h"

namespace ZJVL
{
    void merge_sort_objects(std::vector<std::shared_ptr<GameObject>> &to_sort, GameObject *camera)
    {
        // Merge sort entities just for practice
        if (to_sort.size() == 1)
            return;

        std::size_t half_idx = std::ceil((float)to_sort.size() / 2);

        // The iterator pointing to the half element of the vector
        std::vector<std::shared_ptr<GameObject>>::iterator half_iter = to_sort.end() - (to_sort.size() - half_idx);

        std::vector<std::shared_ptr<GameObject>> l_half(to_sort.begin(), half_iter);
        std::vector<std::shared_ptr<GameObject>> r_half(half_iter, to_sort.end());

        merge_sort_objects(l_half, camera);
        merge_sort_objects(r_half, camera);

        merge(l_half, r_half, to_sort, camera);
    }

    void merge(std::vector<std::shared_ptr<GameObject>> &l_vect, std::vector<std::shared_ptr<GameObject>> &r_vect, std::vector<std::shared_ptr<GameObject>> &merged, GameObject *camera)
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

            if (l_vect[l_idx]->get_object_distance(*camera) > r_vect[r_idx]->get_object_distance(*camera))
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