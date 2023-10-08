//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#include <xsui.h>
#include <stdio.h>

void AppLoop(xsCore *core) {

    xsButton btn = xsCreateButton(
            core,(xsVec2f) {200.f, 200.f}, (xsVec2f) {80.f, 40.f},
            (xsColor) {255, 0, 0, 255},
            XSUI_BUTTON_CHANGE_COLOR_ON_HOVER | XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION |
             XSUI_BUTTON_RETRACT_ON_INTERACTION
    );
    btn.hover_resize_offset = (xsVec2f){10.f, 6.f};
    btn.hover_resize_speed = 0.5f;
    btn.interaction_resize_offset = (xsVec2f){16.f, 12.f};
    btn.interaction_resize_speed = btn.hover_resize_speed;

    xsFont *basic_font = xsCreateFont(core, "Roboto-Black.ttf", 24, (xsColor){0, 255, 0, 255}, XSUI_FONT_BLENDED);
    if (basic_font == NULL) {
        core->exit_flag = 1;
    }

    while (!core->exit_flag) {
        xsUpdateCoreState(core);
        core->exit_flag = xsEventQuitCore(core);

        xsSetBackgroundColor(core, (xsColor){255, 255, 255, 255});

        xsUpdateButtonState(&btn, core->mouse_state & 0b1);
        xsDrawButtonBody(&btn);

        xsDrawFont(basic_font, "Hello  world", (xsVec2i){50, 50});

        xsUpdateCoreRendering(core);
    }

    
    xsFreeFont(basic_font);
}

int main() {

    xsCore core;
    xsInitCore(&core, "window", (xsVec2i){300, 300}, (xsVec2i){640, 480}, 0);

    AppLoop(&core);

    xsFreeCore(&core);
    return 0;
}