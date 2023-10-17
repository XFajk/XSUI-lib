//
// Created by Rudolf Vrbenský on 15/10/2023.
//

#include <xsImage.h>

#include <SDL.h>
#include <SDL2_rotozoom.h>
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
        SDL_FreeSurface(image);
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
    if (image != NULL) {
        SDL_Rect dstrect = (SDL_Rect){pos.x, pos.y, image->w, image->h};

        unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);

        SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        SDL_BlitSurface(image->image, NULL, copy_basic_image, NULL);
        SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

        SDL_BlitSurface(copy_basic_image, NULL, image->core->display, &dstrect);

        SDL_FreeSurface(copy_basic_image);
    }
}

void xsDrawImageTransformed(xsImage* image, xsVec2f pos, xsVec2f new_size, float angle) {
    if (image != NULL) {
        SDL_Rect dstrect;
        unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);
        
        SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        SDL_BlitScaled(image->image, NULL, copy_basic_image, NULL);
        SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

        if (angle != 0.0) copy_basic_image = rotozoomSurface(copy_basic_image, (double)angle, 1.0, 0);
        
        dstrect = (SDL_Rect){
            (pos.x-copy_basic_image->w/2.f)+new_size.x/2.f,
            (pos.y-copy_basic_image->h/2.f)+new_size.y/2.f,
            copy_basic_image->w, copy_basic_image->h
        };
        SDL_BlitSurface(copy_basic_image, NULL, image->core->display, &dstrect);

        SDL_FreeSurface(copy_basic_image);
    }
}

void xsDrawImageTo(xsImage* image, xsVec2f pos, xsImage* target) {
    if (image != NULL || target != NULL) {
        SDL_Rect dstrect = (SDL_Rect){pos.x, pos.y, image->w, image->h};

        unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);

        SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        SDL_BlitSurface(image->image, NULL, copy_basic_image, NULL);
        SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

        SDL_BlitSurface(copy_basic_image, NULL, target->image, &dstrect);

        SDL_FreeSurface(copy_basic_image);
    }
}

void xsDrawImageTransformedTo(xsImage* image, xsVec2f pos, xsVec2f new_size, float angle, xsImage* target) {
    if (image != NULL || target != NULL) {
        SDL_Rect dstrect;
        unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);
        
        SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        SDL_BlitScaled(image->image, NULL, copy_basic_image, NULL);
        SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

        if (angle != 0.0) copy_basic_image = rotozoomSurface(copy_basic_image, (double)angle, 1.0, 0);
        
        dstrect = (SDL_Rect){
            (pos.x-copy_basic_image->w/2.f)+new_size.x/2.f,
            (pos.y-copy_basic_image->h/2.f)+new_size.y/2.f,
            copy_basic_image->w, copy_basic_image->h
        };
        SDL_BlitSurface(copy_basic_image, NULL, target->image, &dstrect);

        SDL_FreeSurface(copy_basic_image);
    }
}

xsImage* xsGetImage(xsImage* image, xsVec2f pos) {
    if (image != NULL) {
        SDL_Rect dstrect = (SDL_Rect){pos.x, pos.y, image->w, image->h};

        unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);

        SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        SDL_BlitSurface(image->image, NULL, copy_basic_image, NULL);
        SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

        SDL_BlitSurface(copy_basic_image, NULL, image->core->display, &dstrect);

        xsImage* result = malloc(sizeof(xsImage));
        if (result == NULL) {
            printf("ERROR: failed not load image: memory allocation failed");
            SDL_FreeSurface(copy_basic_image);
            return NULL;
        }

        result->core = image->core;

        result->image = copy_basic_image;
        result->w = copy_basic_image->w;
        result->h = copy_basic_image->h;

        result->color_key = image->color_key;

        return result;  
    }   
    return NULL;
}

xsImage* xsGetImageTransformed(xsImage* image, xsVec2f pos, xsVec2f new_size, float angle) {
    if (image != NULL) {
        SDL_Rect dstrect;
        unsigned int key_color = SDL_MapRGBA(image->image->format, image->color_key.r, image->color_key.g, image->color_key.b, image->color_key.a);
        
        SDL_Surface* copy_basic_image = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        SDL_BlitScaled(image->image, NULL, copy_basic_image, NULL);
        SDL_SetColorKey(copy_basic_image, SDL_TRUE, key_color);

        if (angle != 0.0) copy_basic_image = rotozoomSurface(copy_basic_image, (double)angle, 1.0, 0);
        
        dstrect = (SDL_Rect){
            (pos.x-copy_basic_image->w/2.f)+new_size.x/2.f,
            (pos.y-copy_basic_image->h/2.f)+new_size.y/2.f,
            copy_basic_image->w, copy_basic_image->h
        };
        SDL_BlitSurface(copy_basic_image, NULL, image->core->display, &dstrect);

        xsImage* result = malloc(sizeof(xsImage));
        if (result == NULL) {
            printf("ERROR: failed not load image: memory allocation failed");
            SDL_FreeSurface(copy_basic_image);
            return NULL;
        }

        result->core = image->core;

        result->image = copy_basic_image;
        result->w = copy_basic_image->w;
        result->h = copy_basic_image->h;

        result->color_key = image->color_key;

        return result; 
    }
    return NULL;
}

void xsFreeImage(xsImage* image) {
    SDL_FreeSurface(image->image);
    free(image);
    printf("INFO: image was freed successfully\n");
}

