/*
 * Vine.cpp
 *
 *  Created on: Apr 28, 2019
 *      Author: brichards
 */

#include <Vine.h>
#include <GfxMgr.h>

Vine::Vine(Engine* engine, Ogre::Vector3 pos, int dir)
{
	std::cout << "Creating vine" << std::endl;
	this->engine = engine;
	if (dir == 0)
		this->position = Ogre::Vector3(45 + pos.x, pos.y, pos.z);
	else
		this->position = Ogre::Vector3(-45 + pos.x, pos.y, pos.z);
	this->sceneNode = 0;
	this->ogreEntity = 0;
	this->growthStage = 0;
	this->growthTimer = 0;
	if (dir == 0)
		this->vineType = 0;
	else
		this->vineType = 1;

	vinePlane.normal = Ogre::Vector3::UNIT_Z;
	vinePlane.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(
		"vine",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//plane,
		vinePlane,
		128, 128, 20, 20,
		true,
		1, 1, 1,
		Ogre::Vector3::UNIT_Y);

	std::cout << "Plane created" << std::endl;
	ogreEntity = this->engine->gfxMgr->mSceneMgr->createEntity("vine");
	std::cout << "Creating entity" << std::endl;
	sceneNode  = this->engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	std::cout << "Creating sceneNode" << std::endl;
	sceneNode->attachObject(ogreEntity);
	sceneNode->setPosition(this->position);
	ogreEntity->setCastShadows(false);
	if (vineType == 0)
		ogreEntity->setMaterialName("vineL/vine_00");
	else
		ogreEntity->setMaterialName("vineR/vine_00");

	std::cout << "Finished creating vine" << std::endl;
}

Vine::~Vine()
{

}

void Vine::GrowOneStage(void)
{
	switch(growthStage)
	{
	case 0:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_01");
		else
			ogreEntity->setMaterialName("vineR/vine_01");
		growthStage++;
		break;
	case 1:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_02");
		else
			ogreEntity->setMaterialName("vineR/vine_02");
		growthStage++;
		break;
	case 2:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_03");
		else
			ogreEntity->setMaterialName("vineR/vine_03");
		growthStage++;
		break;
	case 3:
		if (vineType == 0)
		{
			ogreEntity->setMaterialName("vineL/vine_04");
		}
		else
			ogreEntity->setMaterialName("vineR/vine_04");
		growthStage++;
		break;
	case 4:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_05");
		else
			ogreEntity->setMaterialName("vineR/vine_05");
		growthStage++;
		break;
	case 5:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_06");
		else
			ogreEntity->setMaterialName("vineR/vine_06");
		growthStage++;
		break;
	case 6:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_07");
		else
			ogreEntity->setMaterialName("vineR/vine_07");
		growthStage++;
		break;
	case 7:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_08");
		else
			ogreEntity->setMaterialName("vineR/vine_08");
		growthStage++;
		break;
	case 8:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_09");
		else
			ogreEntity->setMaterialName("vineR/vine_09");
		growthStage++;
		break;
	case 9:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_10");
		else
			ogreEntity->setMaterialName("vineR/vine_10");
		growthStage++;
		break;
	case 10:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_11");
		else
			ogreEntity->setMaterialName("vineR/vine_11");
		growthStage++;
		break;
	case 11:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_12");
		else
			ogreEntity->setMaterialName("vineR/vine_12");
		growthStage++;
		break;
	case 12:
		if (vineType == 0)
			ogreEntity->setMaterialName("vineL/vine_13");
		else
			ogreEntity->setMaterialName("vineR/vine_13");
		growthStage++;
		break;
	}
}

void Vine::Tick(float dt)
{
	growthTimer += dt;
	if (growthStage < 13 && growthTimer > 0.10)
	{
		growthTimer = 0;
		GrowOneStage();
	}
	return;
}
