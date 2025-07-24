#include "Character.h"

void stickCharacterTop(Character_t* character, float top) {
	character->current_y = top;
}
void stickCharacterBottom(Character_t* character, float bottom) {
	character->current_y = bottom;
}
void stickCharacterRight(Character_t* character, float right) {
	character->current_x = right;
}
void stickCharacterLeft(Character_t* character, float left) {
	character->current_x = left;
}


bool isCharacterOutOfBoundTop(Character_t* character, float windowBound) {
	return character->current_y <= windowBound;
}
bool isCharacterOutOfBoundBottom(Character_t* character, float windowBound) {
	return character->current_y >= windowBound;
}
bool isCharacterOutOfBoundLeft(Character_t* character, float windowBound) {
	return character->current_x <= windowBound;
}
bool isCharacterOutOfBoundRight(Character_t* character, float windowBound) {
	return character->current_x >= windowBound;
}