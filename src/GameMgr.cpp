/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>

#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>
#include <Player.h>


GameMgr::GameMgr(Engine *engine): Mgr(engine) {
	cameraNode = 0;
}

GameMgr::~GameMgr() {
	// TODO Auto-generated destructor stub
}

void GameMgr::Init(){

}

void GameMgr::LoadLevel(){

	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);

	  // a fixed point in the ocean so you can see relative motion

	  Ogre::Entity* ogreEntityFixed = engine->gfxMgr->mSceneMgr->createEntity("robot.mesh");
	  Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
	  sceneNode->attachObject(ogreEntityFixed);
	  sceneNode->showBoundingBox(true);

	  // A node to attach the camera to so we can move the camera node instead of the camera.
	  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	  cameraNode->setPosition(0, 200, 500);
	  cameraNode->attachObject(engine->gfxMgr->mCamera);

	  engine->gfxMgr->MakeBuildings();
	  engine->gfxMgr->MakeSky();
	  engine->entityMgr->player = new Player(engine, Ogre::Vector3::ZERO);
	  MakeEntities();
}

void GameMgr::MakeEntities(){
	Ogre::Vector3 pos = Ogre::Vector3(-1000, 0, 0);
}

void GameMgr::LoadNewLevel(std::string levelName)
{
	//Move everything from current level out of sight (out of sight out of mind lol)
	EntityMgr* e = engine->entityMgr;

	for (unsigned int i = 0; i < e->buildings.size(); i++)
	{
		e->buildings[i]->position.z = 10000;
		e->buildings[i]->sceneNode->setPosition(Ogre::Vector3(e->buildings[i]->position.x, e->buildings[i]->position.y, 10000));
	}
	e->buildings.clear();

	for (unsigned int i = 0; i < e->birds.size(); i++)
	{
		e->birds[i]->position.z = 10000;
		e->birds[i]->flyTo = Ogre::Vector3(e->birds[i]->position.x, e->birds[i]->position.y, 10000);
		e->birds[i]->sceneNode->setPosition(Ogre::Vector3(e->birds[i]->position.x, e->birds[i]->position.y, 10000));
	}
	e->birds.clear();

	for (unsigned int i = 0; i < e->vines.size(); i++)
	{
		e->vines[i]->position.z = 10000;
		e->vines[i]->sceneNode->setPosition(Ogre::Vector3(e->vines[i]->position.x, e->vines[i]->position.y, 10000));
	}
	e->vines.clear();

	// Put the levels below here
	if (levelName.compare("level0") == 0)
	{
		engine->entityMgr->CreateNewBuilding(Ogre::Vector3(-750, 540, 0), 0);
		engine->entityMgr->CreateNewBuilding(Ogre::Vector3(-750, 1740, 0), 0);
		engine->entityMgr->CreateNewBuilding(Ogre::Vector3(750, 540, 0), 0);
		engine->entityMgr->CreateNewBuilding(Ogre::Vector3(750, 1740, 0), 0);

		engine->gfxMgr->road.normal = Ogre::Vector3::UNIT_Z;
		engine->gfxMgr->road.d = 0;
		Ogre::MeshManager::getSingleton().createPlane(
			"road",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			//plane,
			engine->gfxMgr->road,
			6400, 192, 20, 20,
			true,
			1, 20, 1,
			Ogre::Vector3::UNIT_Y);

		Ogre::Entity* r = engine->gfxMgr->mSceneMgr->createEntity("road");
		Ogre::SceneNode* r1 = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		r1->attachObject(r);
		r1->setPosition(0, -180, -0.5);
		r->setCastShadows(false);
		r->setMaterialName("buildingMaterials/road");

		engine->entityMgr->player->position = Ogre::Vector3::ZERO;
		engine->entityMgr->seedCount = 25;
	}
}
