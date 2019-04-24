/*
 * Player.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: brichards
 */

#include <Player.h>
#include <GfxMgr.h>

Player::Player(Engine* engine, Ogre::Vector3 pos){
	this->engine = engine;
	this->position = pos;
	this->sceneNode = 0;
	this->ogreEntity = 0;
	this->moveSpeed = 300;
	this->velocity = Ogre::Vector3::ZERO;
	this->gravity = Ogre::Vector3(0.0, -400.0, 0.0);
	this->isFalling = false;

	playerPlane.normal = Ogre::Vector3::UNIT_Z;
	playerPlane.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(
		"player",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//plane,
		playerPlane,
		128, 128, 20, 20,
		true,
		1, 1, 1,
		Ogre::Vector3::UNIT_Y);

	ogreEntity = this->engine->gfxMgr->mSceneMgr->createEntity("player");
	sceneNode  = this->engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(ogreEntity);
	sceneNode->setPosition(this->position);
	ogreEntity->setCastShadows(false);
	ogreEntity->setMaterialName("buildingMaterials/player");
}

Player::~Player(void){

}

void Player::MoveRight(float dt){
	Ogre::Vector3 newPosition = position;

	newPosition.x += moveSpeed * dt;

	if (newPosition.x > 476)
	{
		newPosition.x = position.x;
	}

	sceneNode->setPosition(newPosition);
	position = newPosition;
	std::cout << "NewPosition = " << newPosition << std::endl;

}

void Player::MoveLeft(float dt){
	Ogre::Vector3 newPosition = position;

	newPosition.x -= moveSpeed * dt;

	if (newPosition.x < -476)
	{
		newPosition.x = position.x;
	}

	sceneNode->setPosition(newPosition);
	position = newPosition;
	std::cout << "NewPosition = " << newPosition << std::endl;
}

void Player::Jump(){
	std::cout << "we in " << std::endl;
	if (!isFalling)
	{
		isFalling = true;
		this->velocity.y = 400;
		std::cout << "Velocity.y = " << this->velocity.y << std::endl;
	}
}

void Player::Tick(float dt){
		this->velocity.y += this->gravity.y * dt;
		Ogre::Vector3 newPosition = position;
		newPosition.y += velocity.y * dt;
		if (newPosition.y < 0.0)
		{
			newPosition.y = 0;
			isFalling = false;
		}
		sceneNode->setPosition(newPosition);
		this->position = newPosition;
}
