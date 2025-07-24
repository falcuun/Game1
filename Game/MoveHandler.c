#include "MoveHandler.h"


bool isUpKeyPressed = false;
bool isDownKeyPressed = false;
bool isLeftKeyPressed = false;
bool isRightKeyPressed = false;



void keyboardEventHandler(SDL_Event* event)
{

	if (event->type == SDL_EVENT_KEY_DOWN)
	{
		if (event->key.key == SDLK_UP) { isUpKeyPressed = true; }
		if (event->key.key == SDLK_DOWN) { isDownKeyPressed = true; }
		if (event->key.key == SDLK_LEFT) { isLeftKeyPressed = true; }
		if (event->key.key == SDLK_RIGHT) { isRightKeyPressed = true; }
	}

	if (event->type == SDL_EVENT_KEY_UP)
	{
		if (event->key.key == SDLK_UP) { isUpKeyPressed = false; }
		if (event->key.key == SDLK_DOWN) { isDownKeyPressed = false; }
		if (event->key.key == SDLK_LEFT) { isLeftKeyPressed = false; }
		if (event->key.key == SDLK_RIGHT) { isRightKeyPressed = false; }
	}

}

void characterUpdateMove(Character_t* character, float delta, MoveBounds_t const* bounds, const float base_speed)
{
	if (isUpKeyPressed)
	{
		character->current_y -= base_speed * delta;
		if (isCharacterOutOfBoundTop(character, bounds->top - character->sprite_offset))
		{

			stickCharacterTop(character, bounds->top - character->sprite_offset);
		}
		character->direction = NORTH;
	}
	if (isDownKeyPressed)
	{
		character->current_y += base_speed * delta;
		if (isCharacterOutOfBoundBottom(character, bounds->bottom - character->character_height))
		{

			stickCharacterBottom(character, bounds->bottom - character->character_height);
		}
		character->direction = SOUTH;
	}
	if (isLeftKeyPressed)
	{
		character->current_x -= base_speed * delta;
		if (isCharacterOutOfBoundLeft(character, bounds->left))
		{
			stickCharacterLeft(character, bounds->left - character->sprite_offset);
		}
		character->direction = EAST;

	}
	if (isRightKeyPressed)
	{
		character->current_x += base_speed * delta;
		if (isCharacterOutOfBoundRight(character, bounds->right - character->character_width + character->sprite_offset))
		{
			stickCharacterRight(character, bounds->right - character->character_width + character->sprite_offset);
		}
		character->direction = WEST;
	}

	if (!isRightKeyPressed && !isLeftKeyPressed && !isUpKeyPressed && !isDownKeyPressed)
	{
		character->direction = IDLE;
	}

}