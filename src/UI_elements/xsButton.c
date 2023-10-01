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
        .original_size = size,
        .hover_resize_offset = (xsVec2f){0.f, 0.f},
        .interaction_resize_offset = (xsVec2f){0.f, 0.f},

        .hover_resize_speed = 0.f,
        .interaction_resize_speed = 0.f,

        .color = color,
        .nothing_color = color,
        .hover_color = flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER ? XSUI_COLOR_DARK_GRAY : XSUI_COLOR_TRANSPARENT,
        .interaction_color = flags & XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION ? XSUI_COLOR_LIGHT_GRAY : XSUI_COLOR_TRANSPARENT,

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
    xsDrawRect(
            button->core,
            (xsRect) {
                    lroundf(button->position.x-button->size.x/2.f),
                    lroundf(button->position.y-button->size.y/2.f),
                    lroundf(button->size.x),lroundf(button->size.y)
            },
            button->color
    );
}

void xsUpdateButtonState(xsButton* button, int interaction_starter) {
    SDL_Rect mouse_rect = {button->core->mouse_pos.x, button->core->mouse_pos.y, 1, 1};
    SDL_Rect button_rect = {
            lroundf(button->position.x-button->size.x/2.f),
            lroundf(button->position.y-button->size.y/2.f),
            lroundf(button->size.x), lroundf(button->size.y)
    };
    if (SDL_HasIntersection(&button_rect, &mouse_rect)) {
        button->state = XSUI_BUTTON_HOVERING_OVER_STATE;
        button->color = button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER ? button->hover_color : button->color;

        if (button->flags & XSUI_BUTTON_EXPAND_ON_HOVER && !interaction_starter) {
            button->size.x += ((button->original_size.x + button->hover_resize_offset.x) - button->size.x) * button->hover_resize_speed * button->core->frame_time;
            button->size.y += ((button->original_size.y + button->hover_resize_offset.y) - button->size.y) * button->hover_resize_speed * button->core->frame_time;
        } else if (button->flags & XSUI_BUTTON_RETRACT_ON_HOVER && !interaction_starter) {
            button->size.x += ((button->original_size.x - button->hover_resize_offset.x) - button->size.x) * button->hover_resize_speed * button->core->frame_time;
            button->size.y += ((button->original_size.y - button->hover_resize_offset.y) - button->size.y) * button->hover_resize_speed * button->core->frame_time;
        } else if ((button->flags & XSUI_BUTTON_EXPAND_ON_INTERACTION || button->flags & XSUI_BUTTON_RETRACT_ON_INTERACTION) && !interaction_starter) {
            button->size.x += ((button->original_size.x) - button->size.x) * button->hover_resize_speed *
                              button->core->frame_time;
            button->size.y += ((button->original_size.y) - button->size.y) * button->hover_resize_speed *
                              button->core->frame_time;
        }

        if (interaction_starter) {
            // main interaction logic
            if (!button->clicked && !button->_was_clicked) {
                button->clicked = 1;
            } else {
                button->clicked = 0;
                button->_was_clicked = 1;
            }
            button->holding = 1;
            button->state = XSUI_BUTTON_INTERACTION_STATE;

            // handling flags
            button->color = button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION ? button->interaction_color : button->color;
            if (button->flags & XSUI_BUTTON_EXPAND_ON_INTERACTION) {
                button->size.x += ((button->original_size.x + button->interaction_resize_offset.x) - button->size.x) *
                                  button->interaction_resize_speed * button->core->frame_time;
                button->size.y += ((button->original_size.y + button->interaction_resize_offset.y) - button->size.y) *
                                  button->interaction_resize_speed * button->core->frame_time;
            } else if (button->flags & XSUI_BUTTON_RETRACT_ON_INTERACTION) {
                button->size.x += ((button->original_size.x - button->interaction_resize_offset.x) - button->size.x) *
                                  button->interaction_resize_speed * button->core->frame_time;
                button->size.y += ((button->original_size.y - button->interaction_resize_offset.y) - button->size.y) *
                                  button->interaction_resize_speed * button->core->frame_time;
            }
        } else {
            button->released = button->holding ? 1 : 0;
            button->clicked = 0;
            button->_was_clicked = 0;
            button->holding = 0;
        }
    } else {
        button->state = XSUI_BUTTON_NOTHING_STATE;
        if (button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER) button->color = button->nothing_color;

        button->size.x += ((button->original_size.x) - button->size.x) * button->hover_resize_speed * button->core->frame_time;
        button->size.y += ((button->original_size.y) - button->size.y) * button->hover_resize_speed * button->core->frame_time;

    }
}