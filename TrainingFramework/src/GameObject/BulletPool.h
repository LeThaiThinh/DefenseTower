#pragma once
#include "Bullet.h"
template <class T>
class BulletPool
{
private:
    std::list<std::shared_ptr<Bullet>> resources;

    static BulletPool* instance;
    BulletPool() {}

public:
    static BulletPool* getInstance()
    {
        if (instance == 0)
        {
            instance = new BulletPool;
        }
        return instance;
    }
    std::shared_ptr<Bullet> getResource(BulletType type)
    {
        if (resources.empty())
        {
            return std::make_shared<Bullet>(type);
        }
        else
        {
            std::shared_ptr<Bullet> resource = resources.front();
            resource->SetType(type);
            resources.pop_front();
            return resource;
        }
    }
    void returnResource(std::shared_ptr<Bullet> object)
    {
        object->Reset();
        resources.push_back(object);
    }
};