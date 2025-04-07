#include "engine/core/core.hpp"

int main() {
    yume::init("YUME");

    while(yume::isWindowOpen()) {
        yume::update();
    }

    yume::eExit::close();
}