#pragma once
#include "Collider.h"
namespace pgt
{
    class AABB : public Collider
    {
    protected:
        vec3 _size;

    public:
        AABB();
        AABB(float x, float y, float z, float size_x, float size_y, float size_z);
        virtual ~AABB();
        virtual const vec3 &getSize() const;
        virtual void setSize(const vec3 &siz);

    public:
        virtual bool collidesWith(AABB &c);
        virtual AABB createSurroundingAABB();
        virtual bool quickCheckAsAABB(AABB &other);
    };
}