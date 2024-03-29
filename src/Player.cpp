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
	this->moveSpeed = 500;
	this->velocity = Ogre::Vector3::ZERO;
	this->gravity = Ogre::Vector3(0.0, -1200.0, 0.0);
	this->isFalling = false;
	this->animationTimerSet = 0.2;
	this->animationTimer = this->animationTimerSet;
	this->movingLeft = false;
	this->movingRight = false;
	this->didMove = false;
	this->wasFalling = false;
	this->currentAnimation = 0;
	this->facing = 0;

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
	ogreEntity->setMaterialName("PlayerStanding/left00");
}

Player::~Player(void){

}

void Player::MoveRight(float dt){
	Ogre::Vector3 newPosition = position;
	facing = 1;
	if (movingRight == false)
	{
		if (!isFalling && !wasFalling)
		{
			ogreEntity->setMaterialName("PlayerWalking/rightWalking00");
			currentAnimation = 0;
		}
//		currentAnimation = 1;
		movingRight = true;
		movingLeft = false;

	}
	newPosition.x += moveSpeed * dt;

	bool collisionFound = false;

	// Check for collision with buildings
	for (unsigned int i = 0; i < engine->entityMgr->buildings.size() && !collisionFound; i++)
	{
		Ogre::Vector3 temp = engine->entityMgr->buildings[i]->position;
		if (newPosition.y < temp.y + 664 && newPosition.y > temp.y - 600)
		{
			if (newPosition.x < temp.x + 525 && newPosition.x > temp.x - 525)
			{
				collisionFound = true;
				newPosition.x = position.x;
			}
		}
	}
	// Check for collision with vines
	for (unsigned int i = 0; i < engine->entityMgr->vines.size() && !collisionFound; i++)
	{
		if(engine->entityMgr->vines[i]->position.z > -1)
		{
			if (newPosition.y < engine->entityMgr->vines[i]->position.y + 64 && newPosition.y > engine->entityMgr->vines[i]->position.y - 64 && newPosition.x - 32 < engine->entityMgr->vines[i]->position.x + 60 && newPosition.x + 32 > engine->entityMgr->vines[i]->position.x - 60)
			{
				collisionFound = true;
				newPosition.x = position.x;
			}
		}
	}

	sceneNode->setPosition(newPosition);
	position = newPosition;

}

void Player::MoveLeft(float dt){
	Ogre::Vector3 newPosition = position;
	facing = 0;
	if (movingLeft == false)
	{
		if (!isFalling && !wasFalling)
		{
			ogreEntity->setMaterialName("PlayerWalking/leftWalking00");
			currentAnimation = 0;
		}
//		currentAnimation = 1;
		movingRight = false;
		movingLeft = true;
	}
	newPosition.x -= moveSpeed * dt;

	bool collisionFound = false;

	// Check for collision with buildings
	for (unsigned int i = 0; i < engine->entityMgr->buildings.size() && !collisionFound; i++)
	{
		Ogre::Vector3 temp = engine->entityMgr->buildings[i]->position;
		if (newPosition.y < temp.y + 664 && newPosition.y > temp.y - 600)
		{
			if (newPosition.x < temp.x + 525 && newPosition.x > temp.x - 525)
			{
				collisionFound = true;
				newPosition.x = position.x;
			}
		}
	}
	for (unsigned int i = 0; i < engine->entityMgr->vines.size() && !collisionFound; i++)
	{
		if(engine->entityMgr->vines[i]->position.z > -1)
		{
			if (newPosition.y < engine->entityMgr->vines[i]->position.y + 64 && newPosition.y > engine->entityMgr->vines[i]->position.y - 64 && newPosition.x - 32 < engine->entityMgr->vines[i]->position.x + 60 && newPosition.x + 32 > engine->entityMgr->vines[i]->position.x - 60)
			{
				newPosition.x = position.x;
			}
		}
	}

	sceneNode->setPosition(newPosition);
	position = newPosition;
}

