#pragma once
#ifndef _Serializer_HPP_
#define _Serializer_HPP_

#include <engine/Scene.hpp>

#include <tao/json.hpp>

#include <iostream>

namespace engine
{
    /// \class Serializer
    /// \brief Class that manages the instanciation of the scene objects by deserializing a json file.
    class Serializer
    {
    private:
        /// \brief Format a string to lowercase.
        static std::string format(const std::string &s)
        {
            std::string res(s);
            std::transform(res.begin(), res.end(), res.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            return res;
        }

    protected:
        /// \brief Default constructor.
        Serializer() = default;
        /// \brief Default destructor.
        ~Serializer() = default;

    public:
        /// \brief Returns the current serializer instance.
        /// \return The instance of the current serializer.
        static Serializer &getInstance()
        {
            static Serializer instance;
            return instance;
        }
        /// \brief Copy constructor.
        Serializer(const Serializer &) = delete;
        /// \brief Affectation/Copy assignment operator.
        Serializer &operator=(const Serializer &) = delete;

        /// \brief Parse and load the data from a json file.
        /// \param sceneFilePath : The path to the json file.
        std::shared_ptr<Scene> load(std::string sceneFilePath);

        /// \brief Add an obstacle entity to the obstacles list of the scene.
        /// \param data : The data corresponding to the obstacles json object.
        /// \param destinationList : A const getter to the obstacles of the scene.
        void deserializeObstacles(const tao::json::value &data, std::list<std::unique_ptr<Entity>> &destinationList);

        /// \brief Add an obstacle entity to the collectables list of the scene.
        /// \param data : The data corresponding to the collectables json object.
        /// \param destinationList : A const getter to the collectables of the scene.
        void deserializeCollectables(const tao::json::value &data, std::list<std::unique_ptr<Entity>> &destinationList);

        /// \brief Deserialize and add a player entity to the scene.
        /// \param data : The data corresponding to the player json object.
        /// \param destination : A const getter to the player of the scene.
        void deserializePlayer(const tao::json::value &data, std::unique_ptr<Player> &destination);

        /// \brief Deserialize and add a directional light to the scene.
        /// \param data : The data corresponding to the directional light json object.
        /// \param destination : A const getter to the directional light of the scene.
        void deserializeDirectionalLight(const tao::json::value &data, std::unique_ptr<DirectionalLight> &destination);

        /// \brief Deserialize and add point lights to the scene.
        /// \param data : The data corresponding to the point lights json object.
        /// \param destination : A const getter to the point lights of the scene.
        void deserializePointLights(const tao::json::value &data, std::unique_ptr<PointLights> &destination);

        /// \brief Deserialize and add a skybix to the scene.
        /// \param data : The data corresponding to the cubemap json object.
        /// \param destination : The scene.
        void deserializeCubeMap(const tao::json::value &data, std::shared_ptr<Scene> &destination);

        /// \brief Deserialize and instanciate a new obstacle based on the properties written in the json file.
        /// \param data : The json data corresponding to one specific obstacle in the json obstacles data.
        /// \return A reference to the obstacle newly created.
        Obstacle &deserializeObstacle(const tao::json::value &data);

        /// \brief Deserialize and instanciate a new collectable based on the properties written in the json file.
        /// \param data : The json data corresponding to one specific collectable in the json obstacles data.
        /// \return A reference to the collectable newly created.
        Collectable &deserializeCollectable(const tao::json::value &data);

        /// \brief Deserialize an array into a 3 floats vector.
        /// \param data : The data corresponding to an array of length 3 in the json file.
        /// \return A 3 floats vector.
        inline glm::vec3 deserializeVector3(const tao::json::value &data) { return glm::vec3(data.at(0).as<float>(), data.at(1).as<float>(), data.at(2).as<float>()); }

        /// \brief Deserialize a float.
        /// \param data : The data corresponding to a number in the json file.
        /// \return A float.
        inline float deserializeFloat(const tao::json::value &data) { return data.as<float>(); }

        /// \brief Deserialize a boolean.
        /// \param data : The data corresponding to a boolean (true/false) in the json file.
        /// \return A boolean.
        inline bool deserializeBoolean(const tao::json::value &data) { return data.get_boolean(); }

        /// \brief Deserialize a string.
        /// \param data : The data corresponding to a string in the json file.
        /// \return A string.
        inline std::string deserializeString(const tao::json::value &data) { return format(data.get_string()); }

        /// \brief Deserialize a json object of transformations array.
        /// \param data : A json object containing json transformations arrays.
        /// \return A reference to the transformation object newly created.
        Transform &deserializeTransform(const tao::json::value &data);
    };

} // namespace engine

#endif /* _Serializer_HPP_ */