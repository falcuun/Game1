#ifndef LOADCONFIG_H
#define LOADCONFIG_H


#include <SDL3/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

	SDL_FRect* load_animation_frames(const char* name, int* out_count);
	void free_animation_frames(SDL_FRect* frames);

#ifdef __cplusplus
}
#endif

#endif // !LOADCONFIG_H

