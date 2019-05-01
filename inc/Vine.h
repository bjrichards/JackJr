/*
 * Vine.h
 *
 *  Created on: Apr 28, 2019
 *      Author: brichards
 */

#ifndef INC_VINE_H_
#define INC_VINE_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include <Engine.h>

class Vine{
public:
	Vine(Engine* engine, Ogre::Vector3 pos, int dir);
	virtual ~Vine();

	void GrowOneStage(void);
	void Tick(float dt);

	Ogre::Plane vinePlane;
	Engine* engine;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity* ogreEntity;
	Ogre::Vector3 position;

	float growthTimer;
	int growthStage;
	int vineType;

};



#endif /* INC_VINE_H_ */
