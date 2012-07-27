/* File Name: entity.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#include <stdexcept>
#include <algorithm>
#include "entity.h"
using namespace std;

//-------------------------
//Public access members
//-------------------------

Entity::Entity() {
	//
}

Entity::~Entity() {
	//
}

void Entity::LoadImage(const char* szFileName, Sint16 x, Sint16 y, Uint16 w, Uint16 h) {
	Image::LoadImage(szFileName, x, y, w, h);

	BBox2D::SetBBox( GetImageX(), GetImageY(), GetImageW(), GetImageH() );
}

void Entity::LoadImage(SDL_Surface* pSurface,  Sint16 x, Sint16 y, Uint16 w, Uint16 h) {
	Image::LoadImage(pSurface, x, y, w, h);

	BBox2D::SetBBox( GetImageX(), GetImageY(), GetImageW(), GetImageH() );
}

void Entity::Update(int iDelta) {
	Origin2D::Update(iDelta);

	Image::SetImageX( (Sint16)Origin2D::GetOriginX() );
	Image::SetImageY( (Sint16)Origin2D::GetOriginY() );
}

SDL_Rect Entity::GetWorldBBox(Sint16 x, Sint16 y, Sint16 w, Sint16 h) {
	/* The parameters (x, y, w, h) shift that part of the box by so many
	 * pixels. These are the "tweak" parameters, that temporarily alter
	 * THIS entity's bounding box.
	*/

	SDL_Rect myBox = BBox2D::GetWorldBBox( (Sint16)Origin2D::GetOriginX(), (Sint16)Origin2D::GetOriginY());

	//tweaks
	myBox.x += x;
	myBox.y += y;
	if (myBox.w > -w) myBox.w += w; else myBox.w = 0;
	if (myBox.h > -h) myBox.h += h; else myBox.h = 0;

	return myBox;
}

int Entity::CheckWorldBBox(SDL_Rect otherBox) {
	return BBox2D::CheckWorldBBox(otherBox, (Sint16)Origin2D::GetOriginX(), (Sint16)Origin2D::GetOriginY());
}

int Entity::CheckCollisionSide(SDL_Rect otherBox) {
	/* this figures out the position of the OTHER bbox relative to this entity
	 * 0: no collision
	 * 1: above
	 * 2: below
	 * 3: left
	 * 4: right
	*/

	if (BBox2D::CheckWorldBBox( otherBox )) return 0; //no collision, skip the rest

	SDL_Rect myBox = GetWorldBBox();

	/* above
	 * if (
	 * 		(closer to the top than the bottom) &&
	 * 		(closer to the top than the sides)
	 *		)
	 *	 	return above
	*/

	//above
	if (
		(otherBox.y + otherBox.h - myBox.y < myBox.y + myBox.h - otherBox.y) &&
		(otherBox.y + otherBox.h - myBox.y < min( otherBox.x+otherBox.w-myBox.x, myBox.x+myBox.w-otherBox.x ))
		)
		return 1;

	//below
	else if (
		(myBox.y + myBox.h - otherBox.y < otherBox.y + otherBox.h - myBox.y) &&
		(myBox.y + myBox.h - otherBox.y < min( otherBox.x+otherBox.w-myBox.x, myBox.x+myBox.w-otherBox.x ))
		)
		return 2;

	//left and right were just find-replace of top and bottom

	//left
	else if (
		(otherBox.x + otherBox.w - myBox.x < myBox.x + myBox.w - otherBox.x) &&
		(otherBox.x + otherBox.w - myBox.x < min( otherBox.y+otherBox.h-myBox.y, myBox.y+myBox.h-otherBox.y ))
		)
		return 3;

	//right
	else if (
		(myBox.x + myBox.w - otherBox.x < otherBox.x + otherBox.w - myBox.x) &&
		(myBox.x + myBox.w - otherBox.x < min( otherBox.y+otherBox.h-myBox.y, myBox.y+myBox.h-otherBox.y ))
		)
		return 4;

	else
		throw(logic_error("Collision side unknown"));
}
