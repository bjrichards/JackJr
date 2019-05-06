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
	mTrayMgr->createButton(OgreBites::TL_BOTTOM, "Instruct", "How To Play");
	mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT, "CreditButton", "Credits");

	Ogre::StringVector options;
	options.push_back("Title Screen");
	//options.push_back("Sound Controls");
	options.push_back("Quit");
	options.push_back("Restart");
	mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 300, 3,options);

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

	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
	menu->hide();

}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();
	//wholeTime = (int)engine->gameMgr->timer;
	//int seedCount = 100; //Get data from game once implemented
//	infoLabel->setCaption("Seed Count: " + std::to_string(engine->entityMgr->seedCount));
	if(startTimer == true)
	{
		infoLabel->setCaption("Seed Count: " + std::to_string(engine->entityMgr->seedCount));
		//(engine->gameMgr->timer) -= dt;
		//wholeTime = (int)(engine->gameMgr->timer);
		time -= dt;
		wholeTime = (int)time;
		infoLabel2->setCaption("Timer: " + std::to_string(wholeTime));
		if(wholeTime == 0)
		{
//			engine->gameMgr->Stop();
//			engine->gameMgr->LoadLevel();
		}
	}

	if(engine->entityMgr->player->position.y > engine->gameMgr->finishLine.y && completed == false)
	{
		completed = true;
		endCondition();
	}
//	infoLabel2->setCaption("Timer: " + std::to_string(wholeTime));
}

void UiMgr::endCondition()
{
	std::cout << "You Win" << std::endl;
	startTimer = false;
	//wholeTime = (int)(engine->gameMgr->timer);
	wholeTime = (int)time;
	infoLabel2->setCaption("Timer: " + std::to_string(wholeTime));
	LevelCompleted(engine->entityMgr->seedCount + wholeTime);
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
        //mTrayMgr->destroyWidget("MyMenu");
        mTrayMgr->destroyWidget(infoLabel3);
        mTrayMgr->destroyWidget("Instruct");
        mTrayMgr->destroyWidget("CreditButton");
        mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
        mTrayMgr->showCursor();

    	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
    	menu->show();

    	infoLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "infoLabel", "Seed Count", 200);
    	infoLabel2 = mTrayMgr->createLabel(OgreBites::TL_TOP, "infoLabel2", "Timer", 250);

        startTimer = true;
    }
//    else if(b->getName()=="SelectButton")
//        {
//            std::cout <<"Selection Changed!" << std::endl;
//            engine->entityMgr->SelectNextEntity();
//        }
    else if(b->getName() == "BackButton")
        {
        	mTrayMgr->showBackdrop("Background");
        	b->hide();
        	OgreBites::Widget *backButton = mTrayMgr->getWidget("BackButton");
        	backButton->hide();
        	mTrayMgr->destroyWidget("BackButton");

        	OgreBites::Widget *rules = mTrayMgr->getWidget("Instructions");
        	rules->hide();
        	mTrayMgr->destroyWidget("Instructions");

//        	OgreBites::Widget *creds = mTrayMgr->getWidget("CreditDisplay");
//        	creds->hide();
//        	mTrayMgr->destroyWidget("CreditDisplay");

        	OgreBites::Widget *startButton = mTrayMgr->getWidget("StartButton");
        	startButton->show();

        	OgreBites::Widget *howButton = mTrayMgr->getWidget("Instruct");
        	howButton->show();

        	OgreBites::Widget *cred = mTrayMgr->getWidget("CreditButton");
        	cred->show();

        	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
        	menu->show();
        }
    else if(b->getName()=="BackButtonCredit")
    {
    	mTrayMgr->showBackdrop("Background");
    	b->hide();
    	OgreBites::Widget *backButton = mTrayMgr->getWidget("BackButtonCredit");
    	backButton->hide();
    	mTrayMgr->destroyWidget("BackButtonCredit");

        OgreBites::Widget *creds = mTrayMgr->getWidget("CreditDisplay");
        creds->hide();
        mTrayMgr->destroyWidget("CreditDisplay");

    	OgreBites::Widget *startButton = mTrayMgr->getWidget("StartButton");
    	startButton->show();

    	OgreBites::Widget *howButton = mTrayMgr->getWidget("Instruct");
    	howButton->show();

    	OgreBites::Widget *cred = mTrayMgr->getWidget("CreditButton");
    	cred->show();

    	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
    	menu->show();
    }
    else if(b->getName()== "Instruct")
    {
    	HowToPlay();
    }
    else if(b->getName()=="CreditButton")
    {
    	Credits();
    }
    else if(b->getName()=="BackButtonLevel")
    {
    	//mTrayMgr->showBackdrop("Background");
    	b->hide();
    	OgreBites::Widget *backButton = mTrayMgr->getWidget("BackButtonLevel");
    	backButton->hide();
    	mTrayMgr->destroyWidget("BackButtonLevel");

    	OgreBites::Widget *nextButton = mTrayMgr->getWidget("NextLevelButton");
    	nextButton->hide();
    	mTrayMgr->destroyWidget("NextLevelButton");

    	OgreBites::Widget *win = mTrayMgr->getWidget("WinScreen");
    	win->hide();
    	mTrayMgr->destroyWidget("WinScreen");

    	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
    	menu->show();

    	completed = false;
    	time = 200;
    	startTimer = true;

    	engine->gameMgr->LoadNewLevel("level" + std::to_string(engine->gameMgr->level));

    }
    else if(b->getName()=="NextLevelButton")
    {
    	//mTrayMgr->showBackdrop("Background");
    	b->hide();
    	OgreBites::Widget *nextButton = mTrayMgr->getWidget("NextLevelButton");
    	nextButton->hide();
    	mTrayMgr->destroyWidget("NextLevelButton");

    	OgreBites::Widget *backButton = mTrayMgr->getWidget("BackButtonLevel");
    	backButton->hide();
    	mTrayMgr->destroyWidget("BackButtonLevel");

    	OgreBites::Widget *win = mTrayMgr->getWidget("WinScreen");
    	win->hide();
    	mTrayMgr->destroyWidget("WinScreen");

    	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
    	menu->show();

    	completed = false;
    	time = 200;
    	startTimer = true;

    	engine->gameMgr->LoadNewLevel("level" + std::to_string(engine->gameMgr->level + 1));
    }

}

