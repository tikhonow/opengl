//
// Created by Ruslan Tikhonov on 15/06/2021.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stb_image.h>

#include "Game.h"
#include "graphics/Shader.h"
#include "components/CameraComponent.h"
#include "components/ModelComponent.h"
#include "components/LightComponent.h"
#include "graphics/Model.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexArray.h"
#include "Entity.h"
#include "UserComponent.h"
#include "World.h"

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
};

int main(int argc, char** argv)
{
    Game* game = new Game("Test Game", 800, 600);

    World world(game);
    game->setActiveWorld(&world);

    Entity* player = world.makeEntity();
    player->assign<TransformComponent>();
    player->assign<CameraComponent>();
    player->assign<UserComponent>();

    world.activeCamera = player->get<CameraComponent>();

    int modelId = world.getModelSystem().loadModel("../assets/models/nanosuit.obj");

    Entity* nanosuit = world.makeEntity();
    nanosuit->assign<TransformComponent>();
    nanosuit->assign<ModelComponent>(modelId);

    nanosuit->get<TransformComponent>()->position = glm::vec3(0.f, 2.f, 0.f);
    nanosuit->get<TransformComponent>()->scale = glm::vec3(0.1f);

    int shaderId = world.getShaderSystem().loadShader("assets/shaders/default.glsl");
    Shader* shader = world.getShaderSystem().getShader(shaderId);


    nanosuit->get<ModelComponent>()->setShader(shaderId);

    shader->use();
    shader->setFloat("material.shininess", 48.0f);
    shader->setVec3("dirLight.direction", 0.2f, -2.0f, -0.2f);
    shader->setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);
    shader->setVec3("dirLight.diffuse", 1.f, 1.f, 1.f);
    shader->setVec3("dirLight.specular", 0.f, 0.f, 0.f);

    Entity* dirLight = world.makeEntity();
    dirLight->assign<TransformComponent>();
    dirLight->assign<LightComponent>();

    auto* dirLightCmp = dirLight->get<LightComponent>();
    dirLightCmp->setDirectional(glm::vec3(0.2f, -2.0f, -0.2f));

    {
        Entity* pointLight = world.makeEntity();
        pointLight->assign<TransformComponent>();
        pointLight->assign<LightComponent>();

        auto* pointLightCmp = pointLight->get<LightComponent>();
        pointLightCmp->setPoint(glm::vec3(1.f, 0.f, 1.f), 0.5f);
        pointLightCmp->setAmbient(glm::vec3(1.0f, 0.f, 0.f));
        pointLightCmp->setSpecular(glm::vec3(0.0f, 1.f, 0.f));
    }

    {
        Entity* pointLight = world.makeEntity();
        pointLight->assign<TransformComponent>();
        pointLight->assign<LightComponent>();

        auto* pointLightCmp = pointLight->get<LightComponent>();
        pointLightCmp->setPoint(glm::vec3(1.f, 0.f, 1.f), 1.5f);
        pointLightCmp->setAmbient(glm::vec3(1.0f, 0.f, 0.f));
        pointLightCmp->setSpecular(glm::vec3(0.0f, 1.f, 0.f));
    }

    glfwSetInputMode(game->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader program ("../assets/shaders/textured-flat.glsl");
    program.use();

    program.setInt("texture1", 0);
    program.setInt("texture2", 1);

    // Verticies that make up a cube

    std::vector<float> cubeVertices = {
            // Back face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top-left
            // Front face
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top-left
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            // Left face
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-right
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
            // Right face
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            // Top face
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f  // bottom-left
    };

    std::vector<float> screenQuadVertices = {
            // Top left
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,

            // Bottom right
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
    };

    Texture diffuseTexture = Texture("assets/texture/container2.png");
    Texture specularTexture = Texture("assets/texture/container2_specular.png");

    Shader lampShader("../assets/shaders/lamp.glsl");
    Shader lightingShader("../assets/shaders/color-light.glsl");
    Shader screenShader("../assets/shaders/screen-texture.glsl");

    screenShader.use();
    screenShader.setInt("textureId", 0);

    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);

    VertexArray quadVAO;
    VertexBuffer quadVBO(&screenQuadVertices[0], screenQuadVertices.size()*sizeof(screenQuadVertices), 4*sizeof(float));


    VertexAttribute quadAttrs[] = {
            VertexAttribute(2, GL_FLOAT, 0),
            VertexAttribute(2, GL_FLOAT, 2*sizeof(float))
    };

    quadVAO.addBuffer(quadVBO, quadAttrs, 2);

    VertexArray lampVAO;

    VertexBuffer VBO(&cubeVertices[0], cubeVertices.size()*sizeof(cubeVertices), 8*sizeof(float));

    VertexAttribute attributes[]{
            VertexAttribute(3, GL_FLOAT, 0),
            VertexAttribute(3, GL_FLOAT, 3*sizeof(float)),
            VertexAttribute(3, GL_FLOAT, 6*sizeof(float))
    };

    lampVAO.addBuffer(VBO, attributes, 3);

    VertexArray cubeVAO;
    cubeVAO.addBuffer(VBO, attributes, 3);
    cubeVAO.use();


    // текстуры
    Texture texColorBuffer(game->screenWidth, game->screenHeight, GL_RGB);
    texColorBuffer.setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    texColorBuffer.use();

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    int frameCount = 0;
    float fpsTime = 0;

    while (game->update()) {

        //счетчик кадров
        frameCount++;
        fpsTime += game->deltaTime();

        if (frameCount%100 == 0) {
            glfwSetWindowTitle(game->window, std::string(
                    "CryBabyEngine - FPS: " + std::to_string((int) (1.0f/(fpsTime/100.0f)))).c_str());
            fpsTime = 0;
        }


        glm::mat4 view = player->get<CameraComponent>()->GetViewMatrix();

        glm::mat4 projection = player->get<CameraComponent>()->getProjectionMatrix();


        // свет
        lampShader.use();

        lampShader.setMat4("view", view);
        lampShader.setMat4("projection", projection);

        for (auto& pointLightPosition : pointLightPositions) {

            glm::mat4 model = glm::mat4(1.0f);

            model = glm::translate(model, pointLightPosition);
            model = glm::scale(model, glm::vec3(0.2f));

            lampShader.setMat4("model", model);

            lampVAO.use();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // кубы
        lightingShader.use();

        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);
        lightingShader.setVec3("viewPos", player->get<TransformComponent>()->position);

        diffuseTexture.use(0);
        specularTexture.use(1);

        lightingShader.setFloat("material.shininess", 48.0f);

        lightingShader.setVec3("dirLight.direction", 0.2f, -2.0f, -0.2f);
        lightingShader.setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
        lightingShader.setVec3("dirLight.specular", 0.f, 0.f, 0.f);

        for (int i = 0; i < 4; i++) {
            std::string base = "pointLights[" + std::to_string(i) + "]";
            lightingShader.setVec3(base + ".position", pointLightPositions[i]);
            lightingShader.setVec3(base + ".ambient", 0.05f, 0.05f, 0.05f);
            lightingShader.setVec3(base + ".diffuse", 0.8f, 0.7f, 0.6f);
            lightingShader.setVec3(base + ".specular", 1.0f, 1.0f, 1.0f);
            lightingShader.setFloat(base + ".constant", 1.0f);
            lightingShader.setFloat(base + ".linear", 0.09);
            lightingShader.setFloat(base + ".quadratic", 0.032);
        }

        lightingShader.setVec3("spotLight.position", player->get<TransformComponent>()->position);
        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLight.diffuse", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.09);
        lightingShader.setFloat("spotLight.quadratic", 0.032);

        lightingShader.setVec3("spotLight.direction", player->get<CameraComponent>()->front(player->get<TransformComponent>()));
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.0f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        lampVAO.use();

        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f*i;

            model = glm::rotate(model, (float) glfwGetTime() * 0.2f, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(angle, 0.f, 1.f));

            lightingShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

    glfwTerminate();
    return 0;
}