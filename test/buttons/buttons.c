//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#include <xsui.h>

int main() {

    xsCore core;
    xsInitCore(&core, "window", (Vec2){10.f, 10.f}, (Vec2){640.f, 480.f}, 0);

    xsFreeCore(&core);
    return 0;
}