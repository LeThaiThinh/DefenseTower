#pragma once
template <class T>
class ObjectPool
{
private:
    std::list<std::shared_ptr<T>> resources;

    static ObjectPool* instance;
    ObjectPool() {}

public:
    static ObjectPool* getInstance()
    {
        if (instance == 0)
        {
            instance = new ObjectPool;
        }
        return instance;
    }
    std::shared_ptr<T> getResource()
    {
        if (resources.empty())
        {
            return std::make_shared<T>();
        }
        else
        {
            std::shared_ptr<T> resource = resources.front();
            resources.pop_front();
            return resource;
        }
    }
    std::shared_ptr<T> getResource2(Vector3 position)
    {
        if (resources.empty())
        {
            return new T(position);
        }
        else
        {
            T* resource = resources.front();
            resource->Set2DPosition(Vector2(position.x, position.y));
            resources.pop_front();
            return resource;
        }
    }
    void returnResource(T* object)
    {
        object->Reset();
        resources.push_back(object);
    }
};