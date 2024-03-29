//
// Created by Ruslan Tikhonov on 21/06/2021.
//

#include "graphics/Rendering.h"
#include "Game.h"
#include "World.h"

#include <iostream>

#define UPDATE_TICKS_PER_SECOND 120

Game::Game(std::string windowTitle, unsigned int windowWidth, unsigned int windowHeight)
        : screenWidth(windowWidth), screenHeight(windowHeight), activeWorld(nullptr)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    glfwWindowHint(GLFW_SAMPLES, 4); // Anti aliasing

    window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    // Callbacks
    glfwSetFramebufferSizeCallback(window, Game::window_resize_callback);

    glfwSetCursorPosCallback(window, Game::mouseMoveCallback);
    glfwSetScrollCallback(window, Game::mouseScrollCallback);

    { // width and height might differ on retina screens
        int width = 0, height = 0;

        glfwGetFramebufferSize(window, &width, &height);
        screenWidth = (unsigned)width;
        screenHeight = (unsigned)height;
    }

    lastFrame = glfwGetTime();
    fixedUpdateTime = 0;
}

Game::~Game()
{
    glfwDestroyWindow(window);
}

bool Game::update()
{
    double currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;

    double fixedUpdateRate = 1.0/static_cast<double>(UPDATE_TICKS_PER_SECOND);
    fixedUpdateTime += dt;
    while (fixedUpdateTime > fixedUpdateRate) {
        fixedUpdateTime -= fixedUpdateRate;
        if (activeWorld)
        {
            activeWorld->fixedUpdate();
        }
    }

    activeWorld->onInput(window, dt);

    glfwSwapBuffers(window);
    glfwPollEvents();

    if (activeWorld) {
        activeWorld->update(dt);
        activeWorld->render();
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    return !glfwWindowShouldClose(window);
}

double Game::deltaTime() const
{
    return dt;
}

World* Game::getActiveWorld() const
{
    return activeWorld;
}

void Game::setActiveWorld(World* activeWorld)
{
    this->activeWorld = activeWorld;
    this->activeWorld->game = this;
}

void Game::window_resize_callback(GLFWwindow* window, int width, int height)
{
    Game* game = (Game*)glfwGetWindowUserPointer(window);

    glViewport(0, 0, width, height);

    game->screenHeight = (unsigned)width;
    game->screenHeight = (unsigned)height;
}

void Game::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    Game* game = (Game*)glfwGetWindowUserPointer(window);

    World* world = game->getActiveWorld();
    if (world)
        world->onMouseMove(xpos, ypos);
}

void Game::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Game* game = (Game*)glfwGetWindowUserPointer(window);

    World* world = game->getActiveWorld();
    if (world)
        world->onMouseScroll(xoffset, yoffset);
}
