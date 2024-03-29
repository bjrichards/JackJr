/*
 * GameMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>
#include <string>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();

	void LoadNewLevel(std::string levelName);

	void MakeGround();
	void MakeBuildings();
	void MakeSky();
	void MakeEntities();

	Ogre::SceneNode *cameraNode;

	bool finish = false;
	Ogre::Vector3 finishLine;
	//float timer;
	int level = 0;
};

#endif /* GAMEMGR_H_ */
