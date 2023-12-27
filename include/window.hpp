#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>

class Window {
    public:
        SDL_Renderer *renderer;

        Window(const char *title, int SCREEN_WIDTH, int SCREEN_HEIGHT);
        ~Window();

        void Copy(SDL_Texture *texture, SDL_Rect s_p);
        void Render();
        void Clear();

    private:
        SDL_Window *window;
};

#endif