//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#pragma once

#include <glm/matrix.hpp>
#include "Component.h"

class ModelComponent : public Component
{
public:
    ModelComponent(int modelId);

    ModelComponent();

    int getModelId() const;

    void setModelId(int modelId);

    int getShaderId() const;

    void setShader(int shaderId);

    cglm::Mat4 getModelMatrix();

private:
    int modelId;
    int shaderId;
};


