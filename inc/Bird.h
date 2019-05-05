/*
 * bird.h
 *
 *  Created on: May 4, 2019
 *      Author: brichards
 */

#ifndef INC_BIRD_H_
#define INC_BIRD_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include <Engine.h>
#include <Vine.h>

class Vine;

class Bird{
public:
	Bird(Engine* engine, Ogre::Vector3 pos);
	virtual ~Bird();

	void Tick(float dt);
	bool CheckForTopVineCollisions(float dt);
	void UpdateAnimation(float dt);
	void UpdateVineTimer(float dt);
	void UpdatePosition(float dt);
	void Leave();
	Vine* GetNewVineTarget();

	Ogre::Plane birdPlane;
	Engine* engine;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity* ogreEntity;
	Ogre::Vector3 position;
	Ogre::Vector3 velocity;
	Ogre::Vector3 flyTo;

	bool isOnVine;
	bool isDone;
	bool isLeaving;
	int currentAnimation;
	float animTimer;
	float vineTimer;
	float deleteTimer;
	float moveSpeed;
	Vine* target;
};



#endif /* INC_BIRD_H_ */
