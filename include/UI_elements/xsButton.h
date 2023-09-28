//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#ifndef XSUILIB_XSBUTTON_H
#define XSUILIB_XSBUTTON_H

#include <xsTypes.h>

typedef struct xsCore xsCore;

enum xsButtonState {
    XSUI_BUTTON_NOTHING_STATE,
    XSUI_BUTTON_HOVERING_OVER_STATE,
    XSUI_BUTTON_INTERACTION_STATE
};

enum xsButtonFlags {
    XSUI_BUTTON_INTERACTION_ON_CLICK = 0x1,
    XSUI_BUTTON_INTERACTION_ON_RELEASE = 0x2,
    XSUI_BUTTON_INTERACTION_ON_HOLD = 0x4,
    
    XSUI_BUTTON_CHANGE_COLOR_ON_HOVER = 0x8,
    XSUI_BUTTON_CHANGE_COLOR_ON_INTERACTION = 0x10,

    XSUI_BUTTON_EXPAND_ON_HOVER = 0x20,
    XSUI_BUTTON_EXPAND_ON_INTERACTION = 0x40,

    XSUI_BUTTON_RETRACT_ON_HOVER = 0x80,
    XSUI_BUTTON_RETRACT_ON_INTERACTION = 0x100,
};

typedef struct xsButton {
    unsigned int flags;
    xsCore *core;

    xsVec2f position;
    xsVec2f size;
    xsRect rect;

    xsColor color;
    xsColor nothing_color;
    xsColor hover_color;
    xsColor interaction_color;

    xsVec2f resize_offset;

    enum xsButtonState state;
} xsButton;

xsButton xsCreateButton(xsVec2f position, xsVec2f size, xsColor color, unsigned int flags, xsCore *core);

void xsRenderButtonBody(xsButton* button);

void xsUpdateButtonState(xsButton* button);

#endif //XSUILIB_XSBUTTON_H
