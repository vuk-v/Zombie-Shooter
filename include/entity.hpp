#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>

class Entity {
    public:
        SDL_Texture *texture;
        SDL_Rect pos_size;

        std::string original_direction;
        std::string heart_state;

        Entity(const char *filepath, SDL_Rect pos_size, SDL_Renderer *renderer, std::string original_direction, std::string heart_state);
        void Update(const char *filepath, SDL_Renderer *renderer);
        ~Entity();
};

#endif