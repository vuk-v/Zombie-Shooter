#include "../include/entity.hpp"
#include <iostream>

char DirectionValue(Direction direction) {
    switch (direction) {
        case Forward:
            return 'w';

        case Backward:
            return 's';

        case Left:
            return 'a';

        case Right:
            return 'd';

        case NO_DIRECTION_NEEDED:
            return ' ';
    }

    return ' ';
}

char StateValue(State state) {
    switch (state) {
        case Heart:
            return 'h';

        case Heart_Loss:
            return 'l';

        case Boss:
            return 'b';

        case NO_STATE_NEEDED:
            return ' ';
    }

    return ' ';
}

Entity::Entity(const char *filepath, SDL_Rect pos_size, SDL_Renderer *renderer, Direction original_direction, State state) {
    this->texture = IMG_LoadTexture(renderer, filepath);
    this->pos_size = pos_size;
    this->original_direction = original_direction;
    this->state = state;
}

void Entity::Update(const char *filepath, SDL_Renderer *renderer) {
    this->texture = IMG_LoadTexture(renderer, filepath);
}

Entity::~Entity() {
    SDL_DestroyTexture(this->texture);
}