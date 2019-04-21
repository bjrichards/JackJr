/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <Engine.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	selectedEntity = 0;
	count = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr(){

}


void EntityMgr::SelectNextEntity(){
	if(selectedEntityIndex >= count - 1) {
		selectedEntityIndex = 0;
	} else {
		selectedEntityIndex++;
	}
	Select(selectedEntityIndex);
}


void EntityMgr::Select(int i){
	if(i >= 0 && i < count){
		if(selectedEntity != 0)
			selectedEntity->isSelected = false;
		selectedEntityIndex = i;
		selectedEntity = entities[i];
		selectedEntity->isSelected = true;
	}
}




void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	Entity381 * ent;
	switch(entType){

	case CarrierType:
//		ent = (Entity381 *) (new Carrier(engine, pos, count++));
		break;
	default:
		break;
	}
//	ent->Init();
//	entities.push_back(ent);

}

void EntityMgr::Tick(float dt){
	for(int i = 0; i < count; i++){
		entities[i]->Tick(dt);
	}
}
