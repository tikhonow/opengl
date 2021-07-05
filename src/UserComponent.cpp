//
// Created by Ruslan Tikhonov on 23/06/2021.
//

#include "UserComponent.h"

#include "glf3.h"

#include <iostream>
#include <World.h>

#define WORLD_UP cglm::Vec3(0.0f, 1.0f, 0.0f)

const float CAMERA_DEFAULT_SPEED = 3.5f;
const float CAMERA_DEFAULT_SENSITIVITY = 0.3f;

UserComponent::UserComponent()
    : MouseSensitivity(CAMERA_DEFAULT_SENSITIVITY), MovementSpeed(CAMERA_DEFAULT_SPEED),
      yaw(0.0f), pitch(0.0f), camFront(0.f), DynamicComponent()
{}

void UserComponent::configure(Entity* entity)
{
    Component::configure(entity);
    transform = entity->get<TransformComponent>();
    camera = entity->get<CameraComponent>();
    updateCameraRotation();
}

void UserComponent::onInput(GLFWwindow* window, double dt)
{
    float forwards = 0, sideways = 0, up = 0;
    float forwards_ = 0, sideways_ = 0, up_ = 0;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        forwards += -1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        forwards += 1;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        sideways += -1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        sideways += 1;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        up += -1;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        up += 1;


    moveCamera(forwards, sideways, up, dt);
}

void UserComponent::onMouseMove(double xpos, double ypos)
{
    if (firstMouse) {
        firstMouse = false;
        lastMouseX = xpos;
        lastMouseY = ypos;
    }

    float xoffset = (xpos - lastMouseX);
    float yoffset = (lastMouseY - ypos);
    lastMouseX = (float) xpos;
    lastMouseY = (float) ypos;

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    yaw -= xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraRotation();
}

void UserComponent::onMouseScroll(double horizontal, double vertical)
{
    float min = 1.0f;
    float max = 45.0f;

    if (camera->FOV <= max && camera->FOV >= min)
        camera->FOV -= vertical;

    if (camera->FOV <= min)
        camera->FOV = min;

    if (camera->FOV >= max)
        camera->FOV = max;
}

void UserComponent::moveCamera(float forwards, float sideways, float up, double dt)
{

    cglm::Vec3 direction = cglm::Vec3(forwards, sideways, up);

    if (direction.x == 0 && direction.y == 0 && direction.z == 0)
        return;

    auto velocity = static_cast<float>(MovementSpeed*dt);

    direction = cglm::normalize(direction)*velocity;

    cglm::Vec3 camForward = camera->front(transform);
    camForward.y = 0;
    camForward = cglm::normalize(camForward);

    transform->position += -direction.x * camForward + direction.y * cglm::cross(camForward, cglm::Vec3(0.0f, 1.0f, 0.0f)) + direction.z*cglm::Vec3(0.0f, 1.0f, 0.0f);
}

void UserComponent::updateCameraRotation()
{
    cglm::Vec3 pitchVec(0.f);

    pitchVec.x = cos(cglm::radians(pitch));
    pitchVec.z = sin(cglm::radians(pitch));
    pitchVec = cglm::normalize(pitchVec);

    transform->rotation = cglm::quat(1.0f, 0.f, 0.f, 0.f);
    transform->rotation = transform->rotation * pitchVec;

    transform->rotation = cglm::angleAxis(cglm::radians(yaw), cglm::Vec3(0.f, 1.f, 0.f)) * transform->rotation;
}