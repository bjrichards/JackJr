/*
 * Building.cpp
 *
 *  Created on: May 1, 2019
 *      Author: brichards
 */

#include <Building.h>

Building::Building(Engine* engine, Ogre::Vector3 pos, int buildingType)
{
	this->engine = engine;
	this->position = pos;
	this->buildingType = buildingType;
	this->sceneNode = 0;
	this->ogreEntity = 0;

	buildingPlane.normal = Ogre::Vector3::UNIT_Z;
	buildingPlane.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(
		"building",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		buildingPlane,
		1000, 1200, 20, 20,
		true,
		1, 4, 4,
		Ogre::Vector3::UNIT_Y);

	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity("building");
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(ogreEntity);
	sceneNode->setPosition(position);
	ogreEntity->setCastShadows(false);
	ogreEntity->setMaterialName("buildingMaterials/glassBuilding");
}

Building::~Building()
{

}

