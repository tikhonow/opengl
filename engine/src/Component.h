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

    Entity* getEntity() const
    {
        return entity;
    }

    virtual void configure(Entity* entity)
    {
        this->entity = entity;
    }

protected:
    Entity* entity;
};