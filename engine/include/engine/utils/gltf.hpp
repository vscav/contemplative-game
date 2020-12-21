#pragma once

#include <engine/dependencies/glm.hpp>
#include <engine/dependencies/tiny_gltf.h>

namespace engine
{

    glm::mat4 getLocalToWorldMatrix(const tinygltf::Node &node, const glm::mat4 &parentMatrix);

    void computeSceneBounds(const tinygltf::Model &model, glm::vec3 &bboxMin, glm::vec3 &bboxMax);

} // namespace engine