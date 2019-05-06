/*
 * Bird.cpp
 *
 *  Created on: May 4, 2019
 *      Author: brichards
 */

#include <Bird.h>
#include <GfxMgr.h>

Bird::Bird(Engine* engine, Ogre::Vector3 pos)
{
	this->engine = engine;
	position = pos;
	flyTo = Ogre::Vector3::ZERO;
	velocity = Ogre::Vector3::ZERO;
	isOnVine = false;
	isDone = false;
	isLeaving = false;
	currentAnimation = 0;
	animTimer = 0.25;
	deleteTimer = 2;
	vineTimer = 4;
	moveSpeed = 400;

	birdPlane.normal = Ogre::Vector3::UNIT_Z;
	birdPlane.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(
		"bird",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		birdPlane,
		64, 64, 20, 20,
		true,
		1, 1, 1,
		Ogre::Vector3::UNIT_Y);

	ogreEntity = this->engine->gfxMgr->mSceneMgr->createEntity("bird");
	sceneNode = this->engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(ogreEntity);
	sceneNode->setPosition(this->position);

	ogreEntity->setMaterialName("Bird/flying_00");
	target = GetNewVineTarget();
}

Bird::~Bird()
{

}

void Bird::Tick(float dt)
{
	if (target->position.z < -3)
	{
		if (!isLeaving)
		{
			isLeaving = true;
			float x = Ogre::Math::RangeRandom(-1, 1) * 10000;
			flyTo = Ogre::Vector3(x, this->position.y + 1000, 2) - position;
			isOnVine = false;
			isDone = true;
		}
	}
	UpdateVineTimer(dt);
	UpdateAnimation(dt);

	if (isOnVine && !isDone)
	{
		vineTimer -= dt;
		if (vineTimer <= 0.0)
		{
			isOnVine = false;
			isDone = true;
			target->position.z = -100;
			target->sceneNode->setPosition(target->position);
//			target = 0;
		}
	}
	else if (!isOnVine)
	{
		UpdatePosition(dt);
	}
	if (isDone)
	{
		Leave();
	}
}

Vine* Bird::GetNewVineTarget()
{
	Vine* v = engine->entityMgr->vines[engine->entityMgr->vines.size()-1];

	return v;
}

void Bird::UpdateAnimation(float dt)
{
	animTimer -= dt;
	if (!isOnVine)
	{
		if (currentAnimation > 1)
			currentAnimation = 0;
		if (animTimer <= 0.0)
		{
			animTimer = 0.25;
			switch(currentAnimation)
			{
			case 0:
				ogreEntity->setMaterialName("Bird/flying_01");
				currentAnimation = 1;
				break;
			case 1:
				ogreEntity->setMaterialName("Bird/flying_00");
				currentAnimation = 0;
				break;
			default:
				break;
			}
		}
	}
	else if (isOnVine)
	{
		if (animTimer <= 0.0)
		{
			animTimer = 0.25;
			switch(currentAnimation)
			{
			case 0:
				ogreEntity->setMaterialName("Bird/pecking_00");
				currentAnimation = 1;
				break;
			case 1:
				ogreEntity->setMaterialName("Bird/pecking_01");
				currentAnimation = 2;
				break;
			case 2:
				ogreEntity->setMaterialName("Bird/pecking_02");
				currentAnimation = 3;
				break;
			case 3:
				ogreEntity->setMaterialName("Bird/pecking_01");
				currentAnimation = 0;
				break;
			default:
				break;
			}
		}
	}
}

void Bird::UpdateVineTimer(float dt)
{


}

void Bird::UpdatePosition(float dt)
{
	if (!isDone && target->position.z != -100)
	{
		Ogre::Vector3 v;

	//	v = Ogre::Vector3(target->position.x, target->position.y, target->position.x) - position;
		v = target->position - position;
		if (v.length() < 25.0)
		{
			if (!isOnVine)
			{
				isOnVine = true;
				currentAnimation = 0;
			}
		}
		else
		{
			velocity = v.normalisedCopy() * moveSpeed;

			position += velocity * dt;
		}
	}
	else
	{
		velocity = flyTo.normalisedCopy() * moveSpeed;

		if (flyTo.length() > 50)
			position += velocity * dt;
	}
	sceneNode->setPosition(Ogre::Vector3(this->position.x, this->position.y, 2));

}

void Bird::Leave()
{

}
