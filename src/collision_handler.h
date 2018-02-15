#ifndef H_COLLISION_HANDLE
#define H_COLLISION_HANDLE
#include <iostream>
#include <Box2D/Box2D.h>
#include "body_data.h"

class CollisionHandler2D : public b2ContactListener
{
	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
};
#endif