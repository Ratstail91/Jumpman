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

//-------------------------
//Public access members
//-------------------------

ScenePrime::ScenePrime() {
	m_thing.LoadImage("red.bmp");
	m_floor.SetBBox(0, 0, GetScreen()->w, 100);
	m_floor.SetOriginY(GetScreen()->h);
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
	if (m_thing.GetMotionY() > 0) {
		cout << "falling; ";
		if (m_thing.CheckWorldBBox(m_floor.GetWorldBBox())) {
			//stop falling
			m_thing.SetMotionY(0);
			m_thing.SetOriginY(m_floor.GetOriginY() - m_thing.GetBBoxH() + 1);
		}
		else {
			if (m_thing.GetMotionY() >= 8)
				m_thing.SetMotionY(8);
			else
				m_thing.ShiftMotionY(.001);
		}
	}
	else {
		cout << "walking; ";
		if (m_thing.CheckWorldBBox(m_floor.GetWorldBBox())) {
			//just walking around
		}
		else {
			m_thing.SetMotionY(.001);
		}
	}

	if (m_thing.CheckWorldBBox(m_floor.GetWorldBBox())) {
		cout << "collision; ";
	}

	cout << endl; //debugging

	m_thing.Update(FPSUtility::GetDeltaTime());
}

void ScenePrime::Render(SDL_Surface* const pScreen) {
	SDL_FillRect(pScreen, NULL, SDL_MapRGB(pScreen->format, 0, 0, 0));

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

		case SDLK_SPACE:
			m_thing.ShiftMotionY(-50);
			break;
	};
}

void ScenePrime::KeyUp(SDL_KeyboardEvent const& rKey) {
	//
}

//-------------------------
//Members
//-------------------------

//...

