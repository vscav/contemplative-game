#include <engine/TrackballCamera.hpp>
#include <engine/GLFWManager.hpp>
#include <engine/OpenALManager.hpp>
#include <engine/Scene.hpp>

#include "../include/Application.hpp"

#include <string>

Application::Application()
    : engine::GLApplication(new engine::TrackballCamera(), new engine::GLFWManager(), new engine::OpenALManager(), new engine::Scene())
{
    initialize();
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : engine::GLApplication(new engine::TrackballCamera(), new engine::GLFWManager(), new engine::OpenALManager(),new engine::Scene(), title, width, height, fullScreen)
{
    initialize();
}

void Application::initialize()
{
    // Create a new player
    std::unique_ptr<engine::Player> player(
        new engine::Player(
            engine::Entity(
                new engine::Model("application/res/models/spaceship/scene.gltf"),
                new engine::Shader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag"),
                false)));

    // Create a new entity obstacle
    std::unique_ptr<engine::Entity> obstacle(
        new engine::Obstacle(
            engine::Entity(
                new engine::Model("application/res/models/spaceship/scene.gltf"),
                new engine::Shader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag"),
                false,
                engine::Transform(glm::vec3(8, 0, 2), glm::vec3(1), glm::vec3(0)))));

    // Create a new skybox (CubeMap object)
    std::unique_ptr<engine::CubeMap> skybox(
        new engine::CubeMap(
            "application/res/textures/skybox/space/front.png",
            "application/res/textures/skybox/space/left.png",
            "application/res/textures/skybox/space/back.png",
            "application/res/textures/skybox/space/bottom.png",
            "application/res/textures/skybox/space/right.png",
            "application/res/textures/skybox/space/top.png",
            new engine::Shader("application/res/shaders/skybox.vert", "application/res/shaders/skybox.frag")));

    // Add the newly created entity player to the application scene
    m_scene->add(std::move(player));

    // Add the obstacle newly created to the application scene
    m_scene->add(std::move(obstacle));

    // Add the newly created skybox to the application scene
    m_scene->add(std::move(skybox));
}

void Application::loop()
{
    // Print fps in console by passing true
    engine::TimeManager::getInstance().calculateFrameRate(false);

    // Get the total time ellapsed since the application was run
    float dt = m_windowManager->getTimeElapsed();

    // Update the camera
    m_camera->update(dt);

    // Update the scene
    m_scene->update(dt);

    // Render the entire scene
    m_scene->render();
}
