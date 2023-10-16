//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#ifndef XSUILIB_XSBUTTON_H
#define XSUILIB_XSBUTTON_H

#include <xsTypes.h>
#include <xsImage.h>
#include <xsFont.h>

typedef struct xsCore xsCore;

typedef enum xsButtonState {
    XSUI_BUTTON_NOTHING_STATE,
    XSUI_BUTTON_HOVERING_OVER_STATE,
    XSUI_BUTTON_INTERACTION_STATE
} xsButtonState;

typedef enum xsButtonFlags {
    XSUI_BUTTON_CHANGE_COLOR_ON_HOVER = 0x1,
    XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION = 0x2,

    XSUI_BUTTON_EXPAND_ON_HOVER = 0x4,
    XSUI_BUTTON_EXPAND_ON_INTERACTION = 0x8,

    XSUI_BUTTON_RETRACT_ON_HOVER = 0x10,
    XSUI_BUTTON_RETRACT_ON_INTERACTION = 0x20,
} xsButtonFlags;

typedef struct xsButton {
    unsigned int flags;
    xsCore *core;

    xsVec2f position;

    xsVec2f size;
    xsVec2f original_size;
    xsVec2f hover_resize_offset;
    xsVec2f interaction_resize_offset;

    float hover_resize_speed;
    float interaction_resize_speed;

    xsColor color;
    xsColor nothing_color;
    xsColor hover_color;
    xsColor interaction_color;

    xsFont *font;

    xsImage* image;

    char clicked;
    char _was_clicked;

    char holding;
    char released;

    enum xsButtonState state;
} xsButton;

xsButton* xsCreateButton(xsCore *core, xsVec2f position, xsVec2f size, xsColor color, unsigned int flags);

void xsDrawButtonBody(xsButton* button);
void xsDrawButtonImage(xsButton* button);
void xsDrawButtonText(xsButton *button, const char* text, char scaled);

void xsUpdateButtonState(xsButton* button, int interaction_starter);

void xsFreeButton(xsButton *button);

#endif //XSUILIB_XSBUTTON_H
