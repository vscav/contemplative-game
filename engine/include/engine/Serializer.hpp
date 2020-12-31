#pragma once
#ifndef _Serializer_HPP_
#define _Serializer_HPP_

#include <engine/Scene.hpp>

#include <json.hpp>

#include <iostream>

namespace engine
{

    class Serializer
    {
    private:
        static std::string format(const std::string &s)
        {
            std::string res(s);
            std::transform(res.begin(), res.end(), res.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            return res;
        }

    protected:
        Serializer() = default;
        ~Serializer() = default;

    public:
        tao::json::value m_data;

        static Serializer &getInstance()
        {
            static Serializer instance;
            return instance;
        }

        Serializer(const Serializer &) = delete;
        Serializer &operator=(const Serializer &) = delete;

        std::shared_ptr<Scene> load(std::string sceneFilePath)
        {
            std::cout << "[Serializer] Serializer is loading the scene" << std::endl;

            auto res = std::shared_ptr<Scene>(new Scene());

            tao::json::value data = tao::json::parse_file(sceneFilePath);

            if (nullptr != data.find("directionalLight"))
                deserializeDirectionalLight(data.at("directionalLight"), res->directionalLight());

            if (nullptr != data.find("entities"))
                deserializeArrayIntoList<Entity>(data.at("entities"), res->obstacles());

            std::cout << "[Serializer] Serializer is done loading the scene" << std::endl;

            return res;
        }

        template <typename T>
        void deserializeArrayIntoList(
            const tao::json::value &data,
            std::list<std::unique_ptr<T>> &destinationList)
        {
            std::vector<tao::json::value> objects = data.get_array();

            auto it = objects.begin();
            while (it != objects.end())
            {
                try
                {
                    destinationList.push_back(static_cast<std::unique_ptr<T>>(&deserializeEntity(*it)));
                }
                catch (std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                    std::cerr << "Object will be ignored" << std::endl;
                }

                ++it;
            }
        }

        void deserializeDirectionalLight(const tao::json::value &data, std::unique_ptr<DirectionalLight> &destination)
        {
            // use array to call on lights in json and verify types (directional or point light)
            // bool isStatic = (nullptr != data.find("isStatic")) ? data.at("isStatic").get_boolean() : true;
            // use 
            destination = std::make_unique<DirectionalLight>(DirectionalLight(glm::vec3(1.0f),
                                                                              glm::vec3(0.5f, 0.65f, 1.0f),
                                                                              glm::vec3(1.0f)));
        }

        Entity &deserializeEntity(const tao::json::value &data)
        {
            Entity *res;

            std::string type = format(data.at("type").get_string());

            if (type == "obstacle")
                res = &deserializeObstacle(data);
            // else if (type == "collectable")
            //     res = &deserializeCollectable(data);
            else
                throw EngineException("[Serializer] Invalid entity type: " + type, __FILE__, __LINE__);

            return *res;
        }

        Obstacle &deserializeObstacle(const tao::json::value &data)
        {
            std::string modelName = format(data.at("model").get_string());
            std::string fragShaderName = format(data.at("shader").get_string());
            bool isStatic = (nullptr != data.find("isStatic")) ? data.at("isStatic").get_boolean() : true;

            return *new Obstacle(
                Entity(
                    new engine::Model("application/res/models/" + modelName + "/scene.gltf"),
                    new engine::Shader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag"),
                    isStatic,
                    deserializeTransform(data.at("transform"))));
        }

        // Collectable &deserializeCollectable(const tao::json::value &data)
        // {
        //     return *new Collectable();
        // }

        Transform &deserializeTransform(const tao::json::value &data)
        {
            glm::vec3 position = (nullptr != data.find("position")) ? deserializeVec3(data.at("position")) : glm::vec3(0.0f);
            glm::vec3 rotation = (nullptr != data.find("rotation")) ? deserializeVec3(data.at("rotation")) : glm::vec3(0.0f);
            glm::vec3 scale = (nullptr != data.find("scale")) ? deserializeVec3(data.at("scale")) : glm::vec3(1.0f);

            return *new Transform(position, scale, rotation);
        }

        glm::vec3 deserializeVec3(const tao::json::value &data)
        {
            return glm::vec3(
                data.at(0).as<float>(),
                data.at(1).as<float>(),
                data.at(2).as<float>());
        }
    };

} // namespace engine

#endif /* _Serializer_HPP_ */