//
// Created by Rudolf Vrbenský on 15/10/2023.
//

#include <xsImage.h>

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

xsImage* xsCreateImage(xsCore* core, int w, int h, xsColor color_key) {
    xsBasicImage* image = (xsBasicImage*)SDL_CreateRGBSurface(0, w, h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (image == NULL) {
        printf("ERROR: failed not create image: %s\n", SDL_GetError());
        return NULL;
    }
    xsImage* result = malloc(sizeof(xsImage));
    if (result == NULL) {
        printf("ERROR: failed not create image: memory allocation failed");
        return NULL;
    }
    result->core = core;

    result->image = image;
    result->w = w;
    result->h = h;

    result->color_key = color_key;

    return result; 
}

xsImage* xsLoadImage(xsCore* core, xsColor color_key, const char* path) {
    xsBasicImage* image = IMG_Load(path);
    if (image == NULL) {
        printf("ERROR: failed not load image: %s\n", SDL_GetError());
        return NULL;
    }
    xsImage* result = malloc(sizeof(xsImage));
    if (result == NULL) {
        printf("ERROR: failed not load image: memory allocation failed");
        return NULL;
    }

    result->core = core;

    result->image = image;
    result->w = image->w;
    result->h = image->h;

    result->color_key = color_key;


    return result;
}

void xsDrawImage(xsImage* image, xsVec2f pos) {
    SDL_Rect dstrect = (SDL_Rect){pos.x, pos.y, image->w, image->h};

    unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);

    SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_BlitSurface(image->image, NULL, copy_basic_image, NULL);
    SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

    SDL_BlitSurface(copy_basic_image, NULL, image->core->display, &dstrect);

    SDL_FreeSurface(copy_basic_image);
}

void xsDrawImageScaled(xsImage* image, xsVec2f pos, xsVec2f new_size) {
    SDL_Rect dstrect = (SDL_Rect){pos.x, pos.y, new_size.x, new_size.y};
    unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);

    SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_BlitSurface(image->image, NULL, copy_basic_image, NULL);
    SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

    SDL_BlitScaled(copy_basic_image, NULL, image->core->display, &dstrect);

    SDL_FreeSurface(copy_basic_image);
}

void xsDrawImageTo(xsImage* image, xsVec2f pos, xsImage* target) {
     SDL_Rect dstrect = (SDL_Rect){pos.x, pos.y, image->w, image->h};

    unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);

    SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_BlitSurface(image->image, NULL, copy_basic_image, NULL);
    SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

    SDL_BlitSurface(copy_basic_image, NULL, target->image, &dstrect);

    SDL_FreeSurface(copy_basic_image);
}

void xsDrawImageScaledTo(xsImage* image, xsVec2f pos, xsVec2f new_size, xsImage* target) {
    SDL_Rect dstrect = (SDL_Rect){pos.x, pos.y, new_size.x, new_size.y};
    unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);

    SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_BlitSurface(image->image, NULL, copy_basic_image, NULL);
    SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

    SDL_BlitScaled(copy_basic_image, NULL, target->image, &dstrect);

    SDL_FreeSurface(copy_basic_image);
}

void xsFreeImage(xsImage* image) {
    SDL_FreeSurface(image->image);
    free(image);
    printf("INFO: image was freed successfully\n");
}

