//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#include <UI_elements/xsButton.h>
#include <xsCore.h>
#include <xsUtils.h>
#include <xsConstants.h>

#include <SDL.h>
#include <math.h>

xsButton xsCreateButton(xsVec2f position, xsVec2f size, xsColor color, unsigned int flags) {
    return (xsButton){
        .position = position,
        .size = size,
        .rect = (xsRect){lroundf(position.x-size.x/2.f), lroundf(position.y-size.y/2.f), lroundf(size.x), lroundf(size.y)},

        .color = color,
        .nothing_color = color,
        .hover_color = flags & XSUI_CHANGE_COLOR_ON_HOVER ? XSUI_COLOR_DARK_GRAY : XSUI_COLOR_TRANSPARENT,
        .interaction_color = flags & XSUI_CHANGE_COLOR_ON_INTERACTION ? XSUI_COLOR_LIGHT_GRAY : XSUI_COLOR_TRANSPARENT,

        .resize_offset = (xsVec2f){0.f, 0.f},

        .flags = flags,
    };
}

void xsRenderButtonBody(xsCore* core, xsButton* button) {
    xsDrawRect(core, button->rect, button->color);
}