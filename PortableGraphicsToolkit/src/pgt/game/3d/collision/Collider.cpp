#include "Collider.h"
namespace pgt
{
    Collider::Collider(float x, float y, float z)
    {
        _pos.x = x;
        _pos.y = y;
        _pos.z = z;
    }

    Collider::Collider()
    {
    }
    Collider::~Collider()
    {
    }
    void Collider::setPosition(const vec3& pos)
    {
        _pos.x = pos.x;
        _pos.y = pos.y;
        _pos.z = pos.z;
    }
    const pgt::vec3& Collider::getPosition()
    {
        return _pos;
    }

    bool Collider::checkAABBCollision(float x1, float y1, float z1, float sx1, float sy1, float sz1,
                                      float x2, float y2, float z2, float sx2, float sy2, float sz2)
    {
        return (((x1 >= x2 && x1 <= x2 + sx2) || (x2 >= x1 && x2 <= x1 + sx1)) &&
                ((y1 >= y2 && y1 <= y2 + sy2) || (y2 >= y1 && y2 <= y1 + sy1)) &&
                ((z1 >= z2 && z1 <= z2 + sz2) || (z2 >= z1 && z2 <= z1 + sz1)));
    }
}