/*
 * Command.h
 *
 *  Created on: Mar 28, 2018
 *      Author: sushil
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <Entity381.h>
#include <OgreVector3.h>
#include <CommandTypes.h>

class Command {

public:
	Command(Entity381* ent, CommandType ct);
	virtual ~Command();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();
	bool is_done;

	Entity381* entity;
	CommandType commandType;

};

class MoveTo: public Command {

public:
	MoveTo(Entity381* ent, Ogre::Vector3 location);
	~MoveTo();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD;

};

class Intercept: public Command {

public:
	Intercept(Entity381* ent, Entity381* prey);
	~Intercept();

	void init();
	void tick(float dt);
	bool done();
	Entity381* prey;

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD;

};


#endif /* COMMAND_H_ */
