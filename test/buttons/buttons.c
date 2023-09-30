//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#include <xsui.h>
#include <stdio.h>

void AppLoop(xsCore *core) {

    xsButton btn = xsCreateButton(
            core,(xsVec2f) {200.f, 200.f}, (xsVec2f) {80.f, 40.f},
            (xsColor) {255, 0, 0, 255},
            XSUI_BUTTON_CHANGE_COLOR_ON_HOVER | XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION
    );

    while (!core->exit_flag) {
        xsUpdateCoreState(core);
        core->exit_flag = xsEventQuitCore(core);

        xsSetBackgroundColor(core, (xsColor){255, 255, 255, 255});

        xsUpdateButtonState(&btn, core->mouse_state & 0b1);
        xsDrawButtonBody(&btn);

        if (btn.clicked) printf("button was clicked\n");

        xsUpdateCoreRendering(core);
    }
}

int main() {

    xsCore core;
    xsInitCore(&core, "window", (xsVec2i){10, 10}, (xsVec2i){640, 480}, 0);

    AppLoop(&core);

    xsFreeCore(&core);
    return 0;
}