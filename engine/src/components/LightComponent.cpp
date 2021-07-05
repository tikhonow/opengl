//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#include "Entity.h"
#include "LightComponent.h"
#include "TransformComponent.h"

LightComponent::LightComponent() : type(DIRECTIONAL)
{}

LightComponent::LightComponent(LightComponent::Type type) : type(type)
{}

LightComponent::Type LightComponent::getType() const
{
    return type;
}

const cglm::Vec3& LightComponent::getPosition() const
{
    auto* transform = entity->get<TransformComponent>();
    return transform->position;
}

const cglm::Vec3& LightComponent::getDirection() const
{
    return getPosition();
}

const cglm::Vec3& LightComponent::getAmbient() const
{
    return ambient;
}

const cglm::Vec3& LightComponent::getDiffuse() const
{
    return diffuse;
}

const cglm::Vec3& LightComponent::getSpecular() const
{
    return specular;
}

float LightComponent::getRange() const
{
    return range;
}

void LightComponent::setDirectional(const cglm::Vec3& direction, const cglm::Vec3& ambient, const cglm::Vec3& diffuse,
                                    const cglm::Vec3& specular)
{
    this->type = DIRECTIONAL;
    auto* transform = entity->get<TransformComponent>();
    transform->position = direction;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void LightComponent::setPoint(const cglm::Vec3& position, float range,
                              const cglm::Vec3& ambient, const cglm::Vec3& diffuse, const cglm::Vec3& specular)
{
    this->type = POINT;
    auto* transform = entity->get<TransformComponent>();
    transform->position = position;
    this->range = range;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void LightComponent::setType(LightComponent::Type type)
{
    LightComponent::type = type;
}

void LightComponent::setAmbient(const cglm::Vec3& ambient)
{
    LightComponent::ambient = ambient;
}

void LightComponent::setDiffuse(const cglm::Vec3& diffuse)
{
    LightComponent::diffuse = diffuse;
}

void LightComponent::setSpecular(const cglm::Vec3& specular)
{
    LightComponent::specular = specular;
}

void LightComponent::setRange(float range)
{
    LightComponent::range = range;
}
