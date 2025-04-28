#include <iostream>
#include <random>
#include <opencv2/opencv.hpp>
#include <SDL2/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include "../include/helper_functions.h"
#include "../include/variables.h"

int main() {


    initSDLSystems();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // (Optional) io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark(); // or your preferred theme

    // Initialize SDL2 backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer); // SDL_Window*, SDL_Renderer*
    ImGui_ImplSDLRenderer2_Init(renderer);               // SDL_Renderer*

    SDL_Event e;
    bool quit = false;

    regenColorArray();
    while (!quit) {
        frameStartTime = SDL_GetTicks();
        // Handle quit event
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_WINDOWEVENT_RESIZED) {
                regenWindowTexture();
            }
        }

        // Start the ImGui frame (for rendering ImGui content)
        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

        // ImGui window (UI components)
        ImGui::Begin("Simple Window");
        fps = (1000.0f / static_cast<float>(frameDeltaTime));
        ImGui::Text("fps: %.2f", fps);
        ImGui::End();

        if (enableFpsPrintoutToConsole) {
            std::cout << "Fps: " << fps << "\n";
            std::cout << "Mspf: " << frameDeltaTime << "\n";
        }

        // Update SDL texture with OpenCV frame (webcam feed)
        // SDL_UpdateTexture(texture, nullptr, frame.data, frame.cols * frame.channels());
        texturePixels = nullptr;
        texturePitch = 0;

        oldWindowWidth = windowWidth;
        oldWindowHeight = windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        if (oldWindowWidth != windowWidth || oldWindowHeight != windowHeight) {
            regenColorArray();
        }

        // std::uniform_real_distribution<float> distFloat(0.1f, 2.5f);
        // std::vector<uint32_t> randomColorArray(std::round(static_cast<float>(windowWidth) * distFloat(generator)));

        SDL_LockTexture(texture, NULL, &texturePixels, &texturePitch );

        uint8_t* pixels = static_cast<uint8_t*>(texturePixels);

        for (int i = 0; i < windowWidth; i++) {
            for (int j = 0; j < windowHeight; j++) {
                // int brightness = dist(generator);
                color = randomColorArray[(j * windowWidth + i) % randomColorArray.size()] ;
                r = (color >> 16) & 255;
                g = (color >> 8) & 255;
                b = (color) & 255;

                pixels[(j * windowWidth + i) * bytesPerPixel + 0] = r;
                pixels[(j * windowWidth + i) * bytesPerPixel + 1] = g;
                pixels[(j * windowWidth + i) * bytesPerPixel + 2] = b;
            }
        }

        SDL_UnlockTexture(texture);

        // TODO: add a button to ImGui to generate a random color for each pixel
        // TODO: binning of the pixels using a slider in ImGui for the size 1x1, 2x2, 3x3 etc... and actually average the value and save it to a buffer
        // TODO: after getting the pixel binning to work, display the resulting image in a new sub window that's not resizeable and has an ImGui gui button that lets you download it as idk maybe a bmp and jpeg / png later on

        // Render SDL2 content (webcam feed)
        SDL_RenderClear(renderer);  // Clear the screen (do this once)
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        // ImGui rendering on top of SDL content
        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        ImGui_ImplSDLRenderer2_RenderDrawData(draw_data, renderer);

        // Present the rendered frame
        SDL_RenderPresent(renderer);

        // update frame number
        frameNumber++;
        frameEndTime = SDL_GetTicks();
        frameDeltaTime = (frameEndTime - frameStartTime);
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}