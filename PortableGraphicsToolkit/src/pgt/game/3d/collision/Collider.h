#pragma once
#include <pgt/io/logger/logger.h>
#include <pgt/maths/maths.h>
namespace pgt
{
    class AABB;
    class Collider
    {
    public:
    protected:
        vec3 _pos;

    public:
        Collider();
        Collider(float x, float y, float z);
        virtual ~Collider();
        virtual bool collidesWith(AABB& c) = 0;
        virtual AABB createSurroundingAABB() = 0;
        virtual bool quickCheckAsAABB(AABB& other) = 0;

    public:
        virtual void setPosition(const vec3& pos);
        virtual void move(const vec3& mov)
        {
            setPosition(_pos + mov);
        }
        virtual const vec3& getPosition();

    public:
        static bool checkAABBCollision(float x1, float y1, float z1, float sx1, float sy1,
                                       float sz1, float x2, float y2, float z2, float sx2,
                                       float sy2, float sz2);
    };
}