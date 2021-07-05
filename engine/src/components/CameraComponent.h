//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"
#include "TransformComponent.h"

class Shader;

const float CAMERA_DEFAULT_FOV = 45.0f;

class CameraComponent : public Component
{
public:
    float FOV;

    explicit CameraComponent();

    cglm::Mat4 GetViewMatrix() const;

    cglm::Mat4 getProjectionMatrix() const;

    cglm::Vec3 front(const TransformComponent* transform) const;

};

