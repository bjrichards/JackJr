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

#include <Utils.h>
#include <Command.h>
//#include <Aspect.h>
//#include <UnitAI.h>

InputMgr::InputMgr(Engine *engine) : Mgr(engine), OIS::KeyListener(), OIS::MouseListener() {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
	deltaDesiredAltitude = 20;
	this->selectionDistanceSquaredThreshold = 5000;
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
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
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

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);

}

void InputMgr::UpdateCamera(float dt){
	float move = 400.0f;
	float rotate = 0.001f;

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	 if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	 {
		 move *= 2;
	 }

	  if (mKeyboard->isKeyDown(OIS::KC_W))
	    dirVec.z -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_S))
	    dirVec.z += move;

	  if (mKeyboard->isKeyDown(OIS::KC_R))
	    dirVec.y += move;

	  if (mKeyboard->isKeyDown(OIS::KC_F))
		  if (engine->gameMgr->cameraNode->getPosition().y > 10)
			  dirVec.y -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_A))
	  {
	      dirVec.x -= move;
	  }

	  if (mKeyboard->isKeyDown(OIS::KC_D))
	  {
	      dirVec.x += move;
	  }
		if (mKeyboard->isKeyDown(OIS::KC_Q))
		{
		  engine->gameMgr->cameraNode->yaw(Ogre::Degree(5 * rotate));
		}
	  if (mKeyboard->isKeyDown(OIS::KC_E))
	  {
		  engine->gameMgr->cameraNode->yaw(Ogre::Degree(-5 * rotate));
	  }
	  if (mKeyboard->isKeyDown(OIS::KC_Z))
	  {
		  engine->gameMgr->cameraNode->pitch(Ogre::Degree(5 * rotate));
	  }
	  if (mKeyboard->isKeyDown(OIS::KC_X))
	  {
		  engine->gameMgr->cameraNode->pitch(Ogre::Degree(-5 * rotate));
	  }

	  engine->gameMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
}

void InputMgr::UpdateVelocityAndSelection(float dt){
	keyboardTimer -= dt;

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
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	std::cout << "Mouse pressed" << std::endl;
	if(OIS::MB_Left == mid){
		std::cout << "Left mouse press" << std::endl;
		HandleMouseSelection(me);
	}
	else if (OIS::MB_Right == mid){
		std::cout << "Right mouse press" << std::endl;
		HandleMouseUnitAISelection(me);
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	return true;
}

//check if ms.width and ms.height need to be adjusted when things change
void InputMgr::HandleMouseSelection(const OIS::MouseEvent &me){
//	const OIS::MouseState &ms = mMouse->getMouseState();
//	int index = -1;
//	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float) ms.width, ms.Y.abs/(float)ms.height);
//	std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
//	if(result.first){
//		Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);
//		float minDistanceSquared = FLT_MAX;
//		float distanceSquared; //because squareroot is expensive
//		for(unsigned int i = 0; i < engine->entityMgr->entities.size(); i++){
//			distanceSquared = posUnderMouse.squaredDistance(engine->entityMgr->entities[i]->position);
//			if (distanceSquared < selectionDistanceSquaredThreshold){
//				if (distanceSquared < minDistanceSquared){
//					index = i;
//					minDistanceSquared = distanceSquared;
//				}
//			}
//		}
//		engine->entityMgr->Select(index);
//	}
}

void InputMgr::HandleMouseUnitAISelection(const OIS::MouseEvent &me){
//	const OIS::MouseState &ms = mMouse->getMouseState();
//	int index = -1;
//	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float) ms.width, ms.Y.abs/(float)ms.height);
//	std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
//	bool intercept = false;
//	if(result.first){
//		Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);
//		float minDistanceSquared = FLT_MAX;
//		float distanceSquared; //because squareroot is expensive
//		for(unsigned int i = 0; i < engine->entityMgr->entities.size(); i++){
//			distanceSquared = posUnderMouse.squaredDistance(engine->entityMgr->entities[i]->position);
//			if (distanceSquared < selectionDistanceSquaredThreshold){
//				intercept = true;
//				if (distanceSquared < minDistanceSquared){
//					index = i;
//					minDistanceSquared = distanceSquared;
//				}
//			}
//		}
//		if (intercept){
////			engine->entityMgr->Select(index);
//			std::cout << "Moving to entity" << std::endl;
//			Intercept* c;
//			c = new Intercept(engine->entityMgr->selectedEntity, engine->entityMgr->entities[index]);
//			if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
//			{
//				engine->entityMgr->selectedEntity->aspects[2]->AddCommand(c);
//			}
//			else
//			{
//				engine->entityMgr->selectedEntity->aspects[2]->SetCommand(c);
//			}
//		}
//		else {
//			std::cout << "Moving to position" << std::endl;
//			MoveTo *c;
//			c = new MoveTo(engine->entityMgr->selectedEntity, posUnderMouse);
////			c->init();
//			if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
//			{
//				engine->entityMgr->selectedEntity->aspects[2]->AddCommand(c);
//			}
//			else
//			{
//				engine->entityMgr->selectedEntity->aspects[2]->SetCommand(c);
//			}
//		}
//	}

	return;
}
