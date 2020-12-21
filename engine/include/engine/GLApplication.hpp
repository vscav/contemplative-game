#pragma once
#ifndef _GLApplication_HPP_
#define _GLApplication_HPP_

#include <engine/TimeManager.hpp>
#include <engine/GLWindowManager.hpp>
#include <engine/Camera.hpp>
#include <engine/Scene.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>

namespace engine
{

    /// \brief The different states in which the application can be found.
    enum State
    {
        stateReady,
        stateRun,
        statePause,
        stateExit
    };

    /// \class GLApplication
    /// \brief Class which represents the core of the OpenGL application.
    class GLApplication
    {
    private:
        State m_state; /*!< The current state of the GL application (ready, run or exit). */

    protected:
        std::unique_ptr<GLWindowManager> m_windowManager; /*!< A unique pointer to the window manager of the application. */
        std::shared_ptr<Camera> m_camera;                 /*!< A shared pointer to the camera used by the application and shared with the renderer. */
        std::unique_ptr<Scene> m_scene;                   /*!< A unique pointer to the scene (collection of graphical objects to display). */

        /// \brief The GL application loop (run until the user asks to quit).
        virtual void loop();

    public:
        /// \brief Parameterized constructor.
        /// \param camera : The camera which will be used by the application.
        /// \param manager : The window manager which will be used by the application.
        /// \param scene : The scene which will be displayed by the application.
        GLApplication(Camera *camera, GLWindowManager *manager, Scene *scene);

        /// \brief Detailed parameterized constructor.
        /// \param camera : The camera which will be used by the application.
        /// \param manager : The window manager which will be used by the application.
        /// \param scene : The scene which will be displayed by the application.
        /// \param title : The GL application title (string).
        /// \param width : The GL application width value.
        /// \param height : The GL application height value.
        /// \param fullScreen : A boolean to determine if the GL application window is in full screen mode.
        explicit GLApplication(Camera *camera, GLWindowManager *manager, Scene *scene,
                               std::string title, int width, int height, bool fullScreen);

        /// \brief Copy constructor.
        GLApplication(GLApplication const &) = delete;

        /// \brief Affectation/Copy assignment operator.
        GLApplication &operator=(const GLApplication &) = delete;

        virtual ~GLApplication() = default;

        /// \brief Returns the current GL application instance.
        /// \return The instance of the current application.
        static GLApplication &getInstance();

        /// \brief Exits the GL application by changing the current state.
        void exit();

        /// \brief Runs the GL application by changing the current state and starting the GL application main loop.
        void run();

        /// \brief Returns the current state of the GL application (ready, running, paused, exited).
        /// \return The current state of the GL application (ready, running, paused, exited).
        inline State getState() const { return m_state; }

        /// \brief Returns the window manager (pointer) of the GL application.
        /// \return A pointer to the window manager of the GL application.
        inline GLWindowManager *getWindowManager() const { return m_windowManager.get(); }

        /// \brief Returns the camera (pointer) of the GL application.
        /// \return A pointer to the camera of the GL application.
        inline Camera *getCamera() { return m_camera.get(); };
    };

} // namespace engine

#endif /* _GLApplication_HPP_ */