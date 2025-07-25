#include "Character.h"
#include "Player.h"
#include <SDL3_image/SDL_image.h>
#include "LoadConfig.h"

Animation_t player_animationNorth;
Animation_t player_animationSouth;
Animation_t player_animationEast;
Animation_t player_animationWest;
Animation_t player_animationIdleWest;
Animation_t player_animationIdleEast;

Animation_t player_rollWest;



#define SPRITE_BASE_POSITION 0
#define SPRITE_POSITION_OFFSET 32

#define SPRITE_SHEET_COUNT 7



SDL_Surface* character_image;
SDL_Surface* character_image_flipped;

SDL_FRect* src_movement_west = NULL;
SDL_FRect* src_movement_east = NULL;
SDL_FRect* src_movement_north = NULL;
SDL_FRect* src_movement_south = NULL;
SDL_FRect* src_idle_west = NULL;
SDL_FRect* src_idle_east = NULL;

SDL_FRect* src_roll_west = NULL;

SDL_Texture* texture_right;
SDL_Texture* texture_left;

Animation_t animations[NUMBER_OF_DIRECTIONS];

void initialiseTextures(SDL_Renderer* renderer)
{
	/*
	TODO 2: The Images (SDL_Surface *character_image and character_image_flipped) should NOT live inside this file. 
			These objects need to be moved outside of this file and passed down as arguments from the main context which is loading the files. 
			That way, this class can be made more reusable for either more players, or for adding NPCs through it. 
	
	Rectangles for sprites, loaded via JSON, should LIKELY also be living elsewhere and just be passed down as arguments, where the player class 
	Just takes them as arguments. 


	Player should NOT care what the sprites are, it should just draw the sprites it's being given. 
	Drawing logic should also be moved to helper functions in a separate file, to allow for drawing of multiple characters or use through different threads. 
	
	*/
	character_image = IMG_Load("knight.png");
	character_image_flipped = IMG_Load("knight_flipped.png");

	texture_right = SDL_CreateTextureFromSurface(renderer, character_image);
	texture_left = SDL_CreateTextureFromSurface(renderer, character_image_flipped);

	SDL_free(character_image);
	SDL_free(character_image_flipped);
}


SDL_Texture* texturePicker(Character_Direction_e direction)
{
	switch (direction)
	{
	case IDLE_WEST:
	case WEST:
	case NORTH:
	case ROLL_WEST:
		return texture_right;

	case IDLE_EAST:
	case EAST:
	case SOUTH:
	case ROLL_EAST:
		return texture_left;


	default: return NULL;
	}
}

void createAnimationObject(Animation_t* animation, const SDL_FRect* frames, int frame_count, int current_frame, float frame_timer, float frame_duration)
{
	animation->frames = frames;
	animation->frame_count = frame_count;
	animation->current_frame = current_frame;
	animation->frame_timer = frame_timer;
	animation->frame_duration = frame_duration;
}


void initPlayerAnimations()
{
	// TODO 0: Do this in a loop instead of like this. 



	/*==============================SPRITES WEST=======================================*/
	int walk_west_frame_count = 0;
	src_movement_west = load_animation_frames("walk_west", &walk_west_frame_count);
	createAnimationObject(&player_animationWest, src_movement_west, 8, 0, 0, 0);

	/*==============================SPRITES EAST=======================================*/

	int walk_east_frame_count = 0;
	src_movement_east = load_animation_frames("walk_east", &walk_east_frame_count);
	createAnimationObject(&player_animationEast, src_movement_east, 8, 0, 0, 0);
	/*==============================SPRITES NORTH=======================================*/

	int walk_north_frame_count = 0;
	src_movement_north = load_animation_frames("walk_north", &walk_north_frame_count);
	createAnimationObject(&player_animationNorth, src_movement_north, 8, 0, 0, 0);

	/*==============================SPRITES SOUTH=======================================*/

	int walk_south_frame_count = 0;
	src_movement_south = load_animation_frames("walk_south", &walk_south_frame_count);
	createAnimationObject(&player_animationSouth, src_movement_south, 8, 0, 0, 0);

	/*==============================SPRITES IDLE WEST=======================================*/

	int idle_west_frame_count = 0;
	src_idle_west = load_animation_frames("idle_west", &idle_west_frame_count);
	createAnimationObject(&player_animationIdleWest, src_idle_west, 4, 0, 0, 0);

	/*==============================SPRITES IDLE EAST=======================================*/

	int idle_east_frame_count = 0;
	src_idle_east = load_animation_frames("idle_east", &idle_east_frame_count);
	createAnimationObject(&player_animationIdleEast, src_idle_east, idle_east_frame_count, 0, 0, 0);

	/*==============================SPRITES ROLL WEST=======================================*/


	int roll_west_frame_count = 0;
	src_roll_west = load_animation_frames("roll_west", &roll_west_frame_count);
	createAnimationObject(&player_rollWest, src_roll_west, roll_west_frame_count, 0, 0, 0);

	SDL_Log("Animation Initialised!");
}

void initPlayer(const SDL_Renderer* renderer, Character_t* player, int initial_x, int initial_y, int sprite_offset)
{
	player->current_x = initial_x - sprite_offset;
	player->current_y = initial_y - sprite_offset;
	player->previous_x = 0;
	player->previous_y = 0;
	player->character_width = 64;
	player->character_height = 64;
	player->sprite_offset = sprite_offset;
	player->animation_step = 0;
	player->direction = IDLE_WEST;

	initialiseTextures(renderer);
	initPlayerAnimations();



	player->character_texture = texturePicker(player->direction);

	player->walk_north = player_animationNorth;
	player->walk_south = player_animationSouth;
	player->walk_east = player_animationEast;
	player->walk_west = player_animationWest;
	player->idle_west = player_animationIdleWest;
	player->idle_east = player_animationIdleEast;
	player->roll_west = player_rollWest;

	animations[WEST] = player->walk_west;
	animations[NORTH] = player->walk_north;
	animations[EAST] = player->walk_east;
	animations[SOUTH] = player->walk_south;
	animations[IDLE_WEST] = player->idle_west;
	animations[IDLE_EAST] = player->idle_east;
	animations[ROLL_WEST] = player->roll_west;
	animations[ROLL_EAST] = player->roll_east;

	player->current_animation = &player->idle_west;
	SDL_Log("Player Initialised!");
}

void updateFrame(Character_t* player, float delta)
{

	player->current_animation = &animations[player->direction];
	player->character_texture = texturePicker(player->direction);

	player->current_animation->frame_timer += delta;
	if (player->current_animation->frame_timer >= 0.1f) {
		player->current_animation->frame_timer = 0;
		player->current_animation->current_frame++;
		if (player->current_animation->current_frame >= player->current_animation->frame_count)
			player->current_animation->current_frame = 0;
	}
}