//
// Created by Ruslan Tikhonov on 21/06/2021.
//


#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

class TransformComponent : public Component
{
public:
    explicit TransformComponent(cglm::Vec3 pos = cglm::Vec3(0.0f), cglm::Vec3 scale = cglm::Vec3(1.0f),
            cglm::Quaternion rotation = cglm::Quaternion(cglm::Vec3(glm::radians(180.0f), 0.0f, 0.0f)));

    cglm::Mat4 applyTransform(cglm::Mat4 matrix);

    cglm::Vec3 position;
    cglm::Vec3 scale;
    cglm::Quaternion rotation;
};

