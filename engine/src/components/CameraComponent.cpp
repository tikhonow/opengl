//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "graphics/Shader.h"
#include <World.h>

#define WORLD_UP cglm::Vec3(0.0f, 1.0f, 0.0f)

CameraComponent::CameraComponent()
        : FOV(CAMERA_DEFAULT_FOV),
          Component()
{

}

cglm::Mat4 CameraComponent::GetViewMatrix() const
{
    auto* transform = entity->get<TransformComponent>();

    cglm::Mat4 mat = glm::lookAt(transform->position,
                                transform->position+front(transform), WORLD_UP);

    return mat;
}

cglm::Mat4 CameraComponent::getProjectionMatrix() const
{
    Game* game = entity->world->game;

    cglm::Mat4 projection = glm::perspective(glm::radians(FOV), (float)game->screenWidth / (float)game->screenHeight,
                                            0.1f, 100.0f);

    return projection;
}

cglm::Vec3 CameraComponent::front(const TransformComponent* transform) const
{
    cglm::Vec3 front = transform->rotation * cglm::Vec3(1.0f, 0.0f, 0.0f);
    front = glm::normalize(front);
    return front;
}

