/*
 * Buildings.h
 *
 *  Created on: May 1, 2019
 *      Author: brichards
 */

#ifndef INC_BUILDING_H_
#define INC_BUILDING_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include <Engine.h>

class Building{
public:
	Building(Engine* engine, Ogre::Vector3 pos, int buildingType);
	virtual ~Building();

	Ogre::Plane buildingPlane;
	Engine* engine;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity* ogreEntity;
	Ogre::Vector3 position;

	int buildingType;

};



#endif /* INC_BUILDING_H_ */
