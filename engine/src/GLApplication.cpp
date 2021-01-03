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

  GLApplication::GLApplication(Camera *camera, GLWindowManager *manager, GLAudioManager *a_manager, UI *ui)
      : m_state(stateReady),
        m_windowManager(manager),
        m_audioManager(a_manager),
        m_camera(camera),
        m_UI(ui)
  {
    initialize();
  }

  GLApplication::GLApplication(Camera *camera, GLWindowManager *manager, GLAudioManager *a_manager, UI *ui,
                               std::string title, int width, int height, bool fullScreen)
      : m_state(stateReady),
        m_windowManager(manager),
        m_audioManager(a_manager),
        m_camera(camera),
        m_UI(ui)
  {
    initialize();
  }

  void GLApplication::loadScene(const std::string sceneFilePath)
  {
    m_scene->clearScene();

    setScene(Serializer::getInstance().load(sceneFilePath));

    m_UI->reset();

    Renderer::getInstance().setScene(m_scene);
  }

  void GLApplication::initialize()
  {
    setScene(Serializer::getInstance().load("application/scenes/scene.json"));

    Renderer::getInstance().setCamera(m_camera);
    Renderer::getInstance().setScene(m_scene);

    m_UI->initializeText();
    m_UI->initialize();

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

    while (m_state == stateRun || m_state == statePause || m_state == stateWin)
    {
      if (m_state == stateRun || m_state == stateWin)
      {
        m_audioManager->update();

        getWindowManager()->update();

        getUI()->updateMatrix(getWindowManager()->getWidth(), getWindowManager()->getHeight());

        loop();

        getWindowManager()->processInput();
      }

      getUI()->render();

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
