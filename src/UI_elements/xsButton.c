//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#include <UI_elements/xsButton.h>
#include <xsCore.h>
#include <xsUtils.h>
#include <xsConstants.h>

#include <SDL.h>
#include <math.h>

xsButton xsCreateButton(xsVec2f position, xsVec2f size, xsColor color, unsigned int flags, xsCore *core) {
    return (xsButton){
        .position = position,
        .size = size,
        .rect = (xsRect){lroundf(position.x-size.x/2.f), lroundf(position.y-size.y/2.f), lroundf(size.x), lroundf(size.y)},

        .color = color,
        .nothing_color = color,
        .hover_color = flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER ? XSUI_COLOR_DARK_GRAY : XSUI_COLOR_TRANSPARENT,
        .interaction_color = flags & XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION ? XSUI_COLOR_LIGHT_GRAY : XSUI_COLOR_TRANSPARENT,

        .resize_offset = (xsVec2f){0.f, 0.f},

        .flags = flags,
        .core = core,
        .state = XSUI_BUTTON_NOTHING_STATE,
    };
}

void xsRenderButtonBody(xsButton* button) {
    xsDrawRect(button->core, button->rect, button->color);
}

void xsUpdateButtonState(xsButton* button) {
    SDL_Rect mouse_rect = {button->core->mouse_pos.x, button->core->mouse_pos.y, 1, 1};
    SDL_Rect button_rect = {button->rect.x, button->rect.y, button->rect.w, button->rect.h};
    if (SDL_HasIntersection(&button_rect, &mouse_rect)) {
        button->state = XSUI_BUTTON_HOVERING_OVER_STATE;
        button->color = button->hover_color;
        if (button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER) button->color = button->interaction_color;
        if (button->core->mouse_state[0]) {
            if (button->flags & XSUI_BUTTON_INTERACTION_ON_CLICK) {

            }
            if (button->flags & XSUI_BUTTON_INTERACTION_ON_HOLD) {
                
            }
            if (button->flags & XSUI_BUTTON_INTERACTION_ON_RELEASE) {
                
            }

        }
        
    } else {
        button->state = XSUI_BUTTON_NOTHING_STATE;
        if (button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER) button->color = button->nothing_color;
    }