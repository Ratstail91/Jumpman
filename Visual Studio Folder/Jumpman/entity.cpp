/* File Name: entity.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#include "entity.h"

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
	 * 
	 * There is no error checking yet.
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
