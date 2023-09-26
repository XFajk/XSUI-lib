// xsCore.c
// Created by Rudolf Vrbenský on 24/09/2023.

#include <xsCore.h>
#include <xsMath.h>

#include <SDL.h>
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
char xsInitCore(xsCore *core, const char* win_title, Vec2 win_pos, Vec2 win_size, Uint32 win_flags) {
    // Initialize the SDL video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("INFO: SDL initialized successfully\n");
    } else {
        printf("ERROR: SDL failed to initialize: %s\n", SDL_GetError());
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
        printf("ERROR: SDL failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create an SDL renderer
    core->renderer = SDL_CreateRenderer(core->window, -1, SDL_RENDERER_SOFTWARE);
    if (core->renderer != NULL) {
        printf("INFO: SDL created renderer successfully\n");
    } else {
        printf("ERROR: SDL failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(core->window);
        SDL_Quit();
        return 1;
    }

    return 0;
}

// Runs the XSUI Core
//
// Runs the XSUI Core main loop, executing the provided game_loop function until
// the exit_flag in the core is set to 1.
//
// Parameters:
//   core: Pointer to the XSUI Core structure.
//   game_loop: A function pointer to the game loop function.
//
// Returns:
//   Always returns 0.
char xsRunCore(xsCore *core, void (*game_loop)(xsCore *core, xsEvent *event)) {
    xsEvent event;
    while (!core->exit_flag) {
        game_loop(core, &event);
    }
    return 0;
}

// Updates the core's state
//
// This function presents the renderer's content to the window.
//
// Parameters:
//   core: Pointer to the XSUI Core structure.
void xsUpdateCoreState(xsCore* core) {
    SDL_RenderPresent(core->renderer);
}

// Frees resources held by the XSUI Core
//
// Sets the exit_flag to 1, destroys the renderer, closes the window, and quits SDL.
//
// Parameters:
//   core: Pointer to the XSUI Core structure.
void xsFreeCore(xsCore *core) {
    core->exit_flag = 1;
    SDL_DestroyRenderer(core->renderer);
    SDL_DestroyWindow(core->window);
    SDL_Quit();
}

// A basic game loop for XSUI Core
//
// This function is a simple game loop that checks for SDL_QUIT events to set the
// exit_flag when the window is closed.
//
// Parameters:
//   core: Pointer to the XSUI Core structure.
//   event: Pointer to the XSUI Event structure.
void xsBasicGameLoop(xsCore *core, xsEvent *event) {
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                core->exit_flag = 1;
                break;
            default:
                break;
        }
    }
}
