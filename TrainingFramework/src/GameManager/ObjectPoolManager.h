#pragma once
template <class T>
class ObjectPoolManager:public CSingleton<ObjectPoolManager<T>>
{
private:
    std::list<std::shared_ptr<T>> resources;
    std::list<std::shared_ptr<T>> m_resourceList;
    std::list<std::shared_ptr<T>> m_resourceListRemove;

public:
	std::shared_ptr<T> AddResource() {
		std::shared_ptr<T> resource = GetResource();
        m_resourceList.push_back(resource);
		return resource;
	};
	void Update(float deltaTime) {
        m_resourceListRemove.clear();
		for (auto resource : m_resourceList) {
            resource->Update(deltaTime);
			if (resource->IsDisposable())
                m_resourceListRemove.push_back(resource);
		}
	};
    std::list<std::shared_ptr<T>> Remove() {
		for (auto resource : m_resourceListRemove) {
			m_resourceList.remove(resource);
            ReturnResource(resource);
		}
        return m_resourceListRemove;
	}
	void Draw() {
		for (auto resource : m_resourceList) {
            resource->Draw();
		}
	}
    std::shared_ptr<T> GetResource()
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
    void ReturnResource(std::shared_ptr<T> object)
    {
        object->Reset();
        resources.push_back(object);
    }
};