/* File Name: scene_prime.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
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
	m_floor.SetBBox(0, 0, 32, 1000);
	m_floor.SetOriginY(GetScreen()->h-300);
}

ScenePrime::~ScenePrime() {
	//
}

//-------------------------
//Frame loop members
//-------------------------

/*
void ScenePrime::Update() {
	//simple movement downwards

	//debug...
	SDL_Rect myBox = m_thing.GetWorldBBox(0, 0, 0, 1);

	//if collision
	if (m_floor.CheckWorldBBox(  m_thing.GetWorldBBox(0,0,0,1)  )) {
		m_thing.SetMotionY( 0 );
		m_thing.SetOriginY(m_floor.GetWorldBBox().y - m_thing.GetWorldBBox().h);
	}
	else {
		cout << myBox.x << " " << myBox.y << " " << myBox.x + myBox.w << " " << myBox.y + myBox.h << endl;
		m_thing.SetMotionY(.1);
	}

	//updates
	FPSUtility::CalcDeltaTime();
	m_thing.Update(FPSUtility::GetDeltaTime());
}
//*/

/*
void ScenePrime::Update() {
	FPSUtility::CalcDeltaTime();

	/* I know this is just a prototype, but I'm really not happy with it yet.
	 * I just need to get these algorithms done, and hopefully correctly, then
	 * I can clean it up.
	* /

	//freefall control
	if (m_thing.GetMotionY() != 0) {

		//collision with platform below
		if ( m_floor.CheckCollisionSide(m_thing.GetWorldBBox(0,0,0,1)) == 2 ) {
			//stop fall, snap to platform
			m_thing.SetMotionY(0);
			m_thing.SetOriginY( m_floor.GetWorldBBox().x - m_thing.GetWorldBBox().h );
		}

		//collision with platform above
		else if ( m_floor.CheckCollisionSide(m_thing.GetWorldBBox(0,0,0,1)) == 1 ) {
			//stop fall, snap to platform
			m_thing.SetMotionY(0);
			m_thing.SetOriginY(m_floor.GetWorldBBox().x + m_floor.GetWorldBBox().h);
			m_thing.SetMotionY( ACCELERATE );
		}

		//normal fall
		else {
			//terminal velocity
			if (m_thing.GetMotionY() >= FALL) {
				m_thing.SetMotionY(FALL);
			}

			//accerlate downwards
			else {
				m_thing.ShiftMotionY(ACCELERATE);
			}
		}
	}

	//not in freefall
	else {
		//not on a platform
		if (m_floor.CheckCollisionSide(m_thing.GetWorldBBox(0,0,0,1)) != 1 ) {
			//begin falling
			m_thing.ShiftMotionY(ACCELERATE);
		}
	}

	//sideways movement control
	if (m_thing.CheckCollisionSide(m_floor.GetWorldBBox(0, 0, 1, 0)) == 3 ) {
		//collision on the left, snap to the right side and stop moving left
		m_thing.SetOriginY( m_floor.GetWorldBBox().x + m_floor.GetWorldBBox().w );
		if (m_thing.GetMotionX() < 0)
			m_thing.SetMotionX(0);
	}

	if (m_thing.CheckCollisionSide(m_floor.GetWorldBBox(-1, 0, 1, 0)) == 4 ) {
		//collision on the right, snap to the left side and stop moving right
		m_thing.SetOriginY( m_floor.GetWorldBBox().x - m_thing.GetWorldBBox().w );
		if (m_thing.GetMotionX() > 0)
			m_thing.SetMotionX(0);
	}

	m_thing.Update( FPSUtility::GetDeltaTime());
}
//*/

void ScenePrime::Update() {
	FPSUtility::CalcDeltaTime();

	//boxes
	SDL_Rect myBox = m_thing.GetWorldBBox(0, 0, 0, 1);
	SDL_Rect otherBox = m_floor.GetWorldBBox();

	if (m_thing.GetMotionY() != 0) {
		//freefall

		//cascading conditions

		if ( CheckCollisionBelow(myBox, otherBox) ) {//TODO logic error: problem with jumping...
			//land on a platform
			m_thing.SetMotionY(0);
			m_thing.SetOriginY(m_floor.GetWorldBBox().y-m_thing.GetBBoxH());
		}
		//collision above...

		else {
			//continue falling
			if (m_thing.GetMotionY() >= FALL)
				m_thing.SetMotionY(FALL);
			else
				m_thing.ShiftMotionY(ACCELERATE);
		}
	}
	else {
		//if not on a platform
		if ( !CheckCollisionBelow(myBox, otherBox) ) {
			m_thing.ShiftMotionY(ACCELERATE);
		}
	}

	//left and right movement
	//...

	//updates
	m_thing.Update(FPSUtility::GetDeltaTime());
}

void ScenePrime::Render(SDL_Surface* const pScreen) {
	SDL_FillRect(pScreen, NULL, SDL_MapRGB(pScreen->format, 0, 0, 0));

	//draw the ledge
	SDL_Rect rect = m_floor.GetWorldBBox();

	SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 0, 0));

	//draw the collision indicator
	rect.x = 400;
	rect.y = 400;
	rect.w = 40;
	rect.h = 40;

	//if it is falling, draw the square
	if (m_thing.GetMotionY() != 0)
		SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 255, 255));

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
			else
				m_thing.SetMotionX(-MOVE);

			break;

		case SDLK_RIGHT:
			if (m_thing.GetMotionX() + MOVE <= MOVE)
				m_thing.ShiftMotionX(MOVE);
			else
				m_thing.SetMotionX(MOVE);

			break;

		//debugging
		case SDLK_RETURN:
			m_thing.SetOriginPosition(0, 0);
			break;
	};
}

void ScenePrime::KeyUp(SDL_KeyboardEvent const& rKey) {
	switch(rKey.keysym.sym) {
		//sideways control
		case SDLK_LEFT:
			if (m_thing.GetMotionX() + MOVE <= MOVE)
				m_thing.ShiftMotionX(MOVE);
			else
				m_thing.SetMotionX(MOVE);

			break;

		case SDLK_RIGHT:
			if (m_thing.GetMotionX() - MOVE >= -MOVE)
				m_thing.ShiftMotionX(-MOVE);
			else
				m_thing.SetMotionX(-MOVE);

			break;
	}
}

//-------------------------
//Members
//-------------------------

//...

