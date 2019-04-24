/*
 * GfxMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */


#include <iostream>

#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>

#include <Engine.h>
#include <GfxMgr.h>
#include <EntityMgr.h>

GfxMgr::GfxMgr(Engine *engine): Mgr(engine) {

	mRoot = 0;
	mResourcesCfg = Ogre::StringUtil::BLANK;
	mPluginsCfg   = Ogre::StringUtil::BLANK;
	mWindow = 0;
	mSceneMgr = 0;
	mCamera = 0;
	//oceanSurface(Ogre::Vector3::UNIT_Y, 0);
#ifdef _DEBUG
  mResourcesCfg = "resources_d.cfg";
  mPluginsCfg = "plugins_d.cfg";
#else
  mResourcesCfg = "resources.cfg";
  mPluginsCfg = "plugins.cfg";
#endif

  mRoot = new Ogre::Root(mPluginsCfg);

  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

  Ogre::String name, locType;
  Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

  while (secIt.hasMoreElements())
  {
    Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator it;

    for (it = settings->begin(); it != settings->end(); ++it)
    {
      locType = it->first;
      name = it->second;

      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
    }
  }

  if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	  std::cerr << "Could not find Config File and could not show Config Dialog" << std::endl;

  mWindow = mRoot->initialise(true, "CS381 Game Engine Version 1.0");

  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

  mCamera = mSceneMgr->createCamera("MainCam");
  mCamera->setPosition(0, 0, 600);
  mCamera->lookAt(mCamera->getOrientation().zAxis());
  mCamera->setNearClipDistance(1);

  Ogre::Viewport* vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

  mCamera->setAspectRatio(
    Ogre::Real(vp->getActualWidth()) /
    Ogre::Real(vp->getActualHeight()));

  //-----------------------------------------------------------------------
  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

GfxMgr::~GfxMgr() {

	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

void GfxMgr::Init(){

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  //mRoot->addFrameListener(this);
  //mRoot->startRendering();


}


void GfxMgr::MakeSky(){
	background.normal = Ogre::Vector3::UNIT_Z;
	background.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(
		"background",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//plane,
		background,
		2400, 2400, 5, 5,
		true,
		1, 1, 1,
		Ogre::Vector3::UNIT_Y);

	Ogre::Entity* b = engine->gfxMgr->mSceneMgr->createEntity("background");
	Ogre::SceneNode* ba = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ba->attachObject(b);
	ba->setPosition(0, 0, 0);
	b->setCastShadows(false);
	b->setMaterialName("buildingMaterials/background");
}

void GfxMgr::MakeGround(){

	//Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
//	//Ogre::Plane oceanSurface(Ogre::Vector3::UNIT_Y, 0);
//	//oceanSurface = plane;
//	oceanSurface.normal = Ogre::Vector3::UNIT_Y;
//	oceanSurface.d = 0;
//	Ogre::MeshManager::getSingleton().createPlane(
//	    "ocean",
//	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//	    //plane,
//		oceanSurface,
//	    15000, 15000, 20, 20,
//	    true,
//	    1, 1, 1,
//	    Ogre::Vector3::UNIT_Z);
//
//	  Ogre::Entity* groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ocean");
//	  engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
//	  groundEntity->setCastShadows(false);
//	  //groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
//	  //groundEntity->setMaterialName("OceanHLSL_GLSL");
//	  groundEntity->setMaterialName("Ocean2_Cg");
//	  //groundEntity->setMaterialName("NavyCg");
}

void GfxMgr::MakeBuildings(){

	leftBuilding.normal = Ogre::Vector3::UNIT_Z;
	leftBuilding.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(
		"lbuilding",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//plane,
		leftBuilding,
		500, 2400, 20, 20,
		true,
		1, 1, 2,
		Ogre::Vector3::UNIT_Y);

	Ogre::Entity* lbuildingEntity = engine->gfxMgr->mSceneMgr->createEntity("lbuilding");
	Ogre::SceneNode* leftb1 = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	leftb1->attachObject(lbuildingEntity);
	leftb1->setPosition(-750, 100, 0);
	lbuildingEntity->setCastShadows(false);
	lbuildingEntity->setMaterialName("buildingMaterials/building_right_window");

	rightBuilding.normal = Ogre::Vector3::UNIT_Z;
	rightBuilding.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(
		"rbuilding",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//plane,
		leftBuilding,
		500, 2400, 20, 20,
		true,
		1, 1, 2,
		Ogre::Vector3::UNIT_Y);

	Ogre::Entity* rbuildingEntity = engine->gfxMgr->mSceneMgr->createEntity("rbuilding");
	Ogre::SceneNode* rightb1 = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	rightb1->attachObject(rbuildingEntity);
	rightb1->setPosition(750, 100, 0);
	rbuildingEntity->setCastShadows(false);
	rbuildingEntity->setMaterialName("buildingMaterials/building_right_window");
}


void GfxMgr::windowClosed(Ogre::RenderWindow *rw){
	mRoot->shutdown();
	engine->keepRunning = false;
}

bool GfxMgr::frameRenderingQueued(const Ogre::FrameEvent& fe){
	if(mWindow->isClosed()) return false;
	return true;
}


void GfxMgr::LoadLevel(){

}

void GfxMgr::Stop(){
	mRoot->shutdown();
}

void GfxMgr::Tick(float dt){
//call ogre root render one frame method
	mRoot->renderOneFrame(dt);
	Ogre::WindowEventUtilities::messagePump();
//	mCamera->setPosition(Ogre::Vector3(0.0,engine->entityMgr->player->position.y, 600));
//	  mCamera->lookAt(Ogre::Vector3(0.0, engine->entityMgr->player->position.y + 60, -600));
}

