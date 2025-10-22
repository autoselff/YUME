#include "renderer.h"

Renderer::Renderer() = default;

Renderer::~Renderer() {
    for (auto texSquare : ToRender) {
        delete texSquare;
    }
}

void Renderer::addToRender(TexSquare* texSquare) {
    if (texSquare) {
        ToRender.push_back(texSquare);
    }
}

void Renderer::renderAll() {
    for (auto texSquare : ToRender) {
        if (texSquare) {
            texSquare->simpleRender();
        }
    }
}