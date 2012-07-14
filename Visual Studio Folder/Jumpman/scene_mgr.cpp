/* File Name: scene_mgr.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#include "scene_mgr.h"

//-------------------------
//Preprocessor directives
//-------------------------

#if KR_BASESCENEMGR_H_ != 2012062701 //27/6/2012, revision 1
#error BaseSceneMgr version is incompatible with SceneMgr
#endif

//-------------------------
//Scene headers
//-------------------------

#include "scene_prime.h"

//-------------------------
//Public access members
//-------------------------

//SceneMgr::SceneMgr() {
//	//
//}

//SceneMgr::~SceneMgr() {
//	//
//}

//void SceneMgr::Init() {
//	//
//}

//void SceneMgr::Proc() {
//	//
//}

//void SceneMgr::Quit() {
//	//
//}

//-------------------------
//Protected access members
//-------------------------

void SceneMgr::LoadScene() {
	delete GetScene();

	switch(GetNext()) {
		case BaseScene::SCENE_FIRST: //this is always the first scene in the game

		case SCENE_PRIME:
			SetScene( new ScenePrime() );
	}
}

//-------------------------
//SDL_main()
//-------------------------

#include <iostream>
using namespace std;

int SDL_main(int, char**) {
	SceneMgr app;

	app.Init();
	app.Proc();
	app.Quit();

	return 0;
}
