//
// Created by Ruslan Tikhonov on 21/06/2021.
//


#pragma once

class Entity;

class Component
{
public:
    explicit Component() : entity(nullptr)
    {}

    virtual ~Component() = default;

    virtual void destroy()
    {};

    Entity* getEntity(int id) const
    {
        return entity[id];
    }

    virtual void configure(Entity* entity)
    {
        this->entity.insert(entity);
    }

protected:
    std::unordered_map<Entity*> entity;
};