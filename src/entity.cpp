#include "../include/entity.hpp"
#include <iostream>

Entity::Entity(const char *filepath, SDL_Rect pos_size, SDL_Renderer *renderer, std::string original_direction, std::string heart_state) {
    this->texture = IMG_LoadTexture(renderer, filepath);
    this->pos_size = pos_size;
    this->original_direction = original_direction;
    this->heart_state = heart_state;
}

void Entity::Update(const char *filepath, SDL_Renderer *renderer) {
    this->texture = IMG_LoadTexture(renderer, filepath);
}

Entity::~Entity() {
    SDL_DestroyTexture(this->texture);
}