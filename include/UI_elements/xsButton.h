//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#ifndef XSUILIB_XSBUTTON_H
#define XSUILIB_XSBUTTON_H

#include <xsTypes.h>

typedef struct xsCore xsCore;

enum xsButtonState {
    XSUI_NOTHING_STATE,
    XSUI_HOVERING_OVER,
    XSUI_INTERACTION
};

enum xsButtonFlags {
    XSUI_INTERACTION_ON_CLICK = 0x1,
    XSUI_INTERACTION_ON_RELEASE = 0x2,
    XSUI_INTERACTION_ON_HOLD = 0x4,
    
    XSUI_CHANGE_COLOR_ON_HOVER = 0x8,
    XSUI_CHANGE_COLOR_ON_INTERACTION = 0x10,

    XSUI_EXPAND_ON_HOVER = 0x20,
    XSUI_EXPAND_ON_INTERACTION = 0x40,

    XSUI_RETRACT_ON_HOVER = 0x80,
    XSUI_RETRACT_ON_INTERACTION = 0x100,
};

typedef struct xsButton {
    unsigned int flags;

    xsVec2f position;
    xsVec2f size;
    xsRect rect;

    xsColor color;
    xsColor nothingColor;
    xsColor hoverColor;
    xsColor interactionColor;

    xsVec2f resizeOffset;

    enum xsButtonState state;
} xsButton;

xsButton xsCreateButton(xsVec2f position, xsVec2f size, xsColor color, unsigned int flags);

void xsRenderButtonBody(xsCore* core, xsButton* button);

#endif //XSUILIB_XSBUTTON_H
