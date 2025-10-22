#pragma once

#include "../config/config.h"
#include "texsquare.h"

class Renderer {
public:
    std::vector<TexSquare*> ToRender;

    Renderer();
    ~Renderer();

    void addToRender(TexSquare* texSquare);
    void renderAll();
};