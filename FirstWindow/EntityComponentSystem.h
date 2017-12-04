#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity
{
public:
	void update()
	{
		for (auto& c : m_vComponents) c->update();
	}

	void draw()
	{
		for (auto& c : m_vComponents) c->draw();
	}

	bool isActive() const { return m_bActive; }
	void destroy() { m_bActive = false; }

	template <typename T> bool hasComponent() const
	{
		return m_aComponentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs> (mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		m_vComponents.emplace_back(std::move(uPtr));

		m_aComponentArray[getComponentTypeID<T>()] = c;
		m_aComponentBitset[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const
	{
		auto ptr(m_aComponentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	bool m_bActive = true;
	std::vector<std::unique_ptr<Component>> m_vComponents;

	ComponentArray m_aComponentArray;
	ComponentBitSet m_aComponentBitset;

};

class Manager
{
public:
	void update()
	{
		for (auto& e : m_vEntities) e->update();
	}

	void draw()
	{
		for (auto& e : m_vEntities) e->draw();
	}

	void refresh()
	{
		m_vEntities.erase(
			std::remove_if(
				std::begin(m_vEntities),
				std::end(m_vEntities),
				[](const std::unique_ptr<Entity> &mEntity) { return !mEntity->isActive(); }
			),
			std::end(m_vEntities)
		);
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		m_vEntities.emplace_back(std::move(uPtr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> m_vEntities;

};