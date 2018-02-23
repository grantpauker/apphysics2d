#include <Box2D/Box2D.h>
#include "collision_handler.hpp"
#include "body_data.hpp"


void CollisionHandler2D::BeginContact(b2Contact *contact)
{
	void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void *bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData && bodyUserData2)
	{
		int id1 = static_cast<BodyData *>(contact->GetFixtureA()->GetBody()->GetUserData())->id;
		int id2 = static_cast<BodyData *>(contact->GetFixtureB()->GetBody()->GetUserData())->id;

		static_cast<BodyData *>(bodyUserData)->collisionStart(id2);
		static_cast<BodyData *>(bodyUserData2)->collisionStart(id1);
	}
	// if (bodyUserData)
	// {
	// 	int other_id = static_cast<BodyData *>(contact->GetFixtureA()->GetBody()->GetUserData())->id;
	// 	std::cout << "start_id: " << static_cast<BodyData *>(bodyUserData)->id << endl;
	// 	static_cast<BodyData *>(bodyUserData)->collisionStart(other_id);
	// }
}

void CollisionHandler2D::EndContact(b2Contact *contact)
{
	void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void *bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData && bodyUserData2)
	{
		int id1 = static_cast<BodyData *>(contact->GetFixtureA()->GetBody()->GetUserData())->id;
		int id2 = static_cast<BodyData *>(contact->GetFixtureB()->GetBody()->GetUserData())->id;

		static_cast<BodyData *>(bodyUserData)->collisionEnd(id2);
		static_cast<BodyData *>(bodyUserData2)->collisionEnd(id1);
	}
	// if (bodyUserData)
	// {
	// 	int other_id = static_cast<BodyData *>(contact->GetFixtureA()->GetBody()->GetUserData())->id;
	// 	std::cout << "end_id: " << static_cast<BodyData *>(bodyUserData)->id << endl;
	// 	static_cast<BodyData *>(bodyUserData)->collisionEnd(other_id);
	// }
}
