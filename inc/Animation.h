/*
 * Animation.h
 *
 *  Created on: Apr 10, 2019
 *      Author: brichards
 */

#ifndef INC_ANIMATION_H_
#define INC_ANIMATION_H_

#include <Aspect.h>
#include <string.h>

class Animation : Aspect
{
public:
	Animation(Entity381 *ent);
	~Animation();

	void Tick(float dt);

	std::vector<std::string> textures;
};


#endif /* INC_ANIMATION_H_ */
