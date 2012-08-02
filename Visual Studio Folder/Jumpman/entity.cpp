/* File Name: entity.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#include "entity.h"

//-------------------------
//Preprocessor directives
//-------------------------

#if KR_IMAGE_H_ != 2012072501 //25/7/2012, revision 1
#error Image version is incompatible with this Entity
#endif

#if KR_ORIGIN2D_H_ != 2012072501 //25/7/2012, revision 1
#error Origin2D version is incompatible with this Entity
#endif

#if KR_BBOX2D_H_ != 2012080201 //2/8/2012, revision 1
#error BBox2D version is incompatible with this Entity
#endif

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

bool Entity::CheckWorldBBox(SDL_Rect otherBox) {
	return BBox2D::CheckWorldBBox(otherBox, (Sint16)Origin2D::GetOriginX(), (Sint16)Origin2D::GetOriginY());
}
