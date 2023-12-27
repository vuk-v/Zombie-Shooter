#include "../include/text.hpp"
#include <iostream>

Text::Text(SDL_Surface* surface_message, SDL_Rect pos_size, SDL_Renderer *renderer) {
    this->surface_message = surface_message;
    this->texture = SDL_CreateTextureFromSurface(renderer, surface_message);
    this->pos_size = pos_size;
}

Text::~Text() {
    SDL_FreeSurface(this->surface_message);
    SDL_DestroyTexture(this->texture);
}