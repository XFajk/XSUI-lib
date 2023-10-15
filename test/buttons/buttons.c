//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#include <xsui.h>
#include <stdio.h>

void AppLoop(xsCore *core) {

    xsButton *btn = xsCreateButton(
            core,(xsVec2f) {200.f, 200.f}, (xsVec2f) {70.f, 20.f},
            (xsColor) {255, 0, 0, 255},
            XSUI_BUTTON_CHANGE_COLOR_ON_HOVER | XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION |
             XSUI_BUTTON_RETRACT_ON_INTERACTION | XSUI_BUTTON_EXPAND_ON_HOVER
    );
    if (btn == NULL) core->exit_flag = 1;
    btn->hover_resize_offset = (xsVec2f){5.f, 3.f};
    btn->hover_resize_speed = 0.5f;
    btn->interaction_resize_offset = (xsVec2f){8.f, 6.f};
    btn->interaction_resize_speed = btn->hover_resize_speed;

    xsFont *basic_font = xsCreateFont(core, "assets/Roboto-Black.ttf", 24, (xsColor){0, 0, 0, 255}, XSUI_FONT_BLENDED);
    if (basic_font == NULL) core->exit_flag = 1;

    btn->font = xsCopyFont(basic_font);

    while (!core->exit_flag) {
        xsUpdateCoreState(core);
        core->exit_flag = xsEventQuitCore(core);

        xsSetBackgroundColor(core, (xsColor){255, 255, 255, 255});

        // TODO: add the mouse button's constants
        xsUpdateButtonState(btn, core->mouse_state & 0b1);

        xsDrawButtonBody(btn);
        xsDrawButtonText(btn, "Hello world", 0); // TODO: fix scaled

        //xsDrawFont(basic_font, "Hello  world", (xsVec2f){70.f, 70.f});

        xsUpdateCoreDisplay(core);
    }

    xsFreeButton(btn);
    xsFreeFont(basic_font);
}

int main() {

    xsCore core;
    if (xsInitCore(&core, "window", (xsVec2i){300, 300}, (xsVec2i){640, 480}, 0)) {
        return 1;
    }

    AppLoop(&core);

    xsFreeCore(&core);
    return 0;
}