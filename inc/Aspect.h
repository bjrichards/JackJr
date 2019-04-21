#ifndef __Aspect_h_
#define __Aspect_h_

#include<OgreVector3.h>

class Entity381;    //Forward declaration of the Entity381 class
class Command;
class Aspect
{
public:
  Aspect(Entity381* ent);
  virtual ~Aspect();

  Entity381* entity;

  virtual void Tick(float dt);
  virtual void AddCommand(Command* c);
  virtual void SetCommand(Command* c);


protected:

};



class Renderable : Aspect
{
public:
	Renderable(Entity381* ent);
	~Renderable();

	void Tick(float dt);
};



#endif // #ifndef __Aspect_h_
