#ifndef MOVEHANDLER_H
#define MOVEHANDLER_H

#include "Character.h"

typedef struct MoveBounds {
	float top;
	float bottom;
	float left;
	float right;
}MoveBounds_t;


void keyboardEventHandler(SDL_Event* event);
void characterUpdateMove(Character_t* character, float delta,  MoveBounds_t const*bounds, const float base_speed);


#endif // !MOVEHANDLER_H

