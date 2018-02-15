#include "body_data.h"
#include <iostream>
#include <vector>
#include <algorithm>

int BodyData::nextID = 0;
BodyData::BodyData()
{
	id = ++nextID;
}
bool BodyData::operator==(const BodyData &Ref) const
{
	return (this->body_type == Ref.body_type);
}
void BodyData::collisionStart(int _id)
{
	collisions.push_back(_id);
}
void BodyData::collisionEnd(int _id)
{
	collisions.erase(std::remove(collisions.begin(), collisions.end(), _id), collisions.end());
}