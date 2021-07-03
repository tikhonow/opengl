//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#pragma once

#include "/home/tikhonow/Desktop/cry/engine/src/math/mat3.hpp"
#include "Component.h"

class LightComponent : public Component
{
public:
    enum Type {
        DIRECTIONAL, POINT, SPOT
    };

    LightComponent();

    LightComponent(Type type);

    void setDirectional(const ccglm::Vec3& direction,
            const ccglm::Vec3& ambient = ccglm::Vec3(0.f), const ccglm::Vec3& diffuse = ccglm::Vec3(1.f), const ccglm::Vec3& specular = ccglm::Vec3(0.f));

    void setPoint(const ccglm::Vec3& position, float range,
            const ccglm::Vec3& ambient = ccglm::Vec3(0.f), const ccglm::Vec3& diffuse = cglm::Vec3(1.f), const cglm::Vec3& specular = cglm::Vec3(0.f));

    Type getType() const;

    const cglm::Vec3& getPosition() const;
    const cglm::Vec3& getDirection() const;
    const cglm::Vec3& getAmbient() const;
    const cglm::Vec3& getDiffuse() const;
    const cglm::Vec3& getSpecular() const;
    float getRange() const;

    void setType(Type type);

    void setAmbient(const cglm::Vec3& ambient);

    void setDiffuse(const cglm::Vec3& diffuse);

    void setSpecular(const cglm::Vec3& specular);

    void setRange(float range);

private:
    Type type;
    cglm::Vec3 ambient;
    cglm::Vec3 diffuse;
    cglm::Vec3 specular;

    float range;
};