bool Player::CheckForTopBuildingCollisions(float dt)
{
	Ogre::Vector3 newPosition = position;

	newPosition.x += velocity.y * dt;

	bool collisionFound = false;

	for (unsigned int i = 0; i < engine->entityMgr->buildings.size() && !collisionFound; i++)
		{
			Ogre::Vector3 temp = engine->entityMgr->buildings[i]->position;
			if (newPosition.y < temp.y + 665 && newPosition.y > temp.y - 660)
			{
				if (newPosition.x < temp.x + 520 && newPosition.x > temp.x - 520)
				{
					collisionFound = true;
				}
			}
		}

	if (collisionFound)
	{
		if (velocity.y < 0)
		{
			velocity.y = 0.0;
			if (isFalling == true)
			{
				isFalling = false;
				wasFalling = true;
			}
		}
	}
	return collisionFound;
}

void Player::Jump(){
	//engine->soundMgr->playJumpSound();
	if (!isFalling)
	{
		isFalling = true;
		velocity.y = 0;
		velocity.y = 800;
	}
}

void Player::Tick(float dt){
		CheckForBottomVineCollisions(dt);
		velocity.y += gravity.y * dt;
		CheckForTopVineCollisions(dt);
		CheckForTopBuildingCollisions(dt);
		Ogre::Vector3 newPosition = position;
		newPosition.y += velocity.y * dt;
		animationTimer -= dt;
		if (velocity.y == 0)
		{
			if (isFalling == true)
			{
				isFalling = false;
				wasFalling = true;
			}
		}
		else if (velocity.y < 0.0)
		{
			if (newPosition.y >= 0.0)
				isFalling = true;
		}

		if (newPosition.y < 0.0)
		{
			newPosition.y = 0;
			if (isFalling == true)
			{
				isFalling = false;
				wasFalling = true;
			}
		}
		if (isFalling == true)
		{
			std::cout << velocity.y << std::endl;
			engine->gfxMgr->mCamera->setPosition(Ogre::Vector3(engine->gfxMgr->mCamera->getPosition().x, engine->gfxMgr->mCamera->getPosition().y + velocity.y * dt, engine->gfxMgr->mCamera->getPosition().z));
		}
		engine->gfxMgr->mCamera->setPosition(Ogre::Vector3(position.x - 32, engine->gfxMgr->mCamera->getPosition().y, engine->gfxMgr->mCamera->getPosition().z));

		if ((!isFalling && movingRight && !didMove && !wasFalling))
		{
			if (animationTimer <= 0)
			{
				movingRight = false;
				ogreEntity->setMaterialName("PlayerStanding/right00");
			}
		}
		else if ((!isFalling && facing == 1 && !didMove && !wasFalling))
		{
			if (animationTimer <= 0)
			{
				animationTimer = animationTimerSet;
				ogreEntity->setMaterialName("PlayerStanding/right00");
			}
		}
		else if ((!isFalling && movingLeft && !didMove && !wasFalling))
		{	if (animationTimer <= 0)
			{
				movingLeft = false;
				ogreEntity->setMaterialName("PlayerStanding/left00");
			}
		}
		else if ((!isFalling && facing == 0 && !didMove && !wasFalling))
		{
			if (animationTimer <= 0)
			{
				animationTimer = animationTimerSet;
				ogreEntity->setMaterialName("PlayerStanding/left00");
			}
		}
		if (!isFalling && wasFalling && facing == 0)
		{
			wasFalling = false;
			ogreEntity->setMaterialName("PlayerJumping/leftLanding");
			animationTimer = animationTimerSet;
		}
		else if (!isFalling && wasFalling && facing == 1)
		{
			wasFalling = false;
			ogreEntity->setMaterialName("PlayerJumping/rightLanding");
			animationTimer = animationTimerSet;
		}
		else if (isFalling && movingRight)
		{
			ogreEntity->setMaterialName("PlayerJumping/rightFalling");
		}
		else if (isFalling && movingLeft)
		{
			ogreEntity->setMaterialName("PlayerJumping/leftFalling");
		}
		Animation(dt);
		sceneNode->setPosition(newPosition);
		this->position = newPosition;
}

