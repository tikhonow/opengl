//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#pragma once

#include "Component.h"

class GLFWwindow;

class DynamicComponent : public Component
{
public:
    explicit DynamicComponent() : Component() {}

    virtual void update(float dt) {}
    virtual void fixedUpdate() {}

    virtual void onInput(GLFWwindow* window, double dt) {}
    virtual void onMouseMove(double xpos, double ypos) {}
    virtual void onMouseScroll(double horizontal, double vertical) {}
};
