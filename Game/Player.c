#include "Character.h"
#include "Player.h"
#include <SDL3_image/SDL_image.h>

Animation_t player_animationNorth;
Animation_t player_animationSouth;
Animation_t player_animationEast;
Animation_t player_animationWest;
Animation_t player_animationIdleWest;
Animation_t player_animationIdleEast;

#define SPRITE_BASE_POSITION 0
#define SPRITE_POSITION_OFFSET 32

#define SPRITE_SHEET_COUNT 7



SDL_Surface* character_image;
SDL_Surface* character_image_flipped;

// TODO: Add a JSON with Paths to Sprites, Starting Points (x,y) and Dimensions (h,w)
// Use the NLOHMANN (or whatever) JSON library in a CPP file and return std::string().c_str(); 
// Or simply build the object inside the CPP file and return it for C to continue using it. 

const SDL_FRect src_movement_west[8] =
{
	{SPRITE_BASE_POSITION, 64, 32 ,32},
	{SPRITE_POSITION_OFFSET * 1, 64, 32 ,32},
	{SPRITE_POSITION_OFFSET * 2, 64, 32 ,32},
	{SPRITE_POSITION_OFFSET * 3, 64, 32 ,32},
	{SPRITE_POSITION_OFFSET * 4, 64, 32 ,32},
	{SPRITE_POSITION_OFFSET * 5, 64, 32 ,32},
	{SPRITE_POSITION_OFFSET * 6, 64, 32 ,32},
	{SPRITE_POSITION_OFFSET * 7, 64, 32 ,32},
};
const SDL_FRect src_movement_east[8] =
{
	{SPRITE_BASE_POSITION, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 1, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 2, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 3, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 4, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 5, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 6, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 7, 96, 32 ,32},
};
const SDL_FRect src_movement_north[8] =
{
	{SPRITE_POSITION_OFFSET * 7, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 6, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 5, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 4, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 3, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 2, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 1, 96, 32 ,32},
	{SPRITE_BASE_POSITION , 96, 32 ,32},
};
const SDL_FRect src_movement_south[8] =
{
	{SPRITE_BASE_POSITION, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 1, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 2, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 3, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 4, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 5, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 6, 96, 32 ,32},
	{SPRITE_POSITION_OFFSET * 7, 96, 32 ,32},
};
const SDL_FRect src_idle_west[4] = {
	{SPRITE_BASE_POSITION, 0 , 32, 32},
	{SPRITE_POSITION_OFFSET * 1, 0, 32 ,32},
	{SPRITE_POSITION_OFFSET * 2, 0, 32 ,32},
	{SPRITE_POSITION_OFFSET * 3 , 0, 32 ,32},

};

const SDL_FRect src_idle_east[4] = {
	{SPRITE_POSITION_OFFSET * 7, 0 , 32, 32},
	{SPRITE_POSITION_OFFSET * 6, 0, 32 ,32},
	{SPRITE_POSITION_OFFSET * 5, 0, 32 ,32},
	{SPRITE_POSITION_OFFSET * 4, 0, 32 ,32},

};

SDL_Texture* sprites[NUMBER_OF_DIRECTIONS];
Animation_t animations[NUMBER_OF_DIRECTIONS];


void createAnimationObject(Animation_t* animation, const SDL_FRect *frames, int frame_count, int current_frame, float frame_timer, float frame_duration)
{
	animation->frames = frames;
	animation->frame_count = frame_count;
	animation->current_frame = current_frame;
	animation->frame_timer = frame_timer;
	animation->frame_duration = frame_duration;
}


void initPlayerAnimations()
{
	/*==============================SPRITES WEST=======================================*/

	createAnimationObject(&player_animationWest, src_movement_west, 8, 0, 0, 0);

	/*==============================SPRITES EAST=======================================*/

	createAnimationObject(&player_animationEast, src_movement_east, 8, 0, 0, 0);
	/*==============================SPRITES NORTH=======================================*/

	createAnimationObject(&player_animationNorth, src_movement_north, 8, 0, 0, 0);

	/*==============================SPRITES SOUTH=======================================*/

	createAnimationObject(&player_animationSouth, src_movement_south, 8, 0, 0, 0);

	/*==============================SPRITES IDLE WEST=======================================*/

	createAnimationObject(&player_animationIdleWest, src_idle_west, 4, 0, 0, 0);

	/*==============================SPRITES IDLE EAST=======================================*/

	createAnimationObject(&player_animationIdleEast, src_idle_east, 4, 0, 0, 0);

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
	player->direction = IDLE_WEST;

	character_image = IMG_Load("knight.png");
	character_image_flipped = IMG_Load("knight_flipped.png");

	sprites[WEST] = SDL_CreateTextureFromSurface(renderer, character_image);
	sprites[NORTH] = SDL_CreateTextureFromSurface(renderer, character_image);
	sprites[EAST] = SDL_CreateTextureFromSurface(renderer, character_image_flipped);
	sprites[SOUTH] = SDL_CreateTextureFromSurface(renderer, character_image_flipped);
	sprites[IDLE_WEST] = SDL_CreateTextureFromSurface(renderer, character_image);
	sprites[IDLE_EAST] = SDL_CreateTextureFromSurface(renderer, character_image_flipped);


	SDL_free(character_image);
	SDL_free(character_image_flipped);

	initPlayerAnimations();



	player->character_texture = sprites[WEST];

	player->walk_north = player_animationNorth;
	player->walk_south = player_animationSouth;
	player->walk_east = player_animationEast;
	player->walk_west = player_animationWest;
	player->idle_west = player_animationIdleWest;
	player->idle_east = player_animationIdleEast;

	animations[WEST] = player->walk_west;
	animations[NORTH] = player->walk_north;
	animations[EAST] = player->walk_east;
	animations[SOUTH] = player->walk_south;
	animations[IDLE_WEST] = player->idle_west;
	animations[IDLE_EAST] = player->idle_east;

	player->current_animation = &player->idle_west;
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