#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <stdlib.h>

#include <stdio.h>
#include "Character.h"
#include "Player.h"
#include "MoveHandler.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define CHARACTER_W 64
#define CHARACTER_H 64

#define WINDOW_TOP_LIMIT (0)
#define WINDOW_BOTTOM_LIMIT (WINDOW_HEIGHT) 

#define WINDOW_LEFT_LIMIT (0)
#define WINDOW_RIGHT_LIMIT (WINDOW_WIDTH)

#define START_PLAYER_POSITION_X 0
#define START_PLAYER_POSITION_Y 0

const MoveBounds_t window_bounds = { 
.top = WINDOW_TOP_LIMIT,
.bottom = WINDOW_BOTTOM_LIMIT,
.left = WINDOW_LEFT_LIMIT,
.right = WINDOW_RIGHT_LIMIT };

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


Uint64 last_ticks = 0;

Character_t player;


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	last_ticks = SDL_GetTicks();

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	window = SDL_CreateWindow("Game", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		SDL_Log("Window failed to create");
		SDL_Quit();
	}
	SDL_PropertiesID props = SDL_CreateProperties();
	SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, window);
	SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_PRESENT_VSYNC_NUMBER, window);

	renderer = SDL_CreateRendererWithProperties(props);


	if (renderer == NULL)
	{
		SDL_Log("Renderer Failed to create");
		SDL_Quit();
	}


	SDL_SetRenderLogicalPresentation(renderer, 0, 0, SDL_LOGICAL_PRESENTATION_DISABLED);
	initPlayer(renderer, &player, START_PLAYER_POSITION_X, START_PLAYER_POSITION_Y, 12);

	return SDL_APP_CONTINUE;
}


void mouseEventHandler(SDL_Event* event)
{

	Uint64 current_event_count = 0;
	switch (event->type)
	{
	case SDL_EVENT_WINDOW_MOUSE_ENTER:
		printf("Mouse Entered\n");
		if (window != NULL && renderer != NULL)
		{


		}
		break;
	case SDL_EVENT_WINDOW_MOUSE_LEAVE:
		printf("Mouse Left\n");

		if (window != NULL && renderer != NULL)
		{
		}
		break;

	}

}


SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	keyboardEventHandler(event);
	mouseEventHandler(event);
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}
	return SDL_APP_CONTINUE;  /* carry on with the program! */
}


void drawSprite(Character_t *character)
{
	const SDL_FRect dst_rect = { character->current_x,
		character->current_y,
		CHARACTER_W,
		CHARACTER_H };

	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer,
		character->character_texture,
		&character->current_animation->frames[character->current_animation->current_frame],
		&dst_rect);
	SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	Uint64 current_ticks = SDL_GetTicks();
	float delta = (current_ticks - last_ticks) / 1000.0f;
	last_ticks = current_ticks;

	characterUpdateMove(&player,
		delta,
		&window_bounds,
		200);
	updateFrame(&player, delta);
	drawSprite(&player);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
}