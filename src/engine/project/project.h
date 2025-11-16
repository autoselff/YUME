#pragma once

#include "../config/config.h"
#include "../config/essentials.h"
#include "scene.h"

class Project {
public:

    std::vector<Scene> scenes;
    Scene currentScene;

    Project();
    ~Project();
};