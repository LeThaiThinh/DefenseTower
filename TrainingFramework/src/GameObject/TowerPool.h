#pragma once
#include "../BaseTower.h"
class TowerPool
{
private:
    std::list<std::shared_ptr<BaseTower>> resources;

    static TowerPool* instance;
    TowerPool() {}

public:
    static TowerPool* getInstance()
    {
        if (instance == 0)
        {
            instance = new TowerPool;
        }
        return instance;
    }
    std::shared_ptr<BaseTower> getResource(TowerType type)
    {
        if (resources.empty())
        {
            return std::make_shared<BaseTower>(type);
        }
        else
        {
            std::shared_ptr<BaseTower> resource = resources.front();
            resource->SetType(type);
            resources.pop_front();
            return resource;
        }
    }
    void returnResource(std::shared_ptr<BaseTower> object)
    {
        object->Reset();
        resources.push_back(object);
    }
};