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

            if (data.find("entities") != nullptr)
                deserializeArrayIntoList(data.at("entities"), res->obstacles());

            if (data.find("player") != nullptr)
                deserializePlayer(data.at("player"), res->player());

            if (data.find("directionalLight") != nullptr)
                deserializeDirectionalLight(data.at("directionalLight"), res->directionalLight());

            // if (data.find("pointLights") != nullptr)
            // {
            //     auto pointLights = std::unique_ptr<PointLights>(new PointLights());
            //     deserializePointLights(data.at("pointLights"), pointLights);
            // }

            std::cout << "[Serializer] Serializer is done loading the scene" << std::endl;

            return res;
        }

        // void deserializePointLights(const tao::json::value &data, std::unique_ptr<PointLights> &destination)
        // {
        //     std::vector<tao::json::value> pointLights = data.get_array();

        //     auto it = pointLights.begin();
        //     while (it != pointLights.end())
        //     {
        //         try
        //         {
        //             destination.addPointLight(deserializePointLight(*it));
        //         }
        //         catch (std::exception &e)
        //         {
        //             std::cerr << e.what() << std::endl;
        //             std::cerr << "Light will be ignored" << std::endl;
        //         }

        //         ++it;
        //     }
        // }

        //  void deserializePointLight(const tao::json::value &data, std::unique_ptr<Player> &destination)
        // {}

        void deserializeArrayIntoList(
            const tao::json::value &data,
            std::list<std::unique_ptr<Entity>> &destinationList)
        {
            std::vector<tao::json::value> entities = data.get_array();

            auto it = entities.begin();
            while (it != entities.end())
            {
                try
                {
                    destinationList.push_back(static_cast<std::unique_ptr<Entity>>(&deserializeEntity(*it)));
                }
                catch (std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                    std::cerr << "Entity will be ignored" << std::endl;
                }

                ++it;
            }
        }

        void deserializePlayer(const tao::json::value &data, std::unique_ptr<Player> &destination)
        {
            destination = std::make_unique<Player>(Player(
                Entity(
                    new Model("application/res/models/spaceship/scene.gltf"),
                    new Shader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag"),
                    false)));
        }

        void deserializeDirectionalLight(const tao::json::value &data, std::unique_ptr<DirectionalLight> &destination)
        {
            glm::vec3 intensity = (data.find("intensity") != nullptr) ? deserializeVector3(data.at("intensity")) : glm::vec3(1.0f);
            glm::vec3 color = (data.find("color") != nullptr) ? deserializeVector3(data.at("color")) : glm::vec3(1.0f);
            glm::vec3 direction = (data.find("direction") != nullptr) ? deserializeVector3(data.at("direction")) : glm::vec3(1.0f);
            
            bool isStatic = (data.find("isStatic") != nullptr) ? data.at("isStatic").get_boolean() : true;

            destination = std::make_unique<DirectionalLight>(DirectionalLight(intensity,
                                                                              color,
                                                                              direction,
                                                                              isStatic));
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
            glm::vec3 position = (nullptr != data.find("position")) ? deserializeVector3(data.at("position")) : glm::vec3(0.0f);
            glm::vec3 rotation = (nullptr != data.find("rotation")) ? deserializeVector3(data.at("rotation")) : glm::vec3(0.0f);
            glm::vec3 scale = (nullptr != data.find("scale")) ? deserializeVector3(data.at("scale")) : glm::vec3(1.0f);

            return *new Transform(position, scale, rotation);
        }

        glm::vec3 deserializeVector3(const tao::json::value &data)
        {
            return glm::vec3(
                data.at(0).as<float>(),
                data.at(1).as<float>(),
                data.at(2).as<float>());
        }
    };

} // namespace engine

#endif /* _Serializer_HPP_ */