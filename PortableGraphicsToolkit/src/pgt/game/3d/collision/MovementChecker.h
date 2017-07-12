#pragma once
#include <pgt/maths/maths.h>
#include "Collider.h"
#include "AABB.h"
namespace pgt {
    template <class COLLIDER_TYPE>
    class MovementChecker {
        COLLIDER_TYPE* _collider;
        COLLIDER_TYPE _target_collider;
        AABB _simple_check;
        vec3 _movement;
        std::vector<Collider*> _problematic_colliders;

      public:
        MovementChecker(){};
        ~MovementChecker(){};

      public:
        AABB& getSimplifiedCheckingBounds()
        {
            return _simple_check;
        }
        void setMovingOperation(COLLIDER_TYPE* collider, vec3 move)
        {
            _problematic_colliders.clear();
            _collider = collider;
            _target_collider = *_collider;
            _simple_check = _collider->createSurroundingAABB();
            vec3 pos = _simple_check.getPosition();
            vec3 size = _simple_check.getSize();
            if (move.x > 0) {
                size.x += move.x;
            }
            else {
                pos.x += move.x;
                size.x -= move.x;
            }
            if (move.y > 0) {
                size.y += move.y;
            }
            else {
                pos.y += move.y;
                size.y -= move.y;
            }
            if (move.z > 0) {
                size.z += move.z;
            }
            else {
                pos.z += move.z;
                size.z -= move.z;
            }
            _simple_check.setPosition(pos);
            _simple_check.setSize(size);
            _movement = move;
        }
        void checkAgainstCollider(Collider* c)
        {
            if (c->quickCheckAsAABB(_simple_check)) {
                _problematic_colliders.push_back(c);
            }
        }
        vec3 getResultingMove()
        {
            if (collidesProblematic(
                    vec3(_movement.x, _movement.y, _movement.z))) {
                if (!collidesProblematic(vec3(_movement.x, 0, _movement.z))) {
                    _movement.y = 0;
                    return _movement;
                }
                if (!collidesProblematic(vec3(_movement.x, _movement.y, 0))) {
                    _movement.z = 0;
                    return _movement;
                }
                if (!collidesProblematic(vec3(0, _movement.y, _movement.z))) {
                    _movement.x = 0;
                    return _movement;
                }
                if (!collidesProblematic(vec3(0, 0, _movement.z))) {
                    _movement.x = 0;
                    _movement.y = 0;
                    return _movement;
                }
                if (!collidesProblematic(vec3(_movement.x, 0, 0))) {
                    _movement.y = 0;
                    _movement.z = 0;
                    return _movement;
                }
                if (!collidesProblematic(vec3(0, _movement.y, 0))) {
                    _movement.x = 0;
                    _movement.z = 0;
                    return _movement;
                }
                return vec3(0, 0, 0);
            }
            return _movement;
        }

      private:
        bool collidesProblematic(vec3&& move){
            return collidesProblematic(move);
        }
        bool collidesProblematic(vec3& move)
        {
            _target_collider.setPosition(_collider->getPosition() + move);
            for (Collider* c : _problematic_colliders) {
                if (c->collidesWith(_target_collider)) return true;
            }
            return false;
        }
    };
}