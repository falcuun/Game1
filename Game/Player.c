#include "Character.h"
#include "Player.h"
#include <SDL3_image/SDL_image.h>

Animation_t player_animationNorth;
Animation_t player_animationSouth;
Animation_t player_animationEast;
Animation_t player_animationWest;
Animation_t player_idle;

#define BASE_MOVEMENET_SPRITE_POSITION 0
#define MOVEMENT_SPRITE_OFFSET 32



SDL_Surface* character_image;
SDL_Surface* character_image_flipped;

// TODO: Add a JSON with Paths to Sprites, Starting Points (x,y) and Dimensions (h,w)
// Use the NLOHMANN (or whatever) JSON library in a CPP file and return std::string().c_str(); 
// Or simply build the object inside the CPP file and return it for C to continue using it. 

const SDL_FRect src_movement_west[8] =
{
	{BASE_MOVEMENET_SPRITE_POSITION, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 1, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 2, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 3, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 4, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 5, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 6, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 7, 64, 32 ,32},
};
const SDL_FRect src_movement_east[8] =
{
	{MOVEMENT_SPRITE_OFFSET * 7, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 6, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 5, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 4, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 3, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 2, 64, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 1, 64, 32 ,32},
	{BASE_MOVEMENET_SPRITE_POSITION , 64, 32 ,32},
};
const SDL_FRect src_movement_north[8] =
{
	{MOVEMENT_SPRITE_OFFSET * 7, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 6, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 5, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 4, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 3, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 2, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 1, 96, 32 ,32},
	{BASE_MOVEMENET_SPRITE_POSITION , 96, 32 ,32},
};
const SDL_FRect src_movement_south[8] =
{
	{BASE_MOVEMENET_SPRITE_POSITION, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 1, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 2, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 3, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 4, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 5, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 6, 96, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 7, 96, 32 ,32},
};
const SDL_FRect src_idle[4] = {
	{BASE_MOVEMENET_SPRITE_POSITION, 0 , 32, 32},
	{MOVEMENT_SPRITE_OFFSET * 1, 0, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 2, 0, 32 ,32},
	{MOVEMENT_SPRITE_OFFSET * 3, 0, 32 ,32},

};

SDL_Texture* sprites[5];
Animation_t animations[5];


void initPlayerAnimations()
{
	/*==============================SPRITES WEST=======================================*/


	player_animationWest.frames = src_movement_west;
	player_animationWest.frame_count = 8;
	player_animationWest.current_frame = 0;
	player_animationWest.frame_timer = 0; // Unused for now.
	player_animationWest.frame_duration = 0; // Unused for now.

	/*==============================SPRITES EAST=======================================*/



	player_animationEast.frames = src_movement_east;
	player_animationEast.frame_count = 8;
	player_animationEast.current_frame = 0;
	player_animationEast.frame_timer = 0; // Unused for now.
	player_animationEast.frame_duration = 0; // Unused for now.

	/*==============================SPRITES NORTH=======================================*/




	player_animationNorth.frames = src_movement_north;
	player_animationNorth.frame_count = 8;
	player_animationNorth.current_frame = 0;
	player_animationNorth.frame_timer = 0; // Unused for now.
	player_animationNorth.frame_duration = 0; // Unused for now.

	/*==============================SPRITES SOUTH=======================================*/



	player_animationSouth.frames = src_movement_south;
	player_animationSouth.frame_count = 8;
	player_animationSouth.current_frame = 0;
	player_animationSouth.frame_timer = 0; // Unused for now.
	player_animationSouth.frame_duration = 0; // Unused for now.6

	/*==============================SPRITES IDLE=======================================*/


	player_idle.frames = src_idle;
	player_idle.frame_count = 4;
	player_idle.current_frame = 0;
	player_idle.frame_timer = 0;
	player_idle.frame_duration = 0;


	SDL_Log("Animation Initialised!");
}

void initPlayer(const SDL_Renderer *renderer, Character_t* player, int initial_x, int initial_y, int sprite_offset)
{
	player->current_x = initial_x - sprite_offset;
	player->current_y = initial_y - sprite_offset;
	player->previous_x = 0;
	player->previous_y = 0;
	player->character_width = 64;
	player->character_height = 64;
	player->sprite_offset = sprite_offset;
	player->animation_step = 0;
	player->direction = IDLE;

	character_image = IMG_Load("knight.png");
	character_image_flipped = IMG_Load("knight_flipped.png");

	sprites[WEST] = SDL_CreateTextureFromSurface(renderer, character_image);
	sprites[NORTH] = SDL_CreateTextureFromSurface(renderer, character_image);
	sprites[EAST] = SDL_CreateTextureFromSurface(renderer, character_image_flipped);
	sprites[SOUTH] = SDL_CreateTextureFromSurface(renderer, character_image_flipped);
	sprites[IDLE] = SDL_CreateTextureFromSurface(renderer, character_image);


	initPlayerAnimations();


	SDL_free(character_image);
	SDL_free(character_image_flipped);

	player->character_texture = sprites[WEST];

	player->walk_north = player_animationNorth;
	player->walk_south = player_animationSouth;
	player->walk_east = player_animationEast;
	player->walk_west = player_animationWest;
	player->idle = player_idle;

	animations[WEST] = player->walk_west;
	animations[NORTH] = player->walk_north;
	animations[EAST] = player->walk_east;
	animations[SOUTH] = player->walk_south;
	animations[IDLE] = player->idle;

	player->current_animation = &player->walk_west;
	SDL_Log("Player Initialised!");
}

void updateFrame(Character_t *player, float delta)
{

	player->current_animation = &animations[player->direction];
	player->character_texture = sprites[player->direction];

	player->current_animation->frame_timer += delta;
	if (player->current_animation->frame_timer >= 0.1f) {
		player->current_animation->frame_timer = 0;
		player->current_animation->current_frame++;
		if (player->current_animation->current_frame >= player->current_animation->frame_count)
			player->current_animation->current_frame = 0;
	}
}