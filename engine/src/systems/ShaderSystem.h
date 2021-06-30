//
// Created by Ruslan Tikhonov on 21/06/2021.
//


#pragma once

#include "graphics/Shader.h"

#include <unordered_map>
#include <vector>

class CameraComponent;
class Entity;

class ShaderSystem
{
public:

    ShaderSystem();

    void updateShaders(std::vector<Entity>* entities, CameraComponent* activeCamera);

    int loadShader(const std::string& path);

    Shader* getShader(int id);
    std::unordered_map<int, Shader>* getShaders();

private:
    std::unordered_map<int, Shader> loadedShaders;
    int nextShaderId;

    struct ShaderBlocks {
        UniformBlock cameraBlock;
        UniformBlock directionalLightsBlock;
        UniformBlock pointLightsBlock;

        ShaderBlocks();
    };

    ShaderBlocks shaderBlocks;
};


