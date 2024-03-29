/*
 * GfxMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GFXMGR_H_
#define GFXMGR_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <OgreOverlaySystem.h>

#include <Sample.h>
#include <SdkTrays.h>

#include <Mgr.h>


class GfxMgr:
		public Mgr,
		public Ogre::WindowEventListener,
		public Ogre::FrameListener {
public:
	GfxMgr(Engine *engine);
	virtual ~GfxMgr();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual void windowClosed(Ogre::RenderWindow* rw);
//---------------
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

	void MakeBuildings();
	void MakeGround();
	Ogre::Plane oceanSurface;

	Ogre::Plane leftBuilding;
	Ogre::Plane rightBuilding;
	Ogre::Plane background;
	Ogre::Plane road;
	Ogre::Plane sidewalk;

	void MakeSky();

	//Ogre related stuff
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	Ogre::SceneNode *cameraNode, *pitchNode;
	//SdkTrayManager* mTrayMgr;

};

#endif /* GFXMGR_H_ */
