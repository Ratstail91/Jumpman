/* File Name: scene_prime.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#include <iostream>
#include "scene_prime.h"
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
	m_floor.SetBBox(0, 0, 100, 100);
	m_floor.SetOriginY(GetScreen()->h-300);
}

ScenePrime::~ScenePrime() {
	//
}

//-------------------------
//Frame loop members
//-------------------------

void ScenePrime::Head() {
	//
}

void ScenePrime::Tail() {
	//
}

void ScenePrime::Update() {
	FPSUtility::CalcDeltaTime();

	//better motion control than the kinect
	if (m_thing.GetMotionY() != 0) {
		//falling
		if (m_thing.CheckWorldBBox(m_floor.GetWorldBBox())) {
			//collision with the floor
			m_thing.SetMotionY(0);
			m_thing.SetOriginY(m_floor.GetOriginY() - m_thing.GetBBoxH() + 1); //snap to the floor
		}
		else {
			//freefall control
//			cout << "freefall 17 " << m_thing.GetMotionY() << endl;
			if (m_thing.GetMotionY() >= FALL) {
				m_thing.SetMotionY(FALL);
			}
			else {
				m_thing.ShiftMotionY(ACCELERATE);
			}
		}
	}
	else {
		//standing
		if (m_thing.CheckWorldBBox(m_floor.GetWorldBBox())) {
			//on a ledge, no effect
		}
		else {
			//stepped off of the ledge
			m_thing.ShiftMotionY(ACCELERATE);
		}
	}

	m_thing.Update(FPSUtility::GetDeltaTime());
}

void ScenePrime::Render(SDL_Surface* const pScreen) {
	SDL_FillRect(pScreen, NULL, SDL_MapRGB(pScreen->format, 0, 0, 0));

	//draw the ledge
	SDL_Rect rect;

	rect.x = m_floor.GetOriginX();
	rect.y = m_floor.GetOriginY();
	rect.w = m_floor.GetBBox().w;
	rect.h = m_floor.GetBBox().h;

	SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 0, 0));

	m_thing.DrawTo(pScreen);
}

//-------------------------
//Input loop members
//-------------------------

void ScenePrime::MouseMotion(SDL_MouseMotionEvent const& rMotion) {
	//
}

void ScenePrime::MouseButtonDown(SDL_MouseButtonEvent const& rButton) {
	//
}

void ScenePrime::MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	//
}

void ScenePrime::KeyDown(SDL_KeyboardEvent const& rKey) {
	switch(rKey.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
			break;

			//movement controls
		case SDLK_SPACE:
			if (m_thing.CheckWorldBBox(m_floor.GetWorldBBox())) {
				//jump
				m_thing.SetMotionY(-JUMP);
				m_thing.ShiftOriginY(-1);
			}
			break;

		case SDLK_LEFT:
			m_thing.ShiftMotionX(-MOVE);
			break;

		case SDLK_RIGHT:
			m_thing.ShiftMotionX( MOVE);
			break;

		case SDLK_RETURN:
			m_thing.SetOriginPosition(0, 0);
			break;
	};
}

void ScenePrime::KeyUp(SDL_KeyboardEvent const& rKey) {
	switch(rKey.keysym.sym) {
		case SDLK_LEFT:
			m_thing.ShiftMotionX( MOVE);
			break;

		case SDLK_RIGHT:
			m_thing.ShiftMotionX(-MOVE);
			break;
	}
}

//-------------------------
//Members
//-------------------------

//...

