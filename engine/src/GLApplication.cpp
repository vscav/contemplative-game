#include <engine/GLApplication.hpp>
#include <engine/Renderer.hpp>
#include <engine/EngineException.hpp>
#include <engine/utils/common.hpp>

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

  GLApplication::GLApplication(Camera *camera, GLWindowManager *manager, GLAudioManager *audioManager, Scene *scene)
      : m_state(stateReady),
        m_windowManager(manager),
        m_audioManager(audioManager),
        m_camera(camera),
        m_scene(scene)
  {
    Renderer::getInstance().setCamera(m_camera);
    Renderer::getInstance().setScene(m_scene);

    currentGLApplication = this;
  }

  GLApplication::GLApplication(Camera *camera, GLWindowManager *manager, GLAudioManager *audioManager, Scene *scene,
                               std::string title, int width, int height, bool fullScreen)
      : m_state(stateReady),
        m_windowManager(manager),
        m_audioManager(audioManager),
        m_camera(camera),
        m_scene(scene)
  {
    Renderer::getInstance().setCamera(m_camera);
    Renderer::getInstance().setScene(m_scene);

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
      if(m_state == stateRun){
        m_audioManager->update();
        getWindowManager()->update();
        loop();
        getWindowManager()->processInput();
      }
      getWindowManager()->swapBuffers();
      getWindowManager()->setKeyCallback();
    }
  }

  void GLApplication::pause(){
    if(m_state == stateRun){
      m_state = statePause;
    }
    else{
      m_state = stateRun;
    }
  }

  void GLApplication::loop()
  {
    if (applicationDebug)
      std::cout << "[Info] GLApplication main loop" << std::endl;
  }

  void GLApplication::setState(State newState){
    m_state=newState;
  }

} // namespace engine
