/*
 * Player.h
 *
 *  Created on: Apr 22, 2019
 *      Author: brichards
 */

#ifndef INC_PLAYER_H_
#define INC_PLAYER_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include <Engine.h>

class Player{
public:
	Player(Engine* engine, Ogre::Vector3 pos);
	virtual ~Player();

	void MoveRight(float dt);
	void MoveLeft(float dt);
	void Jump();
	void Tick(float dt);

	Ogre::Plane playerPlane;
	Engine* engine;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity* ogreEntity;
	Ogre::Vector3 position;
	Ogre::Vector3 velocity;
	Ogre::Vector3 gravity;

	float moveSpeed;
	bool isFalling;
};



#endif /* INC_PLAYER_H_ */
