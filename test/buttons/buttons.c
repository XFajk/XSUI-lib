//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#include <xsui.h>
#include <stdio.h>

int main() {

    xsCore core;
    xsInitCore(&core, "window", (Vec2){10.f, 10.f}, (Vec2){640.f, 480.f}, 0);

    xsRunCore(&core, xsBasicGameLoop);

    xsFreeCore(&core);
    return 0;
}