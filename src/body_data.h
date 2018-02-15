
#ifndef H_BODYDATA
#define H_BODYDATA
#include <iostream>
#include <vector>
using namespace std;
enum bodyType
{
	RECTANGLE,
	CIRCLE,
	POLYGON
};
class BodyData
{
  public:
	bodyType body_type;
	int id;
	std::vector<int> collisions;
	BodyData();

	bool operator==(const BodyData &Ref) const;

	void collisionStart(int _id);
	void collisionEnd(int _id);

  private:
	static int nextID;
};
#endif
