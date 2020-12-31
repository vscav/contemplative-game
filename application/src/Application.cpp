#include <engine/TrackballCamera.hpp>
#include <engine/GLFWManager.hpp>
#include <engine/OpenALManager.hpp>

#include "../include/Application.hpp"

#include <string>

Application::Application()
    : engine::GLApplication(new engine::TrackballCamera(), new engine::GLFWManager(), new engine::OpenALManager())
{
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : engine::GLApplication(new engine::TrackballCamera(), new engine::GLFWManager(), new engine::OpenALManager(), title, width, height, fullScreen)
{
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
