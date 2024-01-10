#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>

enum Direction {
    Forward,
    Backward,
    Left,
    Right,
    NO_DIRECTION_NEEDED
};

enum State {
    Heart,
    Heart_Loss,
    Boss,
    NO_STATE_NEEDED
};

char DirectionValue(Direction direction);
char StateValue(State state);

class Entity {
    public:
        SDL_Texture *texture;
        SDL_Rect pos_size;

        Direction original_direction;
        State state;

        Entity(const char *filepath, SDL_Rect pos_size, SDL_Renderer *renderer, Direction original_direction, State state);
        void Update(const char *filepath, SDL_Renderer *renderer);
        ~Entity();
};

#endif