bool Player::CheckForTopVineCollisions(float dt)
{
	if (velocity.y < 0)
		{
			Ogre::Vector3 nextPosition = position + velocity * dt;
			for (unsigned int i = 0; i < engine->entityMgr->vines.size(); i++)
			{
				if(engine->entityMgr->vines[i]->position.z > -1)
				{
					if (nextPosition.y < engine->entityMgr->vines[i]->position.y+64 && nextPosition.y > engine->entityMgr->vines[i]->position.y+60)
					{
						if (nextPosition.x + 32 > engine->entityMgr->vines[i]->position.x-63 && nextPosition.x - 32 < engine->entityMgr->vines[i]->position.x+63)
						{
							if (velocity.y < 0)
								velocity.y = 0;
							if (isFalling == true)
							{
								isFalling = false;
								wasFalling = true;
							}
							return true;
						}
					}
				}
			}
		}

	return false;
}

bool Player::CheckForBottomVineCollisions(float dt)
{
	if (velocity.y > 0)
	{
		Ogre::Vector3 nextPosition = position + velocity * dt;
		for (unsigned int i = 0; i < engine->entityMgr->vines.size(); i++)
		{
			if(engine->entityMgr->vines[i]->position.z > -1)
			{
				if (nextPosition.y  + 64 > engine->entityMgr->vines[i]->position.y-60 && nextPosition.y + 64 < engine->entityMgr->vines[i]->position.y+64)
				{
					if (nextPosition.x + 32 > engine->entityMgr->vines[i]->position.x-63 && nextPosition.x - 32 < engine->entityMgr->vines[i]->position.x+63)
					{
						velocity.y = 0;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Player::IsColliding(Ogre::Vector3 objectPos)
{
	if (objectPos.y - 60 < position.y + 64 && objectPos.y - 60 > position.y - 64)
	{
		if (objectPos.x - 63 < position.x + 32 && objectPos.x + 63 > position.x - 32)
		{
			return true;
		}
	}

	return false;
}

void Player::Animation(float dt)
{
	if (animationTimer <= 0.0)
	{
		animationTimer = animationTimerSet;
		if (isFalling)
		{
			if (facing == 0)
				ogreEntity->setMaterialName("PlayerJumping/leftFalling");
			else
				ogreEntity->setMaterialName("PlayerJumping/rightFalling");
		}
		else if (movingLeft && !wasFalling)
		{
			switch (currentAnimation)
			{
			case 0:
				ogreEntity->setMaterialName("PlayerWalking/leftWalking00");
				currentAnimation = 1;
				break;
			case 1:
				ogreEntity->setMaterialName("PlayerWalking/leftWalking01");
				currentAnimation = 2;
				break;
			case 2:
				ogreEntity->setMaterialName("PlayerWalking/leftWalking02");
				currentAnimation = 3;
				break;
			case 3:
				ogreEntity->setMaterialName("PlayerWalking/leftWalking01");
				currentAnimation = 0;
				break;
			}
		}
		else if (movingRight && !wasFalling)
		{
			switch (currentAnimation)
			{
			case 0:
				ogreEntity->setMaterialName("PlayerWalking/rightWalking00");
				currentAnimation = 1;
				break;
			case 1:
				ogreEntity->setMaterialName("PlayerWalking/rightWalking01");
				currentAnimation = 2;
				break;
			case 2:
				ogreEntity->setMaterialName("PlayerWalking/rightWalking02");
				currentAnimation = 3;
				break;
			case 3:
				ogreEntity->setMaterialName("PlayerWalking/rightWalking01");
				currentAnimation = 0;
				break;
			}
		}
	}
}
