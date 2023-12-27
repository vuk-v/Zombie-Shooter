#include <iostream>
#include <format>
#include <vector>
#include <future>
#include <algorithm>

#include "../include/window.hpp"
#include "../include/entity.hpp"
#include "../include/text.hpp"

int main () {
    Window window("Zombie Survival", 500, 500);
    
    std::vector<Entity> zombies;
    std::vector<Entity> bullets;
    std::vector<Entity> hearts;

    SDL_Color black = {255, 0, 0};
    SDL_Color white = {0, 150, 0};

    TTF_Font* font = TTF_OpenFont("/home/vuk/Documents/Programming/C++/Learning/res/font/data-latin.ttf", 50);

    Text intro_text (
        TTF_RenderText_Solid(font, "Zombies!", white),
        {150, 0, 200, 100},
        window.renderer
    );

    Text end_text (
        TTF_RenderText_Solid(font, "You Failed!", white),
        {150, 0, 200, 100},
        window.renderer
    );

    Entity start_background (
        "/home/vuk/Documents/Programming/C++/Learning/res/img/screen_background.png",
        {0, 0, 500, 500},
        window.renderer,
        "",
        ""
    );

    Entity start_button (
        "/home/vuk/Documents/Programming/C++/Learning/res/img/start/start_button.png",
        {100, 200, 300, 100},
        window.renderer,
        "",
        ""
    );

    Entity restart_button (
        "/home/vuk/Documents/Programming/C++/Learning/res/img/end/restart_button.png",
        {100, 200, 300, 100},
        window.renderer,
        "",
        ""
    );

    Entity background (
        "/home/vuk/Documents/Programming/C++/Learning/res/img/background.png",
        {0, 0, 500, 500},
        window.renderer,
        "",
        ""
    );

    Entity character (
        "/home/vuk/Documents/Programming/C++/Learning/res/img/character/w.png",
        {218, 400, 64, 64},
        window.renderer,
        "",
        ""
    );

    for (int i = 0; i < 3; i++) {
        hearts.push_back(Entity (
            "/home/vuk/Documents/Programming/C++/Learning/res/img/hearts/heart.png",
            {i * 32 + 2, 0 + 2, 32, 32},
            window.renderer,
            "",
            "heart"
        ));
    }

    int int_zombies_killed = 0;
    int x_mouse, y_mouse;
    
    srand(time(NULL));
    int number = rand() % 10 + 1;

    std::string direction = "w";

    SDL_Event event;

    bool quit = false;
    bool gen = false;

    bool start_screen = true;
    bool game = false;
    bool end_screen = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (start_screen) {
                        SDL_GetMouseState(&x_mouse, &y_mouse);

                        if (x_mouse > 100 && x_mouse < 400 && y_mouse > 200 && y_mouse < 300) {
                            start_screen = false;
                            game = true;
                            gen = true;
                        }
                            
                        break;
                    } else if (end_screen) {
                        SDL_GetMouseState(&x_mouse, &y_mouse);

                        if (x_mouse > 100 && x_mouse < 400 && y_mouse > 200 && y_mouse < 300) {
                            int_zombies_killed = 0;
                            direction = "w";
                            
                            hearts.clear();
                            zombies.clear();

                            character.pos_size.x = 218;
                            character.pos_size.y = 400;

                            for (int i = 0; i < 3; i++) {
                                hearts.push_back(Entity (
                                    "/home/vuk/Documents/Programming/C++/Learning/res/img/hearts/heart.png",
                                    {i * 32 + 2, 0 + 2, 32, 32},
                                    window.renderer,
                                    "",
                                    "heart"
                                ));
                            }

                            end_screen = false;
                            game = true;
                            gen = true;
                        }
                    }

                case SDL_KEYDOWN:
                    if (game) {
                        switch (event.key.keysym.sym) {
                            case SDLK_w:
                                character.pos_size.y -= 5;
                                direction = "w";
                                break;

                            case SDLK_a:
                                character.pos_size.x -= 5;
                                direction = "a";
                                break;

                            case SDLK_s:
                                character.pos_size.y += 5;
                                direction = "s";
                                break;

                            case SDLK_d:
                                character.pos_size.x += 5;
                                direction = "d";
                                break;

                            case SDLK_h:
                                bullets.push_back(Entity (
                                    "/home/vuk/Documents/Programming/C++/Learning/res/img/bullet.png",
                                    {character.pos_size.x, character.pos_size.y, 20, 20},
                                    window.renderer,
                                    direction,
                                    ""
                                ));

                                if (direction == "w") {
                                    character.pos_size.y += 5;
                                } else if (direction == "a") {
                                    character.pos_size.x += 5;
                                } else if (direction == "s") {
                                    character.pos_size.y -= 5;
                                } else if (direction == "d") {
                                    character.pos_size.x -= 5;
                                }

                                break;
                        }
                    }
                    break;
            }
        }

        window.Clear();

        if (start_screen) {
            window.Copy(start_background.texture, start_background.pos_size);
            window.Copy(start_button.texture, start_button.pos_size);
            window.Copy(intro_text.texture, intro_text.pos_size);
        }

        if (game) {
            if (gen) {
                if (number == rand() % 100 + 1) {
                    zombies.push_back(Entity (
                        "/home/vuk/Documents/Programming/C++/Learning/res/img/zombie/north.png",
                        {rand() % 400 + 1, 60, 64, 64},
                        window.renderer,
                        "",
                        ""
                    ));
                }
            }

            character.Update(std::format("/home/vuk/Documents/Programming/C++/Learning/res/img/character/{}.png", direction).c_str(), window.renderer);

            window.Copy(background.texture, background.pos_size);
            window.Copy(character.texture, character.pos_size);

            if (zombies.size() != 0) {
                for (int i = 0; i < zombies.size() - 1; i++) {
                    if (SDL_HasIntersection(&zombies.at(i).pos_size, &character.pos_size) || zombies.at(i).pos_size.y > 500) {
                        zombies.at(i).~Entity();
                        zombies.erase(zombies.begin() + i);

                        for (int i = hearts.size() - 1; i >= 0; i--) {
                            if (hearts.at(i).heart_state == "heart") {
                                hearts.at(i).heart_state = "heart_loss";

                                if (i == 0 && hearts.at(i).heart_state == "heart_loss") {
                                    end_screen = true;
                                    game = false;
                                    gen = false;
                                }

                                break;
                            }
                        }
                    }

                    for (int j = 0; j < bullets.size(); j++) {
                        if (SDL_HasIntersection(&zombies.at(i).pos_size, &bullets.at(j).pos_size)) {
                            zombies.at(i).~Entity();
                            zombies.erase(zombies.begin() + i);

                            bullets.at(j).~Entity();
                            bullets.erase(bullets.begin() + j);

                            int_zombies_killed++;

                            continue;
                        } else if (zombies.at(i).pos_size.y > 500) {
                            zombies.at(i).~Entity();
                            zombies.erase(zombies.begin() + i);

                            continue;
                        }
                    }

                    zombies.at(i).Update("/home/vuk/Documents/Programming/C++/Learning/res/img/zombie/north.png", window.renderer);
                    window.Copy(zombies.at(i).texture, zombies.at(i).pos_size);

                    zombies.at(i).pos_size.y += 1;
                }
            }


            std::string string_zombies_killed = std::to_string(int_zombies_killed);
            char const *zombies_killed = string_zombies_killed.c_str();

            Text zombies_killed_counter (
                TTF_RenderText_Solid(font, zombies_killed, black),
                {220, 0, 50, 50},
                window.renderer
            );

            window.Copy(zombies_killed_counter.texture, zombies_killed_counter.pos_size);

            if (bullets.size() != 0) {
                for (int i = 0; i < bullets.size(); i++) {
                    if (
                        bullets.at(i).pos_size.y < 0   ||
                        bullets.at(i).pos_size.y > 500 ||
                        bullets.at(i).pos_size.x < 0   ||
                        bullets.at(i).pos_size.y > 500
                    ) {
                        bullets.at(i).~Entity();
                        bullets.erase(bullets.begin() + i);

                        continue;
                    }

                    bullets.at(i).Update("/home/vuk/Documents/Programming/C++/Learning/res/img/bullet.png", window.renderer);
                    window.Copy(bullets.at(i).texture, bullets.at(i).pos_size);

                    if (bullets.at(i).original_direction == "w") {
                        bullets.at(i).pos_size.y -= 15;
                    } else if (bullets.at(i).original_direction == "a") {
                        bullets.at(i).pos_size.x -= 15;
                    } else if (bullets.at(i).original_direction == "s") {
                        bullets.at(i).pos_size.y += 15;
                    } else if (bullets.at(i).original_direction == "d") {
                        bullets.at(i).pos_size.x += 15;
                    }
                }
            }

            if (hearts.size() != 0) {
                for (int i = 0; i < hearts.size(); i++) {
                    hearts.at(i).Update(std::format("/home/vuk/Documents/Programming/C++/Learning/res/img/hearts/{}.png", hearts.at(i).heart_state).c_str(), window.renderer);
                    window.Copy(hearts.at(i).texture, hearts.at(i).pos_size);
                }
            }
        }

        if (end_screen) {
            window.Copy(start_background.texture, start_background.pos_size);
            window.Copy(end_text.texture, end_text.pos_size);
            window.Copy(restart_button.texture, restart_button.pos_size);
        }

        window.Render();
    }

    TTF_CloseFont(font);

    return 0;
}