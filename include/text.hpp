#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

class Text {
    public:
        SDL_Surface *surface_message;
        SDL_Texture *texture;
        SDL_Rect pos_size;

        Text(SDL_Surface *surface_message, SDL_Rect pos_size, SDL_Renderer *renderer);
        ~Text();
};

#endif