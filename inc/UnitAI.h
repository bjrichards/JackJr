/*
 * UnitAI.h
 *
 *  Created on: Apr 6, 2019
 *      Author: brichards
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_

#include <Aspect.h>
#include <Command.h>

class UnitAI : Aspect
{
public:
	UnitAI(Entity381 *ent);
	~UnitAI();

	void Tick(float dt);
	void AddCommand(Command* c);
	void SetCommand(Command* c);

	std::vector<Command* > commands;
};



#endif /* INC_UNITAI_H_ */
