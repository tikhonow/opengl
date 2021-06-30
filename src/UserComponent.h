//
// Created by Ruslan Tikhonov on 23/06/2021.
//


#pragma once

#include "components/CameraComponent.h"
#include "components/TransformComponent.h"
#include "components/DynamicComponent.h"

class UserComponent : public DynamicComponent
{
public:
    UserComponent();

    float MovementSpeed;
    float MouseSensitivity;

    float yaw, pitch;

    glm::vec3 camFront;

    void updateCameraRotation();

    void moveCamera(float forwards, float sideways, float up, double dt);

    void configure(Entity* entity) override;

    void onInput(GLFWwindow* window, double dt) override;

    void onMouseMove(double xpos, double ypos) override;

    void onMouseScroll(double horizontal, double vertical) override;

private:
    TransformComponent* transform;
    CameraComponent* camera;

    bool firstMouse = true;
    double lastMouseX, lastMouseY;
};

