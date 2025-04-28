//
// Created by philip on 4/27/25.
//
#include "../include/variables.h"
#include "../include/helper_functions.h"
#include <SDL_render.h>
#include <SDL_video.h>


// SDL_Window* window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
// SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
// SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

// settings
const char* windowName = "Webcam binning test";
int windowWidth = 1280;
int windowHeight = 720;
int bytesPerPixel = 3;
bool enableDebugging = true;
bool enableFpsPrintoutToConsole = false;

// basic stuff
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;

std::default_random_engine generator;
std::vector<uint32_t> randomColorArray;

// game loop variables
uint32_t frameNumber = 0;
Uint32 frameStartTime = 0;
Uint32 frameEndTime = 0;
uint32_t frameDeltaTime = 0;
float fps;
char* framerateDisplayText;
void* texturePixels;
int texturePitch;
int oldWindowWidth;
int oldWindowHeight;

// other
uint32_t color;
uint8_t r;
uint8_t g;
uint8_t b;

inline void dynamicSettings() {
    if (!enableDebugging) {
        enableFpsPrintoutToConsole = false;
    }
}