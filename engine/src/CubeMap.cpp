#include <engine/GLApplication.hpp>
#include <engine/CubeMap.hpp>
#include <engine/ResourceManager.hpp>
#include <engine/Renderer.hpp>

namespace engine
{

    CubeMap::CubeMap(const char *cubeFront, const char *cubeLeft, const char *cubeBack, const char *cubeBottom, const char *cubeRight, const char *cubeTop, Shader *shader)
        : m_shader(shader)
    {
        GLfloat vertices[] = {
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f};

        Container<GLfloat> dest;

        for (GLfloat i : vertices)
            dest.add(i);

        m_vertices = dest;

        buildVBO();
        buildVAO();

        m_faces.add(cubeRight);
        m_faces.add(cubeLeft);
        m_faces.add(cubeTop);
        m_faces.add(cubeBottom);
        m_faces.add(cubeFront);
        m_faces.add(cubeBack);

        m_cubeMapTexture = ResourceManager::getInstance().loadCubeMapTexture(m_faces);
    }

    void CubeMap::buildVBO()
    {
        m_vbo.bind();
        m_vbo.setData(getVertices(), GL_STATIC_DRAW);
        m_vbo.unbind();
    }

    void CubeMap::buildVAO()
    {
        m_vao.bind();

        const GLuint VERTEX_ATTR_POSITION = 0;

        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

        m_vbo.bind();

        m_vbo.setVertexAttrib(VERTEX_ATTR_POSITION, 3, GL_FLOAT, 3 * sizeof(GLfloat), 0);

        m_vbo.unbind();

        m_vao.unbind();
    }

    void CubeMap::render()
    {
        GLApplication::getInstance().getWindowManager()->getWindowUtils()->enableDepthTesting(false);

        Renderer::getInstance().sendModelMatrixUniforms(glm::mat4(1.0f), m_shader.get(), true);

        m_shader->bind();

        m_shader->setVec3f("uFogColor", 0.0f, 0.0f, 0.0f);

        m_vao.bind();

        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        m_vao.unbind();

        m_shader->unbind();

        GLApplication::getInstance().getWindowManager()->getWindowUtils()->enableDepthTesting(true);
    }

} // namespace engine