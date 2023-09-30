//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#include <UI_elements/xsButton.h>
#include <xsCore.h>
#include <xsUtils.h>
#include <xsConstants.h>

#include <SDL.h>
#include <math.h>

xsButton xsCreateButton(xsCore *core, xsVec2f position, xsVec2f size, xsColor color, unsigned int flags) {
    return (xsButton){
        .position = position,
        .size = size,
        .rect = (xsRect){lroundf(position.x-size.x/2.f), lroundf(position.y-size.y/2.f), lroundf(size.x), lroundf(size.y)},

        .color = color,
        .nothing_color = color,
        .hover_color = flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER ? XSUI_COLOR_DARK_GRAY : XSUI_COLOR_TRANSPARENT,
        .interaction_color = flags & XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION ? XSUI_COLOR_LIGHT_GRAY : XSUI_COLOR_TRANSPARENT,

        .resize_offset = (xsVec2f){0.f, 0.f},

        .clicked = 0,
        ._was_clicked = 0,

        .holding = 0,
        .released = 0,

        .flags = flags,
        .core = core,
        .state = XSUI_BUTTON_NOTHING_STATE,
    };
}

void xsDrawButtonBody(xsButton* button) {
    xsDrawRect(button->core, button->rect, button->color);
}

void xsUpdateButtonState(xsButton* button, int interaction_starter) {
    SDL_Rect mouse_rect = {button->core->mouse_pos.x, button->core->mouse_pos.y, 1, 1};
    SDL_Rect button_rect = {button->rect.x, button->rect.y, button->rect.w, button->rect.h};
    if (SDL_HasIntersection(&button_rect, &mouse_rect)) {
        button->state = XSUI_BUTTON_HOVERING_OVER_STATE;
        button->color = button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER ? button->hover_color : button->color;
        if (interaction_starter) {
            button->color = button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION ? button->interaction_color : button->color;
            if (!button->clicked && !button->_was_clicked) {
                button->clicked = 1;
            } else {
                button->clicked = 0;
                button->_was_clicked = 1;
            }
        } else {
            button->clicked = 0;
            button->_was_clicked = 0;
        }
    } else {
        button->state = XSUI_BUTTON_NOTHING_STATE;
        if (button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER) button->color = button->nothing_color;
    }
}