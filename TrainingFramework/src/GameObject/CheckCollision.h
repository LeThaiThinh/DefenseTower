#pragma once
#include "MainCharacter.h"
#include "DefensiveManager.h"
class CheckCollision
{
public:
    CheckCollision() {};
    ~CheckCollision() {};
    static bool LineIntersectsRect(Vector3 p1, Vector3 p2, std::shared_ptr<Sprite2D> r)
    {
        return LineIntersectsLine(p1, p2, r->GetLeftTop(), r->GetRightTop()) ||
            LineIntersectsLine(p1, p2, r->GetRightTop(), r->GetRightBottom()) ||
            LineIntersectsLine(p1, p2, r->GetRightBottom(), r->GetLeftBottom()) ||
            LineIntersectsLine(p1, p2, r->GetLeftBottom(), r->GetLeftTop());
    }

    static bool LineIntersectsLine(Vector3 l1p1, Vector3 l1p2, Vector3 l2p1, Vector3 l2p2)
    {
        float q = (l1p1.y - l2p1.y) * (l2p2.x - l2p1.x) - (l1p1.x - l2p1.x) * (l2p2.y - l2p1.y);
        float d = (l1p2.x - l1p1.x) * (l2p2.y - l2p1.y) - (l1p2.y - l1p1.y) * (l2p2.x - l2p1.x);

        if (d == 0)
        {
            return false;
        }

        float r = q / d;

        q = (l1p1.y - l2p1.y) * (l1p2.x - l1p1.x) - (l1p1.x - l2p1.x) * (l1p2.y - l1p1.y);
        float s = q / d;

        if (r < 0 || r > 1 || s < 0 || s > 1)
        {
            return false;
        }

        return true;
    }
private:

};
