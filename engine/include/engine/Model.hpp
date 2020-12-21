#pragma once
#ifndef _Model_HPP_
#define _Model_HPP_

#include <engine/Camera.hpp>
#include <engine/Shader.hpp>
#include <engine/VertexArrayObject.hpp>
#include <engine/utils/filesystem.hpp>
#include <engine/dependencies/tiny_gltf.h>

#include <GL/glew.h>

namespace engine
{
    /// \class Model
    /// \brief Class for instanciating 3D model and using gltf file routine (with tiny gltf library).
    class Model
    {
    public:
        /// \brief Parameterized constructor.
        /// \param gltfFilePath : The path to the GLTF file.
        explicit Model(const std::string &gltfFilePath);
        /// \brief Default destructor.
        ~Model() = default;

        /// \brief Loads the GLTF file which describes the 3D model.
        bool loadGltfFile(tinygltf::Model &model);

        /// \brief Computes a vector of texture objects.
        /// Each texture object is filled with an image and sampling parameters from the corresponding texture of the glTF file.
        /// \param model : The 3D model.
        /// \return A vector of texture objects.
        std::vector<GLuint> createTextureObjects(const tinygltf::Model &model) const;
        /// \brief Computes the vector of buffer objects from the 3D model and returns it.
        /// \param model : The 3D model.
        /// \return A vector of buffer objects.
        std::vector<GLuint> createBufferObjects(const tinygltf::Model &model);
        /// \brief  Takes the 3D model and the vector of buffer objects previously created, creates an array of vertex array objects and returns it.
        /// It then fills the input vector meshIndexToVaoRange with the range of VAOs for each mesh.
        /// \param model : The 3D model.
        /// \param bufferObjects : The vector of buffer objects obtained from the model.
        /// \param meshToVertexArrays : The vector containing the range of VAOs for each mesh.
        std::vector<GLuint> createVertexArrayObjects(const tinygltf::Model &model,
                                                     const std::vector<GLuint> &bufferObjects,
                                                     std::vector<VertexArrayObject::VaoRange> &meshToVertexArrays);

        /// \brief Renders the model to the screen/window.
        /// \param shader : The shaders associated to the model and to its entity.
        void render(Shader *shader);

    private:
        tinygltf::Model m_model; /*!< The 3D model. */
        fs::path m_gltfFilePath; /*!< The path to the GLTF file which describes the 3D model. */

        std::vector<GLuint> m_textureObjects;     /*!< The vector of texture objects obtained from the model. */
        std::vector<GLuint> m_bufferObjects;      /*!< The vector of buffer objects obtained from the model. */
        std::vector<GLuint> m_vertexArrayObjects; /*!< The vector of array objects computed from the model and its meshes. */

        std::vector<VertexArrayObject::VaoRange> m_meshToVertexArrays; /*!< The vector containing the range of VAOs for each mesh. */

        GLuint m_whiteTexture = 0; /*!< This will be used for the base color of objects that have no materials. */

        // bool m_lightFromCamera; /*!< Boolean used to tell whether or not the directionnal light comes from the camera. */
        // bool m_applyOcclusion;
    };

} // namespace engine

#endif /* _Model_HPP_ */