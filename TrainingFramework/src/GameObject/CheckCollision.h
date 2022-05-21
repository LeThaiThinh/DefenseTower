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
    static bool LineIntersectsRect2(Vector3 p1, Vector3 p2, std::shared_ptr<Sprite2D> r)
    {
        return LineIntersectsLine2(p1, p2, r->GetLeftTop(), r->GetRightTop()) ||
            LineIntersectsLine2(p1, p2, r->GetRightTop(), r->GetRightBottom()) ||
            LineIntersectsLine2(p1, p2, r->GetRightBottom(), r->GetLeftBottom()) ||
            LineIntersectsLine2(p1, p2, r->GetLeftBottom(), r->GetLeftTop());
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
            (p2 == r->GetLeftBottom() && p1 == r->GetRightTop()) ||
            ((PointInRect0(p1,r))&&PointInRect0(p2,r));
    }
    static bool PointInRect(Vector3 p1, std::shared_ptr<Sprite2D> r)
    {
        return p1.x >= r->GetLeftTop().x && 
            p1.x <= r->GetRightTop().x &&
            p1.y >= r->GetRightTop().y &&
            p1.y <= r->GetRightBottom().y;
    }
    static bool PointInRect0(Vector3 p1, std::shared_ptr<Sprite2D> r)
    {
        return p1.x > r->GetLeftTop().x &&
            p1.x < r->GetRightTop().x &&
            p1.y > r->GetRightTop().y &&
            p1.y < r->GetRightBottom().y;
    }
    static bool PointInRectI(Vector3 p1, std::shared_ptr<Sprite2D> r)
    {
        return p1.x >= r->GetLeftTopI().x &&
            p1.x <= r->GetRightTopI().x &&
            p1.y >= r->GetRightTopI().y &&
            p1.y <= r->GetRightBottomI().y;
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
    static bool LineIntersectsLine2(Vector3 l1p1, Vector3 l1p2, Vector3 l2p1, Vector3 l2p2)
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

        if (r <= 0 || r >= 1 || s <= 0 || s >= 1)
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
        return r1->GetRightBottom().x >= r2->GetLeftBottom().x &&     // r1 right edge past r2 left
            r1->GetLeftBottom().x <= r2->GetRightBottom().x &&       // r1 left edge past r2 right
            r1->GetLeftBottom().y >= r2->GetLeftTop().y &&       // r1 top edge past r2 bottom
            r1->GetLeftTop().y <= r2->GetRightBottom().y;
    }
    static bool CheckLesser90Degree(std::shared_ptr<Sprite2D> p1, std::shared_ptr<Sprite2D> p2, std::shared_ptr<Sprite2D> p3) {
        int ux = p2->GetPosition().x - p1->GetPosition().x;
        int uy = p2->GetPosition().y - p1->GetPosition().y;   // u = (ux,uy) = vector from p1 to p2
        int vx = p3->GetPosition().x - p1->GetPosition().x;
        int vy = p3->GetPosition().y - p1->GetPosition().y;   // v = (vx,vy) = vector from p1 to p3
        int d = ux * vx + uy * vy;               // Dot product of u and v
        return d > 0;
    }
private:

};
