#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <Mgr.h>
#include <Player.h>
#include <Vine.h>
#include <Bird.h>
#include <Building.h>
#include <Entity381.h>

class Player;
class Vine;
class Building;
class Bird;

class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  Engine *engine;

  Player* player;
  std::vector<Vine*> vines;
  std::vector<Building*> buildings;
  std::vector<Bird*> birds;
  int seedCount;
  std::vector<Entity381*> entities;

  Ogre::SceneManager *sceneMgr;

  void Select(int index);
  void CreateNewVine(Ogre::Vector3 pos, int dir);
  void CreateNewBuilding(Ogre::Vector3 pos, int buildingType);
  void Tick(float dt);

protected:

private:
  void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
  void CreateDDG51(Ogre::Vector3 pos);
  void CreateCarrier(Ogre::Vector3 pos);
  void CreateSpeedBoat(Ogre::Vector3 pos);
  void CreateFrigate(Ogre::Vector3 pos);
  void CreateAlien(Ogre::Vector3 pos);
  int count;

};

#endif // #ifndef __EntityMgr_h_
