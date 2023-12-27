#include "../include/window.hpp"

Window::Window(const char *title, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (this->window == NULL) {
        std::cout << SDL_GetError() << std::endl;
        return;
    } else {
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    }

    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Window::Clear() {
    SDL_RenderClear(this->renderer);
}

void Window::Copy(SDL_Texture *texture, SDL_Rect s_p) {
    SDL_RenderCopy(this->renderer, texture, NULL, &s_p);
}

void Window::Render() {
    SDL_RenderPresent(this->renderer);
}