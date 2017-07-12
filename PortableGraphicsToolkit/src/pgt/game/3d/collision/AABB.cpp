#include "AABB.h"
namespace pgt
{
    AABB::AABB() : Collider()
    {
    }
    AABB::AABB(float x, float y, float z, float size_x, float size_y, float size_z)
        : Collider(x, y, z)
    {
        _size = vec3(size_x, size_y, size_z);
        _pos = vec3(x, y, z);
    }
    AABB::~AABB()
    {
    }

    const pgt::vec3 &AABB::getSize() const
    {
        return _size;
    }
    void AABB::setSize(const vec3 &siz)
    {
        _size = siz;
    }
    bool AABB::collidesWith(AABB &c)
    {
        return checkAABBCollision(_pos.x, _pos.y, _pos.z, _size.x, _size.y, _size.z, c._pos.x,
                                  c._pos.y, c._pos.z, c._size.x, c._size.y, c._size.z);
    }
    AABB AABB::createSurroundingAABB()
    {
        return *this;
    }

    bool AABB::quickCheckAsAABB(AABB &other)
    {
        return collidesWith(other);
    }
}