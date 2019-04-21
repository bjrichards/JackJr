/*
 * UnitAI.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: brichards
 */

#include <UnitAI.h>
#include <Entity381.h>
#include <Utils.h>

UnitAI::UnitAI(Entity381* ent):Aspect(ent){

}

UnitAI::~UnitAI(){

}

void UnitAI::Tick(float dt){
	if(!commands.empty()){
		commands[0]->tick(dt);
		if (commands[0]->done())
		{
			commands.erase(commands.begin());
			if(!commands.empty())
			{
				commands[0]->init();
			}
		}
	}
	else
	{
//		std::cout << "No commands!" << std::endl;
	}

	return;
}

void UnitAI::AddCommand(Command *c){
	commands.push_back(c);
}

void UnitAI::SetCommand(Command *c){
	commands.erase(commands.begin(), commands.end());
	commands.push_back(c);
	commands[0]->init();
}
