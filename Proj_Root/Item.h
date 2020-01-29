#pragma once
#include <string>
#include "json.hpp"
#include <glm/glm.hpp>
#include <array>

using namespace std;


struct Item {
    string name;
    std::array<float, 4> color;
};