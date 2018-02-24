#ifndef H_TRANSFORM
#define H_TRANSFORM
#include <Box2D/Box2D.h>
#include "vector.hpp"

typedef struct Transform2D
{
    VectorF2D pos;
    float rot;
    Transform2D(VectorF2D pos, float rot) : pos(pos), rot(rot) {}
    Transform2D(b2Transform t) : pos(VectorF2D(t.p.x, t.p.y)), rot(t.q.GetAngle() * b2_pi / 180) {}
    Transform2D operator+(Transform2D &t)
    {
        return Transform2D(pos + t.pos, rot + t.rot);
    }
    Transform2D &operator+=(Transform2D &t)
    {
        pos += t.pos;
        rot += t.rot;
        return *this;
    }
} Transform2D;
#endif