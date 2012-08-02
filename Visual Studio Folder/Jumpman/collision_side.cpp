/* File Name: collision_side.cpp
 * Author: Kayne Ruse
 * Date: ...
 * Copyright: (c) Kayne Ruse 2012
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * Description:
 *     ...
*/
#include <stdexcept>
#include <algorithm>
#include "collision_side.h"
using std::min;

//-------------------------
//Preprocessor directives
//-------------------------

#define DISTANCE_ABOVE (otherBox.y + otherBox.h - myBox.y)
#define DISTANCE_BELOW (myBox.y + myBox.h - otherBox.y)
#define DISTANCE_LEFT  (otherBox.x + otherBox.w - myBox.x)
#define DISTANCE_RIGHT (myBox.x + myBox.w - otherBox.x)

//-------------------------
//Function definitions
//-------------------------

CollisionSide CheckCollision(SDL_Rect myBox, SDL_Rect otherBox) {
	//this is a duplicate, but for good reason
	if (myBox.x > otherBox.x + otherBox.w ||
		myBox.y > otherBox.y + otherBox.h ||
		otherBox.x > myBox.x + myBox.w ||
		otherBox.y > myBox.y + myBox.h)
		return CS_NONE;

	return CS_COLLISION;
}

CollisionSide CheckCollisionSide(SDL_Rect myBox, SDL_Rect otherBox) {
	if (!CheckCollision(myBox, otherBox))
		return CS_NONE;

	//check each side, and return only if true
	if (CheckCollisionAbove(myBox, otherBox))
		return CS_ABOVE;

	if (CheckCollisionBelow(myBox, otherBox))
		return CS_BELOW;

	if (CheckCollisionLeft(myBox, otherBox))
		return CS_LEFT;

	if (CheckCollisionRight(myBox, otherBox))
		return CS_RIGHT;

	//error
	throw(std::logic_error("Collision side unknown"));
}

CollisionSide CheckCollisionAbove(SDL_Rect myBox, SDL_Rect otherBox) {
	if (!CheckCollision(myBox, otherBox))
		return CS_NONE;

	if (DISTANCE_ABOVE <= DISTANCE_BELOW && DISTANCE_ABOVE <= min(DISTANCE_LEFT, DISTANCE_RIGHT))
		return CS_ABOVE;

	return CS_NONE;
}

CollisionSide CheckCollisionBelow(SDL_Rect myBox, SDL_Rect otherBox) {
	if (!CheckCollision(myBox, otherBox))
		return CS_NONE;

	if (DISTANCE_BELOW <= DISTANCE_ABOVE && DISTANCE_BELOW <= min(DISTANCE_LEFT, DISTANCE_RIGHT))
		return CS_BELOW;

	return CS_NONE;
}

CollisionSide CheckCollisionLeft(SDL_Rect myBox, SDL_Rect otherBox) {
	if (!CheckCollision(myBox, otherBox))
		return CS_NONE;

	if (DISTANCE_LEFT <= DISTANCE_RIGHT && DISTANCE_LEFT <= min(DISTANCE_ABOVE, DISTANCE_BELOW))
		return CS_LEFT;

	return CS_NONE;
}

CollisionSide CheckCollisionRight(SDL_Rect myBox, SDL_Rect otherBox) {
	if (!CheckCollision(myBox, otherBox))
		return CS_NONE;

	if (DISTANCE_RIGHT <= DISTANCE_LEFT && DISTANCE_RIGHT <= min(DISTANCE_ABOVE, DISTANCE_BELOW))
		return CS_RIGHT;

	return CS_NONE;
}
