//
// Created by Ruslan Tikhonov on 21/06/2021.
//
#pragma once


#include "Entity.h"

class GLFWwindow;

class DynamicSystem
{
public:
    void update(std::vector<Entity> &entities, double dt);
    void fixedUpdate(std::vector<Entity> &entity);

    void processInput(std::vector<Entity> &entity, GLFWwindow* window, double dt);
    void processMouseMove(std::vector<Entity> &entity, double xpos, double ypos);
    void processMouseScroll(std::vector<Entity> &entity, double horizontal, double vertical);
};