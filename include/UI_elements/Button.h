//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#ifndef XSUILIB_BUTTON_H
#define XSUILIB_BUTTON_H

#include <xsTypes.h>

enum xsButtonState {
    XSUI_NO_INTERACTION,
    XSUI_HOVERING_OVER,
    XSUI_PRESSING
};

enum xsButtonFlags {
    XSUI_INTERACTION_ON_CLICK = 0x1,
    XSUI_INTERACTION_ON_RELEASE = 0x2,
    XSUI_INTERACTION_ON_HOLD = 0x4,
    XSUI_CHANGE_COLOR_ON_HOVER = 0x8,
    XSUI_CHANGE_COLOR_ON_INTERACTION = 0x10,
    XSUI_EXPAND_ON_HOVER = 0x20,
    XSUI_EXPAND_ON_INTERACTION = 0x40,
};

typedef struct xsButton {
    unsigned int flags;

    Vec2f position;
    Vec2f size;

    enum xsButtonState state;
} xsButton;

#endif //XSUILIB_BUTTON_H
