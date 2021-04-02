#pragma once

#include "component.h"
#include <map>
#include <memory>
#include <set>
#include <string>
#include <typeindex>

class Entity 
{
	friend class EntityManager;

private:
	std::map<std::type_index, std::shared_ptr<ComponentInterface>> components;
	std::string tag = ""; // Mabe try to do something better?
	size_t id;
	void SetTag(const std::string &tag_)
	{
		tag = tag_;
	}

public:
    std::string GetTag() const 
    {
      return tag;
    }
  //Запрос определенной компоненты
    template<typename Component>
    std::shared_ptr<Component> Get() const 
    {
      auto c = components.at(typeid(Component));
      return std::dynamic_pointer_cast<Component>(c);
    }
    // Добавление множества компонент
    template<typename Component, typename... Args>
    void Add(Args &&... args) 
    {
      components[typeid(Component)] = std::make_shared<Component>(std::forward<Args>(args)...);
    }
    //Добавление одной компоненты
    template<typename Component>
    void Add(std::shared_ptr<Component> component) 
    {
      components[typeid(Component)] = component;
    }
    //Запрос: имеется ли данная компонента?
    template<typename Component>
    bool Contains() const 
    {
      return components.count(typeid(Component)) != 0;
    }

    size_t GetId() const
    {
      return id;
    }

    template<typename Component>
    void Delete() 
    {
      components.erase(typeid(Component));
    }

	bool operator<=(const Entity &rhs) const {
		return !(rhs < *this);
	}
	bool operator>=(const Entity &rhs) const {
		return !(*this < rhs);
	}
    bool operator<(const Entity &rhs) const {
      return id < rhs.id;
    }
    bool operator>(const Entity &rhs) const {
      return rhs < *this;
    }
   
	virtual ~Entity() {
		components.clear();
	}
   
};
