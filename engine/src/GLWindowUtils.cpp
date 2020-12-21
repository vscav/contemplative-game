#include <engine/GLWindowUtils.hpp>
#include <engine/utils/common.hpp>

#include <iostream>

namespace engine
{

    void GLWindowUtils::antialias(bool enable)
    {
        if(debug) std::cout << "[GLWindowUtils] " << (enable ? "Enable" : "Disable") << " antialiasing" << std::endl;
        if (enable && !m_antialiasing)
        {
            glEnable(GL_MULTISAMPLE);
            m_antialiasing = true;
        }
        else if (!enable && m_antialiasing)
        {
            glDisable(GL_MULTISAMPLE);
            m_antialiasing = false;
        }
    }

    void GLWindowUtils::enableAlphaBlending()
    {
        if(debug) std::cout << "[GLWindowUtils] Enable alpha blending mode" << std::endl;
        if (!m_isAlphaBlending)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            m_isAlphaBlending = true;
            m_additiveBlending = false;
        }
    }

    void GLWindowUtils::enableAdditiveBlending()
    {
        if(debug) std::cout << "[GLWindowUtils] Enable blending mode" << std::endl;
        if (!m_additiveBlending)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            m_additiveBlending = true;
            m_isAlphaBlending = false;
        }
    }

    void GLWindowUtils::disableBlending()
    {
        if(debug) std::cout << "[GLWindowUtils] Disable blending mode" << std::endl;
        if (m_isAlphaBlending || m_additiveBlending)
        {
            glDisable(GL_BLEND);
            m_isAlphaBlending = false;
            m_additiveBlending = false;
        }
    }

    void GLWindowUtils::enableDepthTesting(bool enable)
    {
        //if(debug) std::cout << "[GLWindowUtils] " << (enable ? "Enable" : "Disable") << " depth testing" << std::endl;
        if (enable && !m_depthTesting)
        {
            glEnable(GL_DEPTH_TEST);
            m_depthTesting = true;
        }
        else if (!enable && m_depthTesting)
        {
            glDisable(GL_DEPTH_TEST);
            m_depthTesting = false;
        }
    }

    void GLWindowUtils::cullBackFaces(bool cull)
    {
        if(debug) std::cout << "[GLWindowUtils] " << (cull ? "Cull" : "Reject") << " back faces" << std::endl;
        if (cull && !m_cullingBackFace)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            m_cullingBackFace = true;
        }
        else if (!cull && m_cullingBackFace)
        {
            glDisable(GL_CULL_FACE);
            m_cullingBackFace = false;
        }
    }

    void GLWindowUtils::goWireframe(bool goWireframe)
    {
        if(debug) std::cout << "[GLWindowUtils] " << (goWireframe ? "Activate" : "Deactivate") << " wireframe mode" << std::endl;
        if (goWireframe && !m_inWireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            m_inWireframe = true;
        }
        else if (!goWireframe && m_inWireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            m_inWireframe = false;
        }
    }

} // namespace engine