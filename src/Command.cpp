/*
 * Command.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: brichards
 */

#include <Command.h>
#include <Entity381.h>
#include <CommandTypes.h>

Command::Command(Entity381* ent, CommandType ct){
	entity = ent;
	commandType = ct;
	is_done = false;
}

Command::~Command(){

}

void Command::init(){

}

void Command::tick(float dt){

}

bool Command::done(){

	return false;
}


MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location):Command((Entity381*) ent, static_cast<CommandType>(moveTo) ){
	entity = ent;
	targetLocation = location;
	MOVE_DISTANCE_THRESHOLD = 100.0;
}

MoveTo::~MoveTo(){

}

void MoveTo::init(){
	//Set desired speed to max
//	entity->desiredSpeed = entity->maxSpeed;
//
//	//Set desired heading
//	Ogre::Degree heading = Ogre::Degree(Ogre::Math::ATan2((targetLocation.x - entity->position.x), (targetLocation.z - entity->position.z)));
//	std::cout << heading << std::endl;
//	entity->desiredHeading = FixAngle(FixAngle((-heading.valueDegrees())) + 90);
}

void MoveTo::tick(float dt){
//	Ogre::Degree heading = Ogre::Degree(Ogre::Math::ATan2((targetLocation.x - entity->position.x), (targetLocation.z - entity->position.z)));
//		std::cout << heading << std::endl;
//		entity->desiredHeading = FixAngle(FixAngle((-heading.valueDegrees())) + 90);
//	if (entity->position.distance(targetLocation) < MOVE_DISTANCE_THRESHOLD)
//	{
//		entity->desiredSpeed = entity->minSpeed;
//		is_done = true;
//
//	}

	return;
}

bool MoveTo::done(){

	return is_done;
}

Intercept::Intercept(Entity381* ent, Entity381* prey):Command((Entity381*) ent, static_cast<CommandType>(intercept) ){
	entity = ent;
	this->prey = prey;
	MOVE_DISTANCE_THRESHOLD = 100.0;
}

Intercept::~Intercept(){

}

void Intercept::init(){

}

void Intercept::tick(float dt){

}

bool Intercept::done(){

	return is_done;
}
