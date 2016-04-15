//
// Created by inosphe on 2016. 4. 5..
//

#ifndef PROJECT_KEYMAP_H
#define PROJECT_KEYMAP_H

#include <tuple>
#include <functional>
#include <utility>

typedef std::tuple<int, int> ACTION_MAP_KEY;
typedef std::function<void()> ACTION_MAP_FUNC;
typedef std::pair<ACTION_MAP_KEY, ACTION_MAP_FUNC> ACTION_MAP_TYPE;

#endif //PROJECT_KEYMAP_H
