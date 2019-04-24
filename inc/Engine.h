/*
 * Engine.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef ENGINE_H_
#define ENGINE_H_

//#include <EntityMgr.h>
//#include <GameMgr.h>
//#include <GfxMgr.h>
//#include <InputMgr.h>
//#include <UiMgr.h>
#include <SoundMgr.h>

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;
class UiMgr;
//class SoundMgr;


class Engine {
public:
	Engine();
	virtual ~Engine();

	EntityMgr *entityMgr;
	GameMgr   *gameMgr;
	GfxMgr    *gfxMgr;
	InputMgr  *inputMgr;
	UiMgr	  *uiMgr;
	OgreSND::SoundMgr* soundMgr;

	void Init();
	void Run();
	void TickAll(float dt);
	void Cleanup();

	bool keepRunning;
};

#endif /* ENGINE_H_ */
