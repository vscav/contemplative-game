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
        /// \param sceneFilePath : The path to the json file.
        std::shared_ptr<Scene> load(std::string sceneFilePath);

        /// \brief
        /// \param data :
        /// \param destinationList :
        void deserializeObstacles(const tao::json::value &data, std::list<std::unique_ptr<Entity>> &destinationList);

        /// \brief
        /// \param data :
        /// \param destinationList :
        void deserializeCollectables(const tao::json::value &data, std::list<std::unique_ptr<Entity>> &destinationList);

        /// \brief
        /// \param data :
        /// \param destination :
        void deserializePlayer(const tao::json::value &data, std::unique_ptr<Player> &destination);

        /// \brief
        /// \param data :
        /// \param destination :
        void deserializeDirectionalLight(const tao::json::value &data, std::unique_ptr<DirectionalLight> &destination);

        /// \brief
        /// \param data :
        /// \param destination :
        void deserializePointLights(const tao::json::value &data, std::unique_ptr<PointLights> &destination);

        /// \brief
        /// \param data :
        /// \param destination :
        void deserializeCubeMap(const tao::json::value &data, std::shared_ptr<Scene> &destination);

        /// \brief
        /// \param data :
        Obstacle &deserializeObstacle(const tao::json::value &data);

        /// \brief
        /// \param data :
        Collectable &deserializeCollectable(const tao::json::value &data);

        /// \brief
        /// \param data :
        inline glm::vec3 deserializeVector3(const tao::json::value &data) { return glm::vec3(data.at(0).as<float>(), data.at(1).as<float>(), data.at(2).as<float>()); }

        /// \brief
        /// \param data :
        inline float deserializeFloat(const tao::json::value &data) { return data.as<float>(); }

        /// \brief
        /// \param data :
        inline bool deserializeBoolean(const tao::json::value &data) { return data.get_boolean(); }

        /// \brief
        /// \param data :
        inline std::string deserializeString(const tao::json::value &data) { return format(data.get_string()); }

        /// \brief
        /// \param data :
        Transform &deserializeTransform(const tao::json::value &data);
    };

} // namespace engine

#endif /* _Serializer_HPP_ */