/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include<cfloat>

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <UiMgr.h>
#include <Building.h>

InputMgr::InputMgr(Engine *engine) : Mgr(engine), OIS::KeyListener(), OIS::MouseListener() {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
	deltaDesiredAltitude = 20;
	this->selectionDistanceSquaredThreshold = 10000;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
	  // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
		#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("true")));
		pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("true")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
		#endif

	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, true));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, true));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;
	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){

	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}
	mMouse->capture();
//	mTrayMgr->frameRenderingQueued(fe);

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);

}

void InputMgr::UpdateCamera(float dt){

	}

void InputMgr::UpdateVelocityAndSelection(float dt){
	keyboardTimer -= dt;
	if (mKeyboard->isKeyDown(OIS::KC_D))
	{
		engine->entityMgr->player->MoveRight(dt);
		engine->entityMgr->player->didMove = true;
	}
	else if (mKeyboard->isKeyDown(OIS::KC_A))
	{
		engine->entityMgr->player->MoveLeft(dt);
		engine->entityMgr->player->didMove = true;
	}
	else
		engine->entityMgr->player->didMove = false;
	if (mKeyboard->isKeyDown(OIS::KC_SPACE))
		engine->entityMgr->player->Jump();

}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
    if (engine->uiMgr->mTrayMgr->injectMouseMove(me)) return true;
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	std::cout << "Mouse pressed" << std::endl;
    if (engine->uiMgr->mTrayMgr->injectMouseDown(me, mid)) return true;
	if(OIS::MB_Left == mid){
		std::cout << "Left mouse press" << std::endl;
		HandleMouseSelection(me);
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
    if (engine->uiMgr->mTrayMgr->injectMouseUp(me, mid)) return true;
	return true;
}

//check if ms.width and ms.height need to be adjusted when things change
void InputMgr::HandleMouseSelection(const OIS::MouseEvent &me){
	const OIS::MouseState &ms = mMouse->getMouseState();
	int index = -1;
	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float) ms.width, ms.Y.abs/(float)ms.height);
	std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->background);
	if(result.first && (engine->entityMgr->seedCount != 0) && (!engine->entityMgr->player->isFalling)){
		std::cout << "Got Here" << std::endl;
		Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);
		float minDistanceSquared = FLT_MAX;
		float distanceSquared; //because squareroot is expensive
		for(unsigned int i = 0; i < engine->entityMgr->buildings.size(); i++){
			distanceSquared = posUnderMouse.squaredDistance(engine->entityMgr->buildings[i]->position);
			if (distanceSquared < minDistanceSquared && posUnderMouse.y < engine->entityMgr->buildings[i]->position.y + 650 && posUnderMouse.y > engine->entityMgr->buildings[i]->position.y - 650){
				index = i;
				minDistanceSquared = distanceSquared;
			}
		}
		if (index != -1)
		{
			std::cout << "Finished Loop" << std::endl;
			Building* b = engine->entityMgr->buildings[index];
			std::cout << index << std::endl;
			std::cout << "Pointer be pointing" << std::endl;
			if (posUnderMouse.x > b->position.x && !engine->entityMgr->player->IsColliding(Ogre::Vector3(b->position.x + 520, posUnderMouse.y, 0)))
			{
				std::cout << "Creating New Vine" << std::endl;
				engine->entityMgr->CreateNewVine(Ogre::Vector3(b->position.x + 520, posUnderMouse.y, 0), 0);
				std::cout << "Vine Created" << std::endl;
			}
			else if (posUnderMouse.x <= b->position.x && !engine->entityMgr->player->IsColliding(Ogre::Vector3(b->position.x - 520, posUnderMouse.y, 0)))
			{
				std::cout << "Creating New Vine" << std::endl;
				engine->entityMgr->CreateNewVine(Ogre::Vector3(b->position.x - 520, posUnderMouse.y, 0), 1);
				std::cout << "Vine Created" << std::endl;
			}
			engine->entityMgr->seedCount--;
		}
	}
}


