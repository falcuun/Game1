#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL3/SDL.h>

#define NUMBER_OF_DIRECTIONS 8


/*
TODO 3:
Add a state struct that will hold the current state of the character

For example: 

struct Character_State{
	IDLING,
	WALKING,
	ROLLING,
	ATTACKING,
	DEFENDING,
	IS_HIT
}

Each character should manage it's own state machine and it's own states. The states should change based on 
context. 
If moving keys are pressed Character = Walking
If space is pressed character = Rolling
If ctrl is pressed character = Attacking
If alt is held down character = Defending
If smacked character = Is hit

State machine, per character, should at the very least change the current_animation based on the state itself. 

Right now, animation change happens inside updateFrame. This can be renamed to updateCharacterFrame() instead. 

And the handleCharacterStateMachine() should call the updateCharacterFrame() inside, at the very end after it has gone through all the logic. 


Example state flow:

IDLING -> break (from Switch) -> updateCharacterFrame(&character, delta) -> WALKING -> break -> updateCharacterFrame() -> and so on

Example of state interruption:

IDLING -> break -> WALKING -> gets smacked -> Jump state to IS_HIT -> break -> updateCharacterFrame()

Each state should ideally check if the character is being hit, while inside that state. 
If walking, and is hit, character should stop in the current position and play IS_HIT animation.


State transitions should be ATOMIC and driven by input, events, or flags (e.g. is_hit).

TODO 1:
Create a structure for the Location on the map/screen. Something like

struct Position{
float x, float y
}

and then use this instead of raw x,y values per character. This should make the Character struct a bit cleaner.
Cause it will only have :
Position *currentPosition
Position *previousPosition

instead of 4 variabls for c_x, c_y and p_x, p_y

*/

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
