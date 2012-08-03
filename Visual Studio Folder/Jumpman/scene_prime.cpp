/* File Name: scene_prime.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
 * Notes:
 *     "Collisions" must incorporate both bbox.x & origin.x
 *     that is to say, something like this for falling must include GetBBoxX():
 *         player.SetOriginY( floor.getBBoxY() - player.GetBBoxH() - player.GetBBoxX() )
*/
#include <iostream>
#include "scene_prime.h"
#include "collision_side.h"
using namespace std;

//-------------------------
//Preprocessor directives
//-------------------------

#if KR_BASESCENE_H_ != 2012062701 //27/6/2012, revision 1
#error BaseScene version is incompatible with this scene
#endif

//speed controls
#define JUMP .35f
#define FALL .35f
#define MOVE .20f
#define ACCELERATE .001f

//-------------------------
//Public access members
//-------------------------

ScenePrime::ScenePrime() {
	m_thing.LoadImage("red.bmp");
	m_thing.SetOriginPosition(100, 100);

	m_floor.SetBBox(0, 0, GetScreen()->w/2, 100);
	m_floor.SetOriginPosition(100, GetScreen()->h-200);
}

ScenePrime::~ScenePrime() {
	//
}

//-------------------------
//Frame loop members
//-------------------------

void ScenePrime::Update() {
	VerticalControl(&m_thing, &m_floor);
	HorizontalControl(&m_thing, &m_floor);

	//updates
	FPSUtility::CalcDeltaTime();
	m_thing.Update(FPSUtility::GetDeltaTime());
}

void ScenePrime::Render(SDL_Surface* const pScreen) {
	SDL_FillRect(pScreen, NULL, SDL_MapRGB(pScreen->format, 0, 0, 0));

	//draw the ledge
	SDL_FillRect(pScreen, &m_floor.GetWorldBBox(), SDL_MapRGB(pScreen->format, 255, 0, 0));

/*	//draw the collision indicator
	SDL_Rect rect;

	rect.x = 400;
	rect.y = 400;
	rect.w = 40;
	rect.h = 40;

	//debug display
	if ( m_thing.GetMotionX() != 0 && CheckCollisionSide(m_thing.GetWorldBBox(), m_floor.GetWorldBBox()) ) {
		SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 255, 255));
	}
*/
	m_thing.DrawTo(pScreen);
}

//-------------------------
//Input loop members
//-------------------------

void ScenePrime::KeyDown(SDL_KeyboardEvent const& rKey) {
	switch(rKey.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
			break;

			//movement controls
		case SDLK_SPACE:
			if (m_thing.GetMotionY() == 0 && CheckCollisionBelow(m_thing.GetWorldBBox(0,0,0,1), m_floor.GetWorldBBox()) ) {
				//jump
				m_thing.SetMotionY(-JUMP);
			}
			break;

		//sideways control
		case SDLK_LEFT:
			if (m_thing.GetMotionX() - MOVE >= -MOVE)
				m_thing.ShiftMotionX(-MOVE);

			break;

		case SDLK_RIGHT:
			if (m_thing.GetMotionX() + MOVE <= MOVE)
				m_thing.ShiftMotionX(MOVE);

			break;

		//debugging
		case SDLK_RETURN:
			m_thing.SetOriginPosition(0, 0);
			m_thing.StopMotion();
			break;

		case SDLK_j:
			m_thing.ShiftMotionY(-JUMP*2);
			break;
	};
}

void ScenePrime::KeyUp(SDL_KeyboardEvent const& rKey) {
	switch(rKey.keysym.sym) {
		//sideways control
		case SDLK_LEFT:
			if (m_thing.GetMotionX() + MOVE <= 0)
				m_thing.ShiftMotionX(MOVE);
			else
				m_thing.SetMotionX(0);

			break;

		case SDLK_RIGHT:
			if (m_thing.GetMotionX() - MOVE >= 0)
				m_thing.ShiftMotionX(-MOVE);
			else
				m_thing.SetMotionX(0);

			break;
	}
}

//-------------------------
//Movement control
//-------------------------

void ScenePrime::VerticalControl(Entity* pPlayer, Entity* pWall) {
	//freefall control

	if (pPlayer->GetMotionY() > 0 && CheckCollisionBelow(pPlayer->GetWorldBBox(0,0,0,1), pWall->GetWorldBBox()) ) {
		//landing on a platform
		pPlayer->SetMotionY(0);
		pPlayer->SetOriginY(pWall->GetWorldBBox().y - pPlayer->GetBBoxH() - pPlayer->GetBBoxY());
	}
	else if (pPlayer->GetMotionY() < 0 && CheckCollisionAbove(pPlayer->GetWorldBBox(0,-1,0,1), pWall->GetWorldBBox()) ) {
		//hitting a platofrm above
//		pPlayer->SetMotionY(0);
		pPlayer->SetOriginY(pWall->GetWorldBBox().y + pWall->GetWorldBBox().h - pPlayer->GetBBoxY());
		pPlayer->SetMotionY(ACCELERATE);
	}
	else if (pPlayer->GetMotionY() != 0) {
		//freefall
		if (pPlayer->GetMotionY() >= FALL)
			pPlayer->SetMotionY(FALL);
		else
			pPlayer->ShiftMotionY(ACCELERATE);
	}
	else if (pPlayer->GetMotionY() == 0 && !CheckCollisionBelow(pPlayer->GetWorldBBox(0,0,0,1), pWall->GetWorldBBox()) ) {
		pPlayer->ShiftMotionY(ACCELERATE);
	}
}

void ScenePrime::HorizontalControl(Entity* pPlayer, Entity* pWall) {
	//collision on the left
	if ( pPlayer->GetMotionX() < 0 && CheckCollisionLeft(pPlayer->GetWorldBBox(), pWall->GetWorldBBox()) ) {
		pPlayer->SetMotionX(0);
		pPlayer->SetOriginX(pWall->GetWorldBBox().x + pWall->GetWorldBBox().w - pPlayer->GetBBoxX());
	}

	//collision on the right
	if ( pPlayer->GetMotionX() > 0 && CheckCollisionRight(pPlayer->GetWorldBBox(), pWall->GetWorldBBox()) ) {
		pPlayer->SetMotionX(0);
		pPlayer->SetOriginX(pWall->GetWorldBBox().x - pPlayer->GetWorldBBox().w - pPlayer->GetBBoxX());
	}
}

//-------------------------
//Members
//-------------------------

//...

