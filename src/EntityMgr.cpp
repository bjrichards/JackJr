/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <Engine.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	count = 0;
	this->engine = eng;
	player = 0;
	seedCount = 25;
	sceneMgr = engine->gfxMgr->mSceneMgr;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreateNewVine(Ogre::Vector3 pos, int dir)
{
	Vine* v = new Vine(engine, Ogre::Vector3(pos.x, pos.y, 1.0), dir);

	vines.push_back(v);
}

void EntityMgr::CreateNewBuilding(Ogre::Vector3 pos, int buildingType)
{
	Building* b = new Building(engine, pos, buildingType);
	buildings.push_back(b);
}


void EntityMgr::Tick(float dt){
	for (unsigned int i = 0; i < vines.size(); i++)
	{
		vines[i]->Tick(dt);
	}
	for (unsigned int i = 0; i < birds.size(); i++)
	{
		birds[i]->Tick(dt);
	}
	float toBirdOrNotToBird = Ogre::Math::RangeRandom(0, 1.0);
	std::cout << toBirdOrNotToBird << std::endl;
	if (toBirdOrNotToBird > 0.99993 && vines.size() > 0)
	{
		std::cout << "Creating a bird" << std::endl;
		Bird* bird = new Bird(engine, Ogre::Vector3((player->position.x+900), (player->position.y + 1000), 2));
		birds.push_back(bird);
	}
	player->Tick(dt);
}
