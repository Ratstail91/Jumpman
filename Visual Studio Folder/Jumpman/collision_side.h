/* File Name: collision_side.h
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
#ifndef KR_COLLISIONSIDE_H_
#define KR_COLLISIONSIDE_H_

#include "SDL.h"

enum CollisionSide {
	CS_NONE = 0,
	CS_ABOVE,
	CS_BELOW,
	CS_LEFT,
	CS_RIGHT,
	CS_COLLISION
};

CollisionSide CheckCollision		(SDL_Rect myBox, SDL_Rect otherBox);
CollisionSide CheckCollisionSide	(SDL_Rect myBox, SDL_Rect otherBox);
CollisionSide CheckCollisionAbove	(SDL_Rect myBox, SDL_Rect otherBox);
CollisionSide CheckCollisionBelow	(SDL_Rect myBox, SDL_Rect otherBox);
CollisionSide CheckCollisionLeft	(SDL_Rect myBox, SDL_Rect otherBox);
CollisionSide CheckCollisionRight	(SDL_Rect myBox, SDL_Rect otherBox);

#endif
