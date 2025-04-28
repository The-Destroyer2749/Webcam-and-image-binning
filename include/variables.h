//
// Created by philip on 4/26/25.
//

#ifndef INIT_H
#define INIT_H

#include <SDL.h>
#include <cstdint>
#include <SDL2/SDL_stdinc.h>
#include <random>  // Add this line
#include <vector>  // Add this line


// settings
extern const char* windowName;
extern int windowWidth;
extern int windowHeight;
extern int bytesPerPixel;
extern bool enableDebugging;
extern bool enableFpsPrintoutToConsole;

// basic stuff
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;

extern std::default_random_engine generator;
extern std::vector<uint32_t> randomColorArray;

// game loop variables

extern uint32_t frameNumber;
extern Uint32 frameStartTime;
extern Uint32 frameEndTime;
extern uint32_t frameDeltaTime;
extern float fps;
extern char* framerateDisplayText;
extern void* texturePixels;
extern int texturePitch;
extern int oldWindowWidth;
extern int oldWindowHeight;

// other runtime variables
extern uint32_t color;
extern uint8_t r;
extern uint8_t g;
extern uint8_t b;

#endif //INIT_H