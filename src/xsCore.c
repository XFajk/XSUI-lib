// xsCore.c
// Created by Rudolf Vrbenský on 24/09/2023.

#include <xsCore.h>
#include <xsTypes.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>

// Initializes the XSUI Core
//
// Initializes the XSUI Core, which includes setting up the SDL video subsystem,
// creating a window, and a software renderer.
//
// Parameters:
//   core: Pointer to the XSUI Core structure to be initialized.
//   win_title: The title of the window.
//   win_pos: Position of the window (Vec2 with x and y coordinates).
//   win_size: Size of the window (Vec2 with width and height).
//   win_flags: SDL window flags.
//
// Returns:
//   0 on success, 1 on failure.
char xsInitCore(xsCore *core, const char* win_title, xsVec2i win_pos, xsVec2i win_size, Uint32 win_flags) {
    core->exit_flag = 0;

    // Initialize the SDL video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("INFO: SDL initialized successfully\n");
    } else {
        printf("FATAL ERROR: SDL failed to initialize: %s\n", SDL_GetError());
        return 1;
    }

    if (!TTF_Init()) {
        printf("INFO: SDL_TTF initialized successfully\n");
    } else {
        printf("FATAL ERROR: SDL_TTF failed to initialize: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int IMG_initialized = IMG_Init(IMG_flags);
    if ((IMG_initialized & IMG_flags) == IMG_flags) {
        printf("INFO: SDL_Image initialized successfully\n");
    } else {
        printf("FATAL ERROR: SDL_Image failed to initialize: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create an SDL window
    core->window = SDL_CreateWindow(
            win_title,
            win_pos.x, win_pos.y, win_size.x, win_size.y,
            win_flags
    );
    if (core->window != NULL)
    {
        printf("INFO: SDL created window successfully\n");
    } else {
        printf("FATAL ERROR: SDL failed to create window: %s\n", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_GetWindowSize(core->window, &core->window_width, &core->window_height);

    // Create an SDL renderer
    // TODO: give the user the ability to chose the renderer flags
    core->display = SDL_GetWindowSurface(core->window);

    core->event = malloc(sizeof(xsEvent));
    int max_fail_count = 10;
    int i = 0;
    while (core->event == NULL ) {
        if (i > max_fail_count) {
            printf("FATAL ERROR: a heap allocations are failing unknown error shutting down\n");
            xsFreeCore(core);
            return 1;
        }
        SDL_Delay(500);
        printf("ERROR: a heap allocation failed trying again\n");
        core->event = malloc(sizeof(xsEvent));
        i++;
    }

    core->_last_time = SDL_GetPerformanceCounter();

    printf("\n");

    return 0;
}

// Updates the core's rendering
//
// This function presents the renderer's content to the window.
//
// Parameters:
//   core: Pointer to the XSUI Core structure.
void xsUpdateCoreDisplay(xsCore* core) {
    SDL_UpdateWindowSurface(core->window);
}

// Updates the core's state
//
// Polls for SDL events and stores them in the core's event structure plus it initializes the
// mouse and keyboard states. 
//
// Parameters:
//   core: Pointer to the XSUI Core structure.
void xsUpdateCoreState(xsCore* core) {
    SDL_PollEvent(core->event);
    core->mouse_state = SDL_GetMouseState(&core->mouse_pos.x, &core->mouse_pos.y);
    core->keyboard_state = SDL_GetKeyboardState(&core->number_of_keys);

    unsigned long currentTicks = SDL_GetPerformanceCounter();
    unsigned long frequency = SDL_GetPerformanceFrequency();

    core->frame_time= (float)(currentTicks - core->_last_time) / (float)frequency*60.f;

    core->_last_time = currentTicks;
}


// Checks if a quit event occurred
//
// Checks if the event stored in the core is a quit event (e.g., window close).
//
// Parameters:
//   core: Pointer to the XSUI Core structure.
//
// Returns:
//   1 if the event occurs and 0 if it doesn't
char xsEventQuitCore(xsCore* core) {
    return core->event->type == SDL_QUIT;
}


// Frees resources held by the XSUI Core
//
// Sets the exit_flag to 1, destroys the renderer, closes the window, and quits SDL.
//
// Parameters:
//   core: Pointer to the XSUI Core structure.
void xsFreeCore(xsCore *core) {
    core->exit_flag = 1;
    SDL_DestroyWindow(core->window);
    free(core->event);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    printf("INFO: the core object and SDL-lib were freed successfully\n");
}

