#pragma once
#include "MainCharacter.h"
#include "Defensive/BaseDefensive.h"
#include "Defensive/BaseDefensive.h"
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
    static bool LineIntersectsRectPathing(Vector3 p1, Vector3 p2, std::shared_ptr<Sprite2D> r)
    {
        return LineIntersectsLinePathing(p1, p2, r->GetLeftTop(), r->GetRightTop()) ||
            LineIntersectsLinePathing(p1, p2, r->GetRightTop(), r->GetRightBottom()) ||
            LineIntersectsLinePathing(p1, p2, r->GetRightBottom(), r->GetLeftBottom()) ||
            LineIntersectsLinePathing(p1, p2, r->GetLeftBottom(), r->GetLeftTop()) ;
    }
    static bool LineIntersectsRectPathing2(Vector3 p1, Vector3 p2, std::shared_ptr<Sprite2D> r)
    {
        return LineIntersectsLinePathing(p1, p2, r->GetLeftTop(), r->GetRightTop()) ||
            LineIntersectsLinePathing(p1, p2, r->GetRightTop(), r->GetRightBottom()) ||
            LineIntersectsLinePathing(p1, p2, r->GetRightBottom(), r->GetLeftBottom()) ||
            LineIntersectsLinePathing(p1, p2, r->GetLeftBottom(), r->GetLeftTop()) ||
            (p1 == r->GetLeftTop() && p2 == r->GetRightBottom()) ||
            (p1 == r->GetLeftBottom() && p2 == r->GetRightTop()) ||
            (p2 == r->GetLeftTop() && p1 == r->GetRightBottom()) ||
            (p2 == r->GetLeftBottom() && p1 == r->GetRightTop());
    }
    static bool PointInRect(Vector3 p1, std::shared_ptr<Sprite2D> r)
    {
        return p1.x > r->GetLeftTop().x && 
            p1.x < r->GetRightTop().x &&
            p1.y > r->GetRightTop().y &&
            p1.y < r->GetRightBottom().y;
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
    static bool LineIntersectsLinePathing(Vector3 l1p1, Vector3 l1p2, Vector3 l2p1, Vector3 l2p2)
    {
        float q = (l1p1.y - l2p1.y) * (l2p2.x - l2p1.x) - (l1p1.x - l2p1.x) * (l2p2.y - l2p1.y);
        float d = (l1p2.x - l1p1.x) * (l2p2.y - l2p1.y) - (l1p2.y - l1p1.y) * (l2p2.x - l2p1.x);
        //std::cout << l1p1.x <<" "<< l1p2.y <<" "<< l2p1.x <<" "<< l2p2.y << std::endl;
        //std::cout << l1p1.x - l1p2.x << " " << l1p2.x - l2p1.x << " " << l2p1.x - l2p2.x <<std::endl;
        if (l1p1.x == l1p2.x && l1p2.x == l2p1.x && l2p1.x == l2p2.x 
            && ((l1p1.y - l2p1.y) * (l1p1.y - l2p2.y) < 0 || (l1p2.y - l2p1.y) * (l1p2.y - l2p2.y) < 0 || (l2p1.y - l1p1.y) * (l2p1.y - l1p2.y) < 0 || (l2p2.y - l1p1.y) * (l2p2.y - l1p2.y) < 0)) {
            //std::cout <<"  "<< l1p1.y - l2p1.y << " " << l1p1.y - l2p2.y << " " << l1p2.y - l2p1.y << " " << l1p2.y - l2p2.y << std::endl;
            //printf("intersectt");
            return true;
        }
        if (l1p1.y ==l1p2.y && l1p2.y == l2p1.y && l2p1.y == l2p2.y
            && ((l1p1.x - l2p1.x) * (l1p1.x - l2p2.x) < 0 || (l1p2.x - l2p1.x) * (l1p2.x - l2p2.x) < 0 || (l2p1.x - l1p1.x) * (l2p1.x - l1p2.x) < 0 || (l2p2.x - l1p1.x) * (l2p2.x - l1p2.x) < 0)) {
            //printf("intersectt");
            return true;
        }

        if (d == 0)
        {
            return false;
        }


        float r = q / d;

        q = (l1p1.y - l2p1.y) * (l1p2.x - l1p1.x) - (l1p1.x - l2p1.x) * (l1p2.y - l1p1.y);
        float s = q / d;

        if (r <= 0 || r >= 1 || s <= 0 || s >= 1)
        {
            return false;
        }

        return true;
    }
    static bool RectIntersectRect(std::shared_ptr<Sprite2D> r1,std::shared_ptr<Sprite2D> r2) {
        if (r1->GetPosition().x + r1->GetWidth() / 2.f > r2->GetPosition().x - r2->GetWidth() / 2.f && (r1->GetPosition().x - r1->GetWidth() / 2.f < r2->GetPosition().x + r2->GetWidth() / 2.f)
            && (r1->GetPosition().y + r1->GetHeight() / 2.f > r2->GetPosition().y - r2->GetHeight() / 2.f) && (r1->GetPosition().y - r1->GetHeight() / 2.f < r2->GetPosition().y + r2->GetWidth() / 2.f)) {
            return true;
        }
        else return false;
    }
private:

};
