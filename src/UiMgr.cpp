/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Types381.h>
#include <Player.h>

UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	    mOverlaySystem = new Ogre::OverlaySystem();
	    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

	    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){
	//init sdktrays

    mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
    mInputContext.mMouse = engine->inputMgr->mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UiMgr::stop(){

}

void UiMgr::LoadLevel(){
//	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Spawn Boat!");
//	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "SelectButton", "Select Next");


//	Ogre::StringVector options;
//	options.push_back("Select Boat");
//	options.push_back("Spawn SpeedBoat");
//	options.push_back("Spawn Destroyer");
//	options.push_back("Spawn Carrier");
//	mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 300, 4,options);

	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("20190410_045430320_iOS.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	mTrayMgr->showBackdrop("Background");

	mTrayMgr->createButton(OgreBites::TL_BOTTOM, "StartButton", "Start");

	Ogre::StringVector options;
	options.push_back("Title Screen");
	options.push_back("Sound Controls");
	options.push_back("Quit");
	options.push_back("Restart");
	mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 300, 4,options);

	//mTrayMgr->showBackdrop("ECSLENT/UI"); //Menu display at the buttom of the screen

	//mLabel = mTrayMgr->createLabel(OgreBites::TL_LEFT,"MyLabel","Menu Stuff for Testing",250);

//	infoLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "infoLabel", "No Unit Selected", 200);
//	infoLabel2 = mTrayMgr->createLabel(OgreBites::TL_TOP, "infoLabel2", "No Unit Selected", 250);
	infoLabel3 = mTrayMgr->createLabel(OgreBites::TL_CENTER, "infoLabel3", "Jack Jr: The Vine Jumper", 300);


	//OgreBites::ProgressBar * pbar;
	//pbar = mTrayMgr->createProgressBar(OgreBites::TL_TOP,"TimerBar", "Timer", 300, 200);
	//pbar->setProgress(100);

	//Timer = mTrayMgr->createProgressBar(OgreBites::TL_TOP,"TimerBar", "Timer", 300, 200);
	//time = 0;
	//Timer->setProgress(time);

}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();

	//int seedCount = 100; //Get data from game once implemented
//	infoLabel->setCaption("Seed Count: " + std::to_string(engine->entityMgr->seedCount));
	if(startTimer == true)
	{
		infoLabel->setCaption("Seed Count: " + std::to_string(engine->entityMgr->seedCount));
		time = time - dt;
		wholeTime = (int)time;
		infoLabel2->setCaption("Timer: " + std::to_string(wholeTime));
		if(wholeTime == 0)
		{
//			engine->gameMgr->Stop();
//			engine->gameMgr->LoadLevel();
		}
	}
//	infoLabel2->setCaption("Timer: " + std::to_string(wholeTime));

}

void UiMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){
    if(b->getName()=="StartButton")
    {
        mTrayMgr->hideBackdrop();
        mTrayMgr->destroyWidget(b->getName());
        mTrayMgr->destroyWidget("MyMenu");
        mTrayMgr->destroyWidget(infoLabel3);
        mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
        mTrayMgr->showCursor();

    	infoLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "infoLabel", "No Unit Selected", 200);
    	infoLabel2 = mTrayMgr->createLabel(OgreBites::TL_TOP, "infoLabel2", "No Unit Selected", 250);

        startTimer = true;
    }
//    else if(b->getName()=="SelectButton")
//        {
//            std::cout <<"Selection Changed!" << std::endl;
//            engine->entityMgr->SelectNextEntity();
//        }

}

void UiMgr::itemSelected(OgreBites::SelectMenu *m){
    switch(m->getSelectionIndex()){
    case 0:
    	mLabel->setCaption("Test print Title Screen");
    	break;
    case 1:
    	mLabel->setCaption("Test Print Sound Control");
    	break;
    case 2:
    	mLabel->setCaption("QUITTER");
    	engine->keepRunning = false;
    	break;
    case 3:
    	mLabel->setCaption("RESTART");
//    	engine->Cleanup();
//    	engine->Init();
//    	engine->Run();
    	break;
    default:
    	break;
    }

}
