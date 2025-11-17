#pragma once

#include "../config/config.h"
#include "../config/essentials.h"

class Scene {
public:
    Renderer renderer;

    Scene();
    ~Scene();

    virtual void start();
    virtual void update();
    virtual void end();
};