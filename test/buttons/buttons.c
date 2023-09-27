//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#include <xsui.h>

int main() {

    xsCore core;
    xsInitCore(&core, "window", (Vec2i){10, 10}, (Vec2i){640, 480}, 0);

    xsBasicAppLoop(&core);

    xsFreeCore(&core);
    return 0;
}