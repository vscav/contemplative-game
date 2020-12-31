#include <engine/GLApplication.hpp>
#include <engine/Renderer.hpp>
#include <engine/EngineException.hpp>
#include <engine/utils/common.hpp>
#include <engine/Serializer.hpp>

namespace engine
{

  GLApplication *currentGLApplication = nullptr;

  GLApplication &GLApplication::getInstance()
  {
    if (currentGLApplication)
      return *currentGLApplication;
    else
      throw EngineException("[GLApplication] There is no current GLApplication", __FILE__, __LINE__);
  }

  GLApplication::GLApplication(Camera *camera, GLWindowManager *manager, GLAudioManager *a_manager)
      : m_state(stateReady),
        m_windowManager(manager),
        m_audioManager(a_manager),
        m_camera(camera)
  {
    setScene(Serializer::getInstance().load("application/scenes/scene.json"));

    Renderer::getInstance().setCamera(m_camera);
    Renderer::getInstance().setScene(m_scene);

    currentGLApplication = this;
  }

  GLApplication::GLApplication(Camera *camera, GLWindowManager *manager, GLAudioManager *a_manager,
                               std::string title, int width, int height, bool fullScreen)
      : m_state(stateReady),
        m_windowManager(manager),
        m_audioManager(a_manager),
        m_camera(camera)
  {
    setScene(Serializer::getInstance().load("application/scenes/scene.json"));

    Renderer::getInstance().setCamera(m_camera);
    Renderer::getInstance().setScene(m_scene);

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

    // Add the newly created skybox to the application scene
    m_scene->add(std::move(skybox));

    currentGLApplication = this;
  }

  void GLApplication::exit()
  {
    if (applicationDebug)
      std::cout << "[GLApplication] Application exited successfully" << std::endl;

    m_state = stateExit;
  }

  void GLApplication::run()
  {
    m_state = stateRun;

    while (m_state == stateRun || m_state == statePause)
    {
      if (m_state == stateRun)
      {
        m_audioManager->update();
        getWindowManager()->update();
        loop();
        getWindowManager()->processInput();
      }
      getWindowManager()->swapBuffers();
      getWindowManager()->setKeyCallback();
    }
  }

  void GLApplication::pause()
  {
    if (m_state == stateRun)
    {
      m_state = statePause;
    }
    else
    {
      m_state = stateRun;
    }
  }

  void GLApplication::loop()
  {
    if (applicationDebug)
      std::cout << "[Info] GLApplication main loop" << std::endl;
  }

  void GLApplication::setState(State newState)
  {
    m_state = newState;
  }

} // namespace engine
