//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#include <UI_elements/xsButton.h>
#include <xsCore.h>
#include <xsUtils.h>
#include <xsImage.h>
#include <xsFont.h>
#include <xsConstants.h>

#include <SDL.h>
#include <math.h>

xsButton* xsCreateButton(xsCore *core, xsVec2f position, xsVec2f size, xsColor color, unsigned int flags) {
    xsButton *btn = malloc(sizeof(xsButton));
    if (btn == NULL) {
        printf("ERROR: failed to allocate the memory for the button\n");
        return NULL;
    }
    btn->position = position;

    btn->size = size;
    btn->original_size = size;
    btn->hover_resize_offset = (xsVec2f){0.f, 0.f};
    btn->interaction_resize_offset = (xsVec2f){0.f, 0.f};

    btn->hover_resize_speed = 0.f;
    btn->interaction_resize_speed = 0.f;

    btn->color = color;
    btn->nothing_color = color;
    btn->hover_color = flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER ? XSUI_COLOR_DARK_GRAY : XSUI_COLOR_TRANSPARENT;
    btn->interaction_color = flags & XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION ? XSUI_COLOR_LIGHT_GRAY : XSUI_COLOR_TRANSPARENT;

    btn->font = NULL;

    btn->image = NULL;

    btn->clicked = 0;
    btn->_was_clicked = 0;

    btn->holding = 0;
    btn->released = 0;

    btn->flags = flags;
    btn->core = core;
    btn->state = XSUI_BUTTON_NOTHING_STATE;

    printf("INFO: the xsButton was created successfully\n");

    return btn;
}

void xsDrawButtonBody(xsButton* button) {
    xsDrawRect(
            button->core,
            (xsRect) {
                    lroundf(button->position.x-button->size.x),
                    lroundf(button->position.y-button->size.y),
                    lroundf(button->size.x*2.f),lroundf(button->size.y*2.f)
            },
            button->color
    );
}

void xsDrawButtonImage(xsButton* button) {
    xsDrawImageScaled(
        button->image,
        (xsVec2f){button->position.x-button->size.x, button->position.y-button->size.y},
        (xsVec2f){button->size.x*2.f, button->size.y*2.f}
    );
}

void xsDrawButtonText(xsButton *button, const char* text, char scaled) {
    if (button->font != NULL) {
        if (!scaled) {
            xsDrawFont(button->font, text, button->position);
        } else {
            xsDrawFontScaled(button->font, text, button->position, (xsVec2f){lroundf(button->size.x), lroundf(button->size.y)}) ;
        }
    } else {
        printf("ERROR: the buttons font was not initialized\n");
    }
}


void interaction(xsButton* button) {
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
}

void no_interaction(xsButton *button) {
    button->released = button->holding ? 1 : 0;
    button->clicked = 0;
    button->_was_clicked = 0;
    button->holding = 0;
}

void hovering(xsButton *button, int interaction_starter) {
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
}

void no_hovering(xsButton *button) {
    button->state = XSUI_BUTTON_NOTHING_STATE;
    if (button->flags & XSUI_BUTTON_CHANGE_COLOR_ON_HOVER) button->color = button->nothing_color;

    button->size.x += ((button->original_size.x) - button->size.x) * button->hover_resize_speed * button->core->frame_time;
    button->size.y += ((button->original_size.y) - button->size.y) * button->hover_resize_speed * button->core->frame_time;
}

void xsUpdateButtonState(xsButton* button, int interaction_starter) {
    SDL_Rect mouse_rect = {button->core->mouse_pos.x, button->core->mouse_pos.y, 1, 1};
    SDL_Rect button_rect = {
            lroundf(button->position.x-button->size.x),
            lroundf(button->position.y-button->size.y),
            lroundf(button->size.x*2.f), lroundf(button->size.y*2.f)
    };
    if (SDL_HasIntersection(&button_rect, &mouse_rect)) {

        hovering(button, interaction_starter);

        if (interaction_starter) interaction(button); else no_interaction(button);

    } else {
        no_hovering(button);
    }
}


void xsFreeButton(xsButton *button) {
    printf("\nINFO: the xsButton is getting freed\n");
    xsFreeFont(button->font);
    xsFreeImage(button->image);
    free(button);
    printf("INFO: the xsButton was freed successfully\n\n");
}