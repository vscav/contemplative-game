#pragma once
#ifndef _GLFWManager_HPP_
#define _GLFWManager_HPP_

#include <engine/GLWindowManager.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>

namespace engine
{

    /// \class GLFWManager
    /// \brief Class which is the implementation of the abstract base class GLWindowManager, and which uses the
    /// GLFW cross-platform library to create a window, process input (to communicate with the inputs manager) and create the OpenGL
    /// context.
    class GLFWManager final : public GLWindowManager
    {
    protected:
        GLFWwindow *m_window; /*!< The GLFW window object (pointer) that manages the window and input. */

        GLFWmonitor *m_monitor; /*!< The primary monitor of the user, which will be used to display the application window. */

        bool m_firstMouse = true; /*!< A boolean used to determine if the click captured is the first. */

        std::string m_title; /*!< The window/application title (string). */
        int m_width;         /*!< The window width value. */
        int m_height;        /*!< The window height value. */
        bool m_fullScreen;   /*!< A boolean to determine if the window is in full screen mode. */

        float m_lastX = float(m_width) / 2.0f;  /*!< The last position of the mouse X position. */
        float m_lastY = float(m_height) / 2.0f; /*!< The last position of the mouse Y position. */

        float m_deltaTime; /*!< The GLFW window total time ellapsed. */
        float m_time;      /*!< The time difference between the previous frame that was drawn and the current frame of the GLFW window. */

    public:
        /// \brief Constructor.
        /// \param title : The window/application title.
        /// \param width : The window width value.
        /// \param height : The window height value.
        /// \param fullScreen : A boolean to determine if the window is in full screen mode.
        explicit GLFWManager(std::string title = "GL Application template", int width = 1280, int height = 720, bool fullScreen = false);
        /// \brief Destructor.
        inline ~GLFWManager() override { destroy(); };

        /// \brief Initializes the window and creates the OpenGL context.
        /// \return An integer acting as a boolean for success/fail information.
        int initialize() override;

        /// \brief Gets information about GLFW and OpenGL contexts.
        /// \param major : OpenGL major version accepted.
        /// \param minor : OpenGL minor version accepted.
        void getContext(int major, int minor);

        /// \brief Get information about OpenGL version and renderer.
        void getLogInformation();

        /// \brief Creates the GLFW window, either in full screen or not.
        void createWindow();

        /// \brief Centers the GLFW window on the monitor screen.
        void centerWindow();

        /// \brief Swaps the back buffer to the front (should be called every frame).
        void swapBuffers() override;

        /// \brief Processes any needed input for the application.
        void processInput() override;

        /// \brief Updates the window (should be called every frame).
        void update() override;

        /// \brief Destroys the window and the OpenGL context.
        void destroy() override;

        /// \brief Returns the window/application title.
        /// \return The title of the window/application.
        inline std::string getTitle() const override { return m_title; };
        /// \brief Returns the window width.
        /// \return The window width.
        inline int getWidth() const override { return m_width; };
        /// \brief Returns the window height.
        /// \return The window height.
        inline int getHeight() const override { return m_height; };
        /// \brief Returns the window ratio (window width divided by window height).
        /// \return The window ratio (window width divided by window height).
        inline float getWindowRatio() const override { return float(m_width) / float(m_height); };
        /// \brief Returns a boolean that indicates whether or not the window is in full screen mode.
        /// \return A boolean that indicates whether or not the window is in full screen mode.
        inline bool isFullScreen() const override { return m_fullScreen; };

        /// \brief Returns the total time elapsed since the GL application was started.
        /// \return The total time elapsed since the GL application was started.
        float const getTimeElapsed() override;
        /// \brief Returns the time elapsed since the last frame.
        /// \return The time elapsed since the last frame.
        float const getFrameDeltaTime() override;
    };

} // namespace engine

#endif /* _GLFWManager_HPP_ */