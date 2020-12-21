#include <engine/Shader.hpp>
#include <engine/utils/common.hpp>
#include <engine/utils/cout_colors.hpp>

#include <iostream>

namespace engine
{

    Shader::Shader(const char *vertexShader, const char *fragmentShader, const char *geometryShader, const bool &fromFile)
        : m_programId(0), m_vertexId(0), m_fragmentId(0), m_geometryId(0), m_compiled(false)
    {
        std::string vsStr;
        std::string fsStr;
        std::string gsStr;

        if (fromFile)
        {
            vsStr = parseFile(vertexShader);
            fsStr = parseFile(fragmentShader);
            if (geometryShader != nullptr)
            {
                gsStr = parseFile(geometryShader);
            }
            else
            {
                gsStr = "";
            }
        }
        else
        {
            vsStr = vertexShader;
            fsStr = fragmentShader;
            if (geometryShader != nullptr)
            {
                gsStr = geometryShader;
            }
            else
            {
                gsStr = "";
            }
        }

        m_programId = glCreateProgram();

        // compile shaders
        m_vertexId = compileShader(GL_VERTEX_SHADER, vsStr);
        m_fragmentId = compileShader(GL_FRAGMENT_SHADER, fsStr);

        if (geometryShader != nullptr)
        {
            m_geometryId = compileShader(GL_GEOMETRY_SHADER, gsStr);
        }

        AttachShaderId("Vertex", m_vertexId);
        AttachShaderId("Fragment", m_fragmentId);
        if (geometryShader != nullptr)
        {
            AttachShaderId("Geometry", m_geometryId);
        }

        glLinkProgram(m_programId);

        int linkResult;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &linkResult);
        if (linkResult == GL_FALSE)
        {
            glDeleteProgram(m_programId);
            if(debug) std::cerr << COLOR_RED << "[Shader] ERROR: Shader creation aborded (linking doesn't work)"<< COLOR_RESET << std::endl;
        }
        else
        {
            glValidateProgram(m_programId);
            m_compiled = true;
        }

        glDeleteShader(m_vertexId);
        glDeleteShader(m_fragmentId);
        if (geometryShader != nullptr)
            glDeleteShader(m_geometryId);
    }

    Shader::~Shader()
    {
        if (m_programId != 0)
            glDeleteProgram(m_programId);
    }

    void Shader::AttachShaderId(const char *shaderName, const GLuint id)
    {
        if (id != 0)
        {
            glAttachShader(m_programId, id);
            if(debug) std::cout << "[Shader] " << shaderName << " shader attached " << std::endl;
        }
        else
        {
            if(debug) std::cout << COLOR_RED << "[Shader] ERROR: Creation aborded (" << shaderName << " shader not compiled)" << COLOR_RESET << std::endl;
            assert(false);
        }
    }

    GLuint Shader::compileShader(const GLenum &shaderType, const std::string &shaderStr)
    {

        GLuint shaderId = glCreateShader(shaderType);

        if (shaderId)
        {
            const char *shaderCode = shaderStr.c_str();
            glShaderSource(shaderId, 1, &shaderCode, nullptr);
            glCompileShader(shaderId);

            int compileResult;
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);
            if (compileResult == GL_FALSE)
            {

                int infosLength;
                glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infosLength);
                std::vector<char> message(infosLength);
                glGetShaderInfoLog(shaderId, infosLength, &infosLength, &message[0]);
                if(debug) std::cerr << COLOR_RED << "[Shader] ERROR: Error during compiling shader (" << shaderTypeStr(shaderType) << ") :" << std::endl
                          << &message[0] << COLOR_RESET << std::endl;
                return 0;
            }
        }
        else
        {
            if(debug) std::cerr << COLOR_RED << "[Shader] ERROR: Failed to assign new shader id (" << shaderTypeStr(shaderType) << " shader)" << COLOR_RESET << std::endl;
        }
        return shaderId;
    }

    std::string Shader::parseFile(const char *filepath)
    {

        std::string shaderStr;
        std::ifstream file(filepath, std::ios::in);

        if (!file.is_open())
        {
            std::string message = "[Shader] ERROR: Failed to open file: ";
            message += filepath;
            if(debug) std::cerr << COLOR_RED << message.c_str() << COLOR_RESET << std::endl;
        }

        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        shaderStr = stream.str();

        return shaderStr;
    }

    bool Shader::bind() const
    {
        if (m_compiled)
        {
            glUseProgram(m_programId);
        }
        return m_compiled;
    };

    std::string Shader::shaderTypeStr(const GLenum &shaderType)
    {
        switch (shaderType)
        {
        case GL_FRAGMENT_SHADER:
            return "GL_FRAGMENT_SHADER";

        case GL_GEOMETRY_SHADER:
            return "GL_GEOMETRY_SHADER";

        case GL_COMPUTE_SHADER:
            return "GL_COMPUTE_SHADER";

        case GL_VERTEX_SHADER:
            return "GL_VERTEX_SHADER";

        case GL_TESS_CONTROL_SHADER:
            return "GL_TESS_CONTROL_SHADER";

        case GL_TESS_EVALUATION_SHADER:
            return "GL_TESS_EVALUATION_SHADER";

        default:
            return nullptr;
        }
    }

    GLint Shader::getUniform(const std::string &uniformName)
    {
        if (m_uniformLocationCache.find(uniformName) != m_uniformLocationCache.end())
        {
            return m_uniformLocationCache[uniformName];
        }

        GLint location = glGetUniformLocation(m_programId, uniformName.c_str());

        if (location == -1)
        {
            if(debug) std::cerr << COLOR_RED << "[Shader] ERROR: uniform \"" << uniformName << "\" doesn't exist" << COLOR_RESET << std::endl;
        }

        m_uniformLocationCache[uniformName] = location;
        return location;
    }

    void Shader::setInt(const std::string &uniformName, int v)
    {
        glUniform1i(getUniform(uniformName), v);
    }

    void Shader::setFloat(const std::string &uniformName, float v)
    {
        glUniform1f(getUniform(uniformName), v);
    }

    void Shader::setVec2f(const std::string &uniformName, const glm::vec2 &v)
    {
        glUniform2f(getUniform(uniformName), v.x, v.y);
    }

    void Shader::setVec2f(const std::string &uniformName, const float &x, const float &y)
    {
        glUniform2f(getUniform(uniformName), x, y);
    }

    void Shader::setVec3f(const std::string &uniformName, const glm::vec3 &v)
    {
        glUniform3f(getUniform(uniformName), v.x, v.y, v.z);
    }

    void Shader::setVec3f(const std::string &uniformName, const float &x, const float &y, const float &z)
    {
        glUniform3f(getUniform(uniformName), x, y, z);
    }

    void Shader::setVec4f(const std::string &uniformName, const glm::vec4 &v)
    {
        glUniform4f(getUniform(uniformName), v.x, v.y, v.z, v.w);
    }

    void Shader::setVec4f(const std::string &uniformName, const float &x, const float &y, const float &z, const float &w)
    {
        glUniform4f(getUniform(uniformName), x, y, z, w);
    }

    void Shader::setMat3(const std::string &uniformName, const glm::mat3 &m)
    {
        glUniformMatrix3fv(getUniform(uniformName), 1, GL_FALSE, &m[0][0]);
    }

    void Shader::setMat4(const std::string &uniformName, const glm::mat4 &m)
    {
        glUniformMatrix4fv(getUniform(uniformName), 1, GL_FALSE, &m[0][0]);
    }

} // namespace engine