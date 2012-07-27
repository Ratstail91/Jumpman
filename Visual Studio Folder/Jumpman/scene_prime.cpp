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
	m_floor.SetBBox(0, 0, 32, 32);
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

	if ( m_floor.CheckWorldBBox( m_thing.GetWorldBBox(0,0,0,1) ) ) {
		m_thing.SetMotionY( 0 );
		m_thing.SetOriginY( m_floor.GetWorldBBox().y - m_thing.GetWorldBBox().h );
	}
	else {
		m_thing.SetMotionY(.1);
	}

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
			if ( m_floor.CheckWorldBBox( m_thing.GetWorldBBox(0,0,0,1) ) ) {
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

