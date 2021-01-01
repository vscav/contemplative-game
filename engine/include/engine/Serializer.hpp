#pragma once
#ifndef _Serializer_HPP_
#define _Serializer_HPP_

#include <engine/Scene.hpp>

#include <tao/json.hpp>

#include <iostream>

namespace engine
{
    /// \class
    /// \brief
    class Serializer
    {
    private:
        /// \brief
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
        /// \brief
        static Serializer &getInstance()
        {
            static Serializer instance;
            return instance;
        }
        /// \brief
        Serializer(const Serializer &) = delete;
        /// \brief
        Serializer &operator=(const Serializer &) = delete;

        /// \brief
        std::shared_ptr<Scene> load(std::string sceneFilePath);

        /// \brief
        void deserializeObstacles(const tao::json::value &data, std::list<std::unique_ptr<Entity>> &destinationList);

        // /// \brief
        // void deserializeCollectables(const tao::json::value &data, std::list<std::unique_ptr<Entity>> &destinationList);

        /// \brief
        void deserializePlayer(const tao::json::value &data, std::unique_ptr<Player> &destination);

        /// \brief
        void deserializeDirectionalLight(const tao::json::value &data, std::unique_ptr<DirectionalLight> &destination);

        /// \brief
        void deserializePointLights(const tao::json::value &data, std::unique_ptr<PointLights> &destination);

        /// \brief
        Obstacle &deserializeObstacle(const tao::json::value &data);

        // /// \brief
        // Collectable &deserializeCollectable(const tao::json::value &data);

        /// \brief
        void deserializeCubeMap(const tao::json::value &data, std::shared_ptr<Scene> &destination);

        /// \brief
        inline glm::vec3 deserializeVector3(const tao::json::value &data) { return glm::vec3(data.at(0).as<float>(), data.at(1).as<float>(), data.at(2).as<float>()); }

        /// \brief
        inline float deserializeFloat(const tao::json::value &data) { return data.as<float>(); }

        /// \brief
        inline bool deserializeBoolean(const tao::json::value &data) { return data.get_boolean(); }

        /// \brief
        inline std::string deserializeString(const tao::json::value &data) { return format(data.get_string()); }

        /// \brief
        Transform &deserializeTransform(const tao::json::value &data)
        {
            glm::vec3 position = (nullptr != data.find("position")) ? deserializeVector3(data.at("position")) : glm::vec3(0.0f);
            glm::vec3 rotation = (nullptr != data.find("rotation")) ? deserializeVector3(data.at("rotation")) : glm::vec3(0.0f);
            glm::vec3 scale = (nullptr != data.find("scale")) ? deserializeVector3(data.at("scale")) : glm::vec3(1.0f);

            return *new Transform(position, scale, rotation);
        }
    };

} // namespace engine

#endif /* _Serializer_HPP_ */