#pragma once
#ifndef _GLWindowUtils_HPP_
#define _GLWindowUtils_HPP_

#include <GL/glew.h>

namespace engine
{

    /// \class GLWindowUtils
    /// \brief Utility class for updating OpenGL state (such as alpha blending, depth testing, etc.).
    class GLWindowUtils
    {
    private:
        bool m_cullingBackFace = false;  /*!< A boolean to tell if whether or not the culling back face option is enabled. */
        bool m_inWireframe = false;      /*!< A boolean to tell if whether or not the wireframe mode is enabled. */
        bool m_isAlphaBlending = false;  /*!< A boolean to tell if whether or not the alpha blending mode is enabled. */
        bool m_additiveBlending = false; /*!< A boolean to tell if whether or not the additive blending mode is enabled. */
        bool m_antialiasing = false;     /*!< A boolean to tell if whether or not the antialiasing option is enabled. */
        bool m_depthTesting = false;     /*!< A boolean to tell if whether or not the depth testing is enabled. */

    public:
        /// \brief Constructor.
        GLWindowUtils() = default;
        /// \brief Destructor.
        ~GLWindowUtils() = default;

        /// \brief Enables/Disables the antialiasing option.
        /// \param enable : A boolean to enable (true) or disable (false) the option.
        void antialias(bool enable);

        /// \brief Enables the alpha blending mode.
        void enableAlphaBlending();

        /// \brief Enables the additive blending mode.
        void enableAdditiveBlending();

        /// \brief Disables the alpha and additive blending modes.
        void disableBlending();

        /// \brief Enables/Disables the depth testing.
        /// \param enable : A boolean to enable (true) or disable (false) the testing.
        void enableDepthTesting(bool enable);

        /// \brief Enables/Disables the culling back face option.
        /// \param cull : A boolean to cull (true) or reject (false) the back face.
        void cullBackFaces(bool cull);

        /// \brief Enables/Disables the wireframe mode.
        /// \param goWireframe : A boolean to enable (true) or disable (false) the wireframe mode.
        void goWireframe(bool goWireframe);
    };

} // namespace engine

#endif /* _GLWindowUtils_HPP_ */