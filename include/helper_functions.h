//
// Created by philip on 4/27/25.
//
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "variables.h"
#include <random>
#include <iostream>

inline void regenWindowTexture() {
    SDL_DestroyTexture(texture);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
}

inline void initSDLSystems() {
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

    // SDL init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return -1;
    }
}

inline void regenColorArray() {
    randomColorArray.resize(windowWidth * windowHeight);

    std::uniform_int_distribution<uint32_t> distInt(0, 16777215);

    for (int i = 0; i < randomColorArray.size(); i++) {
        randomColorArray[i] = distInt(generator);
    }
    std::cout << "Updated Color Array's contents; id: " << distInt(generator) << "\n";
}
/**
 * Updates the randomColorArray by recalculating the size of the array and regenerating each item with a new random color
 *
 * Takes no inputs
 */
#endif //HELPER_FUNCTIONS_H
