#ifndef ZJVL_UTIL_ALGORITHMS_H
#define ZJVL_UTIL_ALGORITHMS_H

#include "all.h"
#include "scene/game_object.h"

namespace ZJVL
{
    void merge_sort_objects(std::vector<std::shared_ptr<GameObject>> &to_sort, GameObject *camera);

    void merge(std::vector<std::shared_ptr<GameObject>> &l_vect, std::vector<std::shared_ptr<GameObject>> &r_vect, std::vector<std::shared_ptr<GameObject>> &merged, GameObject *camera);
}

#endif