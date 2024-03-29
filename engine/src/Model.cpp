#include <engine/Model.hpp>
#include <engine/Shader.hpp>
#include <engine/Renderer.hpp>
#include <engine/dependencies/glm.hpp>
#include <engine/EngineException.hpp>
#include <engine/utils/gltf.hpp>
#include <engine/utils/common.hpp>

#include <iostream>

namespace engine
{
    Model::Model(const std::string &gltfFilePath) : m_gltfFilePath(gltfFilePath)
    {
        if (!loadGltfFile(m_model))
            throw EngineException("[GLTF Model] Couldn't load GLTF file", __FILE__, __LINE__);

        if (applicationDebug)
            std::cout << "[GLTF Model] GLTF file has been successfully read and loaded" << std::endl;

        m_textureObjects = createTextureObjects(m_model);

        m_bufferObjects = createBufferObjects(m_model);

        m_vertexArrayObjects = createVertexArrayObjects(m_model, m_bufferObjects, m_meshToVertexArrays);

        createDefaultTexture();
    }

    void Model::render(Shader *shader)
    {
        shader->bind();

        const auto uBaseColorTexture = shader->getUniform("uBaseColorTexture");
        const auto uBaseColorFactor = shader->getUniform("uBaseColorFactor");

        const auto uMetallicRoughnessTexture = shader->getUniform("uMetallicRoughnessTexture");
        const auto uMetallicFactor = shader->getUniform("uMetallicFactor");
        const auto uRoughnessFactor = shader->getUniform("uRoughnessFactor");

        const auto uEmissiveTexture = shader->getUniform("uEmissiveTexture");
        const auto uEmissiveFactor = shader->getUniform("uEmissiveFactor");

        const auto uOcclusionTexture = shader->getUniform("uOcclusionTexture");
        const auto uOcclusionStrength = shader->getUniform("uOcclusionStrength");

        const auto bindMaterial = [&](const GLuint materialIndex) {
            if (materialIndex >= 0)
            {
                const auto &material = m_model.materials[materialIndex];
                const auto &pbrMetallicRoughness = material.pbrMetallicRoughness;
                if (uBaseColorFactor >= 0)
                {
                    shader->setVec4f("uBaseColorFactor",
                                     (float)pbrMetallicRoughness.baseColorFactor[0],
                                     (float)pbrMetallicRoughness.baseColorFactor[1],
                                     (float)pbrMetallicRoughness.baseColorFactor[2],
                                     (float)pbrMetallicRoughness.baseColorFactor[3]);
                }
                if (uBaseColorTexture >= 0)
                {
                    auto textureObject = m_whiteTexture;
                    if (pbrMetallicRoughness.baseColorTexture.index >= 0)
                    {
                        const auto &texture =
                            m_model.textures[pbrMetallicRoughness.baseColorTexture.index];
                        if (texture.source >= 0)
                        {
                            textureObject = m_textureObjects[texture.source];
                        }
                    }

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, textureObject);
                    shader->setInt("uBaseColorTexture", 0);
                }
                if (uMetallicFactor >= 0)
                    shader->setFloat("uMetallicFactor", (float)pbrMetallicRoughness.metallicFactor);
                if (uRoughnessFactor >= 0)
                    shader->setFloat("uRoughnessFactor", (float)pbrMetallicRoughness.roughnessFactor);
                if (uMetallicRoughnessTexture >= 0)
                {
                    auto textureObject = 0u;
                    if (pbrMetallicRoughness.metallicRoughnessTexture.index >= 0)
                    {
                        const auto &texture = m_model.textures[pbrMetallicRoughness.metallicRoughnessTexture.index];
                        if (texture.source >= 0)
                            textureObject = m_textureObjects[texture.source];
                    }

                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, textureObject);
                    shader->setInt("uMetallicRoughnessTexture", 1);
                }
                if (uEmissiveFactor >= 0)
                {
                    shader->setVec3f("uEmissiveFactor",
                                     (float)material.emissiveFactor[0],
                                     (float)material.emissiveFactor[1],
                                     (float)material.emissiveFactor[2]);
                }
                if (uEmissiveTexture >= 0)
                {
                    auto textureObject = 0u;
                    if (material.emissiveTexture.index >= 0)
                    {
                        const auto &texture = m_model.textures[material.emissiveTexture.index];
                        if (texture.source >= 0)
                        {
                            textureObject = m_textureObjects[texture.source];
                        }
                    }

                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, textureObject);
                    shader->setInt("uEmissiveTexture", 2);
                }
                if (uOcclusionStrength >= 0)
                    shader->setFloat("uOcclusionStrength", (float)material.occlusionTexture.strength);
                if (uOcclusionTexture >= 0)
                {
                    auto textureObject = m_whiteTexture;
                    if (material.occlusionTexture.index >= 0)
                    {
                        const auto &texture = m_model.textures[material.occlusionTexture.index];
                        if (texture.source >= 0)
                            textureObject = m_textureObjects[texture.source];
                    }

                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, textureObject);
                    shader->setInt("uOcclusionTexture", 3);
                }
            }
            else
            {
                if (uBaseColorFactor >= 0)
                    shader->setVec4f("uBaseColorFactor", 1, 1, 1, 1);
                if (uBaseColorTexture >= 0)
                {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, m_whiteTexture);
                    shader->setInt("uBaseColorTexture", 0);
                }
                if (uMetallicFactor >= 0)
                    shader->setFloat("uMetallicFactor", 1.f);
                if (uRoughnessFactor >= 0)
                    shader->setFloat("uRoughnessFactor", 1.f);
                if (uMetallicRoughnessTexture >= 0)
                {
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    shader->setInt("uMetallicRoughnessTexture", 1);
                }
                if (uEmissiveFactor >= 0)
                    shader->setVec3f("uEmissiveFactor", 0.f, 0.f, 0.f);
                if (uEmissiveTexture >= 0)
                {
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    shader->setInt("uEmissiveTexture", 2);
                }
                if (uOcclusionStrength >= 0)
                    shader->setFloat("uOcclusionStrength", 0.f);
                if (uOcclusionTexture >= 0)
                {
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    shader->setInt("uOcclusionTexture", 3);
                }
            }
        };

        const auto drawModel = [&]() {
            Renderer::getInstance().sendDirectionalLightUniforms(shader);

            const std::function<void(int)> drawNode =
                [&](int nodeIdx) {
                    const auto &node = m_model.nodes[nodeIdx];

                    if (node.mesh >= 0)
                    {
                        const auto &mesh = m_model.meshes[node.mesh];
                        const auto &vaoRange = m_meshToVertexArrays[node.mesh];
                        for (size_t pIdx = 0; pIdx < mesh.primitives.size(); ++pIdx)
                        {
                            const auto vao = m_vertexArrayObjects[vaoRange.begin + pIdx];
                            const auto &primitive = mesh.primitives[pIdx];

                            bindMaterial(primitive.material);

                            glBindVertexArray(vao);
                            if (primitive.indices >= 0)
                            {
                                const auto &accessor = m_model.accessors[primitive.indices];
                                const auto &bufferView = m_model.bufferViews[accessor.bufferView];
                                const auto byteOffset =
                                    accessor.byteOffset + bufferView.byteOffset;
                                glDrawElements(primitive.mode, GLsizei(accessor.count),
                                               accessor.componentType, (const GLvoid *)byteOffset);
                            }
                            else
                            {
                                const auto accessorIdx = (*begin(primitive.attributes)).second;
                                const auto &accessor = m_model.accessors[accessorIdx];
                                glDrawArrays(primitive.mode, 0, GLsizei(accessor.count));
                            }
                        }
                    }

                    for (const auto childNodeIdx : node.children)
                        drawNode(childNodeIdx);
                };

            if (m_model.defaultScene >= 0)
            {
                for (const auto nodeIdx : m_model.scenes[m_model.defaultScene].nodes)
                {
                    drawNode(nodeIdx);
                }
            }
        };

        drawModel();

        shader->unbind();
    }

    bool Model::loadGltfFile(tinygltf::Model &model)
    {
        if (applicationDebug)
            std::cout << "[GLTF Model] Loading file " << m_gltfFilePath << std::endl;

        tinygltf::TinyGLTF loader;

        std::string err;
        std::string warn;

        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, m_gltfFilePath.string());

        if (!warn.empty())
            std::cerr << warn << std::endl;

        if (!err.empty())
            std::cerr << err << std::endl;

        if (!ret)
        {
            std::cerr << "Failed to parse glTF file" << std::endl;
            return false;
        }

        return true;
    }

    std::vector<GLuint> Model::createTextureObjects(
        const tinygltf::Model &model) const
    {
        std::vector<GLuint> textureObjects(model.textures.size(), 0);

        tinygltf::Sampler defaultSampler;
        defaultSampler.minFilter = GL_LINEAR;
        defaultSampler.magFilter = GL_LINEAR;
        defaultSampler.wrapS = GL_REPEAT;
        defaultSampler.wrapT = GL_REPEAT;

        glActiveTexture(GL_TEXTURE0);

        glGenTextures(GLsizei(model.textures.size()), textureObjects.data());
        for (size_t i = 0; i < model.textures.size(); ++i)
        {
            const auto &texture = model.textures[i];
            assert(texture.source >= 0);
            const auto &image = model.images[texture.source];

            const auto &sampler =
                texture.sampler >= 0 ? model.samplers[texture.sampler] : defaultSampler;
            glBindTexture(GL_TEXTURE_2D, textureObjects[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0,
                         GL_RGBA, image.pixel_type, image.image.data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                            sampler.minFilter != -1 ? sampler.minFilter : GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                            sampler.magFilter != -1 ? sampler.magFilter : GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sampler.wrapS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sampler.wrapT);

            if (sampler.minFilter == GL_NEAREST_MIPMAP_NEAREST ||
                sampler.minFilter == GL_NEAREST_MIPMAP_LINEAR ||
                sampler.minFilter == GL_LINEAR_MIPMAP_NEAREST ||
                sampler.minFilter == GL_LINEAR_MIPMAP_LINEAR)
            {
                glGenerateMipmap(GL_TEXTURE_2D);
            }
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        return textureObjects;
    }

    std::vector<GLuint> Model::createBufferObjects(
        const tinygltf::Model &model)
    {
        std::vector<GLuint> bufferObjects(model.buffers.size(), 0);

        glGenBuffers(GLsizei(model.buffers.size()), bufferObjects.data());
        for (size_t i = 0; i < model.buffers.size(); ++i)
        {
            glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[i]);
            glBufferStorage(GL_ARRAY_BUFFER, model.buffers[i].data.size(),
                            model.buffers[i].data.data(), 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return bufferObjects;
    }

    std::vector<GLuint> Model::createVertexArrayObjects(
        const tinygltf::Model &model, const std::vector<GLuint> &bufferObjects,
        std::vector<VertexArrayObject::VaoRange> &meshToVertexArrays)
    {
        std::vector<GLuint> vertexArrayObjects;

        meshToVertexArrays.resize(model.meshes.size());

        const GLuint VERTEX_ATTRIB_POSITION_IDX = 0;
        const GLuint VERTEX_ATTRIB_NORMAL_IDX = 1;
        const GLuint VERTEX_ATTRIB_TEXCOORD0_IDX = 2;

        std::map<std::string, GLuint> attributes;
        attributes.insert(std::make_pair("POSITION", VERTEX_ATTRIB_POSITION_IDX));
        attributes.insert(std::make_pair("NORMAL", VERTEX_ATTRIB_NORMAL_IDX));
        attributes.insert(std::make_pair("TEXCOORD_0", VERTEX_ATTRIB_TEXCOORD0_IDX));

        for (size_t i = 0; i < model.meshes.size(); ++i)
        {
            const auto &mesh = model.meshes[i];
            const auto vaoOffset = vertexArrayObjects.size();
            vertexArrayObjects.resize(vaoOffset + mesh.primitives.size());

            auto &vaoRange = meshToVertexArrays[i];
            vaoRange.begin = GLsizei(vaoOffset);
            vaoRange.count = GLsizei(mesh.primitives.size());
            glGenVertexArrays(vaoRange.count, &vertexArrayObjects[vaoRange.begin]);

            for (size_t pIdx = 0; pIdx < mesh.primitives.size(); ++pIdx)
            {
                const auto vao = vertexArrayObjects[vaoRange.begin + pIdx];
                const auto &primitive = mesh.primitives[pIdx];
                glBindVertexArray(vao);

                for (auto attribute : attributes)
                {
                    const auto iterator = primitive.attributes.find(attribute.first);
                    if (iterator != end(primitive.attributes))
                    {
                        const auto accessorIdx = (*iterator).second;
                        const auto &accessor = model.accessors[accessorIdx];
                        const auto &bufferView = model.bufferViews[accessor.bufferView];
                        const auto bufferIdx = bufferView.buffer;

                        glEnableVertexAttribArray(attribute.second);

                        assert(GL_ARRAY_BUFFER == bufferView.target);

                        glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[bufferIdx]);

                        const auto byteOffset = accessor.byteOffset + bufferView.byteOffset;
                        glVertexAttribPointer(attribute.second, accessor.type,
                                              accessor.componentType, GL_FALSE, GLsizei(bufferView.byteStride),
                                              (const GLvoid *)byteOffset);
                    }
                }

                if (primitive.indices >= 0)
                {
                    const auto accessorIdx = primitive.indices;
                    const auto &accessor = model.accessors[accessorIdx];
                    const auto &bufferView = model.bufferViews[accessor.bufferView];
                    const auto bufferIdx = bufferView.buffer;

                    assert(GL_ELEMENT_ARRAY_BUFFER == bufferView.target);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjects[bufferIdx]);
                }
            }
        }
        glBindVertexArray(0);

        if (applicationDebug)
            std::cout << "[GLTF Model] Number of VAOs: " << vertexArrayObjects.size() << std::endl;

        return vertexArrayObjects;
    }

    void Model::createDefaultTexture()
    {
        GLuint whiteTexture;

        float white[] = {1, 1, 1, 1};
        glGenTextures(1, &whiteTexture);
        glBindTexture(GL_TEXTURE_2D, whiteTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, &white);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        glBindTexture(GL_TEXTURE_2D, 0);

        m_whiteTexture = whiteTexture;
    }

} // namespace engine