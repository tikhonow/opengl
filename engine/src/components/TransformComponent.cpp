//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#include "TransformComponent.h"

TransformComponent::TransformComponent(cglm::Vec3 pos, cglm::Vec3 scale, cglm::Quaternion rotation)
    : Component(), position(pos), scale(scale), rotation(rotation)
{}

cglm::Mat4 TransformComponent::applyTransform(cglm::Mat4 matrix)
{
    matrix = glm::scale(matrix, scale);
//    matrix = cglm::Mat4_cast(rotation) * matrix;
    matrix = glm::translate(matrix, position);

    return matrix;
}
