//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#include <xsui.h>
#include <stdio.h>

int main() {

    xsCore core;
    xsInitCore(&core, "window", (xsVec2i){10, 10}, (xsVec2i){640, 480}, 0);

    xsBasicAppLoop(&core);

    xsFreeCore(&core);
    return 0;
}