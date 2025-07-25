#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL3/SDL.h>

#define NUMBER_OF_DIRECTIONS 8

typedef enum Character_Direction
{
	IDLE_WEST = 0,
	IDLE_EAST = 1,
	NORTH = 2,
	SOUTH = 3,
	EAST = 4,
	WEST = 5,
	ROLL_EAST = 6,
	ROLL_WEST = 7
}Character_Direction_e;

typedef struct Animation {
	const SDL_FRect* frames;
	int frame_count;
	int current_frame;
	float frame_timer;
	float frame_duration;
} Animation_t;

typedef struct Character {

	float current_x, current_y, previous_x, previous_y ;
	float character_width, character_height;
	float sprite_offset;
	int animation_step;
	Character_Direction_e direction;
	Character_Direction_e previous_direction;
	SDL_Texture* character_texture;

	
	Animation_t idle_east;
	Animation_t idle_west;
	Animation_t walk_north;
	Animation_t walk_south;
	Animation_t walk_east;
	Animation_t walk_west;
	Animation_t roll_west;
	Animation_t roll_east;
	Animation_t* current_animation;


}Character_t;

void stickCharacterTop(Character_t* character, float top);
void stickCharacterBottom(Character_t* character, float bottom);
void stickCharacterRight(Character_t* character, float right);
void stickCharacterLeft(Character_t* character, float left);


bool isCharacterOutOfBoundTop		 (Character_t *character, float windowBound);
bool isCharacterOutOfBoundBottom	 (Character_t * character, float windowBound);
bool isCharacterOutOfBoundLeft		 (Character_t * character, float windowBound);
bool isCharacterOutOfBoundRight		 (Character_t * character, float windowBound);




#endif // !CHARACTER_HPP
