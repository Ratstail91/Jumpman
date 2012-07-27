/* File Name: entity.h
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#ifndef KR_ENTITY_H_
#define KR_ENTITY_H_

#include "image.h"
#include "origin_2d.h"
#include "bbox_2d.h"

class Entity : public Image, public Origin2D, public BBox2D {
public:
	/* Public access members */
	Entity();
	virtual ~Entity();

	virtual void LoadImage(const char* szFileName, Sint16 x=0, Sint16 y=0, Uint16 w=0, Uint16 h=0);
	virtual void LoadImage(SDL_Surface* pSurface,  Sint16 x=0, Sint16 y=0, Uint16 w=0, Uint16 h=0);

	virtual void Update(int iDelta);

	virtual SDL_Rect GetWorldBBox	(Sint16 x=0, Sint16 y=0, Sint16 w=0, Sint16 h=0);
	virtual int CheckWorldBBox		(SDL_Rect otherBox);

protected:
	/* Protected access members */
	Image::SetImageX;
	Image::SetImageY;
	Image::GetImageX;
	Image::GetImageY;
};

#endif