void UiMgr::itemSelected(OgreBites::SelectMenu *m){
    switch(m->getSelectionIndex()){
//    case 0:
//    	std::cout<< "How to play"<<std::endl;
//    	HowToPlay();
//    	break;
    case 0:
    	//mLabel->setCaption("Test print Title Screen");
    	//engine->uiMgr->LoadLevel();
    	mTrayMgr->destroyWidget(infoLabel);
    	mTrayMgr->destroyWidget("infoLabel2");

    	startTimer = false;
    	mTrayMgr->showBackdrop("Background");

    	mTrayMgr->createButton(OgreBites::TL_BOTTOM, "StartButton", "Start");
    	mTrayMgr->createButton(OgreBites::TL_BOTTOM, "Instruct", "How To Play");
    	mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT, "CreditButton", "Credits");
    	infoLabel3 = mTrayMgr->createLabel(OgreBites::TL_CENTER, "infoLabel3", "Jack Jr: The Vine Jumper", 300);
    	break;
//    case 2:
//    	//mLabel->setCaption("Test Print Sound Control");
//    	break;
    case 1:
    	//mLabel->setCaption("QUITTER");
    	engine->keepRunning = false;
    	break;
    case 2:
    	//mLabel->setCaption("RESTART");
    	time = 200;
    	engine->gameMgr->LoadNewLevel("level" + std::to_string(engine->gameMgr->level));
    	//engine->gameMgr->LoadNewLevel("level1");
    	break;
    default:
    	break;
    }

}

void UiMgr::HowToPlay()
{
	std::cout << "How to Play" << std::endl;
	//mTrayMgr->hideBackdrop();

	// Create instructions Text Box
	instructions = mTrayMgr->createTextBox(OgreBites::TL_CENTER, "Instructions", "How To Play", 550, 400);
	instructions->setText("				Hello, Welcome To Jack Jr: The Vine Jumper!\n");
	instructions->appendText("Controls:\n");
	instructions->appendText("		SpaceBar = Jump\n");
	instructions->appendText("		A = Left Movement");
	instructions->appendText("		D = Right Movement\n");
	instructions->appendText("		Left Mouse Click on Buildings = Create Vines\n");
	instructions->appendText("Goal:\n");
	instructions->appendText("		Reach the top of the buildings\n");
	instructions->appendText("Rules:\n");
	instructions->appendText("		a). Cannot create vines while jumping.\n");
	instructions->appendText("		b). Reach the top of the building before timer runs out\n");
	instructions->appendText("		c). Player will have a limited number of seeds to grow vines\n");
	instructions->appendText("		d). Watch out for the bird. They eat your vines\n");
	instructions->appendText("		e). Player wins the level when reaching the top\n\n\n\n");
	instructions->appendText("Have Fun! :)");


	mTrayMgr->createButton(OgreBites::TL_CENTER, "BackButton", "Close");

//	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
//	menu->hide();

	OgreBites::Widget *startButton = mTrayMgr->getWidget("StartButton");
	startButton->hide();

	OgreBites::Widget *howButton = mTrayMgr->getWidget("Instruct");
	howButton->hide();

	OgreBites::Widget *cred = mTrayMgr->getWidget("CreditButton");
	cred->hide();
}

void UiMgr::Credits()
{
	std::cout << "Credits" << std::endl;
	//mTrayMgr->hideBackdrop();

	credits = mTrayMgr->createTextBox(OgreBites::TL_CENTER, "CreditDisplay", "Credit", 400, 150);
	credits->setText("						Team members:\n");
	credits->appendText("	Braeden Richards: Gameplay, GFX, Physics\n");
	credits->appendText("	Ryan Van: Gameplay Assistant, SFX, UI\n");

	mTrayMgr->createButton(OgreBites::TL_CENTER, "BackButtonCredit", "Close");

//	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
//	menu->hide();

	OgreBites::Widget *startButton = mTrayMgr->getWidget("StartButton");
	startButton->hide();

	OgreBites::Widget *howButton = mTrayMgr->getWidget("Instruct");
	howButton->hide();

	OgreBites::Widget *cred = mTrayMgr->getWidget("CreditButton");
	cred->hide();
}

void UiMgr::LevelCompleted(int score)
{
	std::cout << "Level Completed" << std::endl;

	nextLevelWindow = mTrayMgr->createTextBox(OgreBites::TL_CENTER, "WinScreen", "Level Completed", 400, 200);
	nextLevelWindow->setText("Congrats on Completing Level " + std::to_string(engine->gameMgr->level) + "\n");
	nextLevelWindow->appendText("Total Score: " + std::to_string(score) + "\n");

	mTrayMgr->createButton(OgreBites::TL_CENTER, "BackButtonLevel", "Restart");

	mTrayMgr->createButton(OgreBites::TL_CENTER, "NextLevelButton", "Next Level");

	OgreBites::Widget *menu = mTrayMgr->getWidget("MyMenu");
	menu->hide();

}
