#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>
//#include <UnitAI.h>
#include <Types381.h>

#include <Engine.h>

class Entity381
{
public:
  Entity381(Engine *engine, Ogre::Vector3 pos, int identity);
  virtual ~Entity381();

  Engine *engine;

  //static data
  int identity;
  std::string name;
  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;
  float acceleration, turnRate;
  float minSpeed, maxSpeed;

  //dynamic data
  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  bool isSelected;
  float desiredHeading, desiredSpeed;
  float heading, speed;


  EntityTypes entityType;
  std::vector<Aspect* > aspects;

  void Init();

  void Tick(float dt);

protected:


};



class Carrier: public Entity381 {
public:
	Carrier(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Carrier();

};


#endif // #ifndef __Entity381_h_
