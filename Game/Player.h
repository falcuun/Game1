#ifndef PLAYER_H
#define PLAYER_H


void initPlayer(const SDL_Renderer* renderer, Character_t* player, int initial_x, int initial_y, int sprite_offset);
void initPlayerAnimations();
void updateFrame(Character_t* player, float delta);

#endif // !PLAYER_H
