#pragma once
#ifndef _WindowManager_HPP_
#define _WindowManager_HPP_

#include <engine/InputManager.hpp>
#include <engine/GLWindowUtils.hpp>

#include <string>
#include <fstream>

namespace engine
{

    /// \class GLWindowManager
    /// \brief Class for managing the creation of the window, input and the
    /// creating of the OpenGL context. This class should be inherited from to create
    /// specific implementations like GLFW or SDL.
    class GLWindowManager
    {
    protected:
        std::unique_ptr<GLWindowUtils> m_windowUtils; /*!< The utilitary class for our window. */

        std::unique_ptr<InputManager> m_inputManager; /*!< The input manager for our window. */

    public:
        /// \brief Destructor. This is needed so that the class inheriting this will have it's deconstructor called.
        virtual ~GLWindowManager() = default;

        /// \brief Initializes the window and creates the OpenGL context.
        /// \return An integer acting as a boolean for success/fail information.
        virtual int initialize() = 0;

        /// \brief Swaps the back buffer to the front (should be called every frame).
        virtual void swapBuffers() = 0;

        /// \brief Processes any needed input for the application.
        virtual void processInput() = 0;

        /// \brief Updates the window (should be called every frame).
        virtual void update() = 0;

        /// \brief Destroys the window and the OpenGL context.
        virtual void destroy() = 0;

        /// \brief Returns the window/application title.
        /// \return The title of the window/application.
        virtual std::string getTitle() const = 0;
        /// \brief Returns the window width.
        /// \return The window width.
        virtual int getWidth() const = 0;
        /// \brief Returns the window height.
        /// \return The window height.
        virtual int getHeight() const = 0;
        /// \brief Returns the window ratio (window width divided by window height).
        /// \return The window ratio (window width divided by window height).
        virtual float getWindowRatio() const = 0;
        /// \brief Returns a boolean that indicates whether or not the window is in full screen mode.
        /// \return A boolean that indicates whether or not the window is in full screen mode.
        virtual bool isFullScreen() const = 0;

        /// \brief Returns the total time elapsed since the window was launched.
        /// \return The total time elapsed since the GL application was started.
        virtual float const getTimeElapsed() = 0;
        /// \brief Returns the time elapsed since the last frame.
        /// \return The time elapsed since the last frame.
        virtual float const getFrameDeltaTime() = 0;

        /// \brief Sets the application's inputs manager.
        /// \param inputManager : A pointer to the inputManager of the application.
        // inline void setInputManager(std::shared_ptr<InputManager> inputManager) { m_inputManager = std::move(inputManager); };
        /// \brief Returns the application's inputs manager.
        /// \return A pointer to the application's inputs manager.
        inline InputManager *getInputManager() const { return m_inputManager.get(); };
        /// \brief Sets the application's window utility.
        /// \param windowUtils : A pointer to the window utility of the application.
        // inline void setWindowUtils(std::shared_ptr<GLWindowUtils> windowUtils) { m_windowUtils = std::move(windowUtils); };
        /// \brief Returns the application's window utility.
        /// \return A pointer to the window utility of the application.
        inline GLWindowUtils *getWindowUtils() const { return m_windowUtils.get(); };
    };

} // namespace engine

#endif /* _WindowManager_HPP_ */