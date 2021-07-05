//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#include "ModelComponent.h"
#include "Entity.h"
#include "components/TransformComponent.h"

ModelComponent::ModelComponent(int modelId) : Component(), modelId(modelId), shaderId(0)
{}

ModelComponent::ModelComponent() : Component(), modelId(0), shaderId(0)
{}

int ModelComponent::getModelId() const
{
    return modelId;
}

void ModelComponent::setModelId(int modelId)
{
    ModelComponent::modelId = modelId;
}

int ModelComponent::getShaderId() const
{
    return shaderId;
}

void ModelComponent::setShader(int shaderId)
{
    ModelComponent::shaderId = shaderId;
}

cglm::Mat4 ModelComponent::getModelMatrix()
{
    auto* transform = entity->get<TransformComponent>();

    cglm::Mat4 model = transform->applyTransform(cglm::Mat4(1.f));

    return model;
}
