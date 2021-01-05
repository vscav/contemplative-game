#pragma once
#ifndef _Scene_HPP_
#define _Scene_HPP_

#include <engine/Player.hpp>
#include <engine/Obstacle.hpp>
#include <engine/Collectable.hpp>
#include <engine/CubeMap.hpp>
#include <engine/Shader.hpp>
#include <engine/DirectionalLight.hpp>
#include <engine/PointLight.hpp>
#include <engine/ParticleSystem.hpp>

#include <list>
#include <memory>

namespace engine
{

    constexpr float endlessMaximumCollideDistance = 20.0f;

    /// \class Scene
    /// \brief Class that contains and manages the entities and objects of the application.
    class Scene
    {
    private:
        std::unique_ptr<Player> m_player; /*!< The entity player of the scene. */

        std::list<std::unique_ptr<Entity>> m_obstacles; /*!< A list of entities representing the obstacles in the scene. */

        std::list<std::unique_ptr<Entity>> m_collectables; /*!< A list of entities representing the collectables in the scene. */

        std::unique_ptr<DirectionalLight> m_directionalLight; /*!< The directional light of the scene. */

        std::unique_ptr<PointLights> m_pointLigths; /*!< An object to store and manage all the point lights in the scene. */

        std::unique_ptr<CubeMap> m_skybox; /*!< The skybox of the scene. */

        float m_maxCollideDistance = endlessMaximumCollideDistance; /*!< The maximum collision distance used in the scene for detection. */

    public:
        /// \brief Constructor.
        Scene() = default;
        /// \brief Destructor.
        ~Scene() = default;

        /// \brief Gets the player entity of the scene.
        /// \return The player entity of the scene.
        inline std::unique_ptr<Player> &player() { return m_player; };
        /// \brief Gets the player entity of the scene as a const reference.
        /// \return The player entity of the scene as a const reference.
        inline const std::unique_ptr<Player> &player() const { return m_player; };

        /// \brief Gets the directional light of the scene.
        /// \return The directional light of the scene.
        inline std::unique_ptr<DirectionalLight> &directionalLight() { return m_directionalLight; };
        /// \brief Gets the directional light of the scene as a const reference.
        /// \return The directional light of the scene as a const reference.
        inline const std::unique_ptr<DirectionalLight> &directionalLight() const { return m_directionalLight; };

        /// \brief Gets the point lights of the scene.
        /// \return The point lights of the scene.
        inline std::unique_ptr<PointLights> &pointLights() { return m_pointLigths; };
        /// \brief Gets the point lights of the scene as a const reference.
        /// \return The point lights of the scene as a const reference.
        inline const std::unique_ptr<PointLights> &pointLights() const { return m_pointLigths; };

        /// \brief Gets the obstacles of the scene.
        /// \return The obstacles of the scene.
        inline std::list<std::unique_ptr<Entity>> &obstacles() { return m_obstacles; };
        /// \brief Gets the obstacles of the scene as a const reference.
        /// \return The obstacles of the scene as a const reference.
        inline const std::list<std::unique_ptr<Entity>> &obstacles() const { return m_obstacles; };

        /// \brief Gets the collectables of the scene.
        /// \return The collectables of the scene.
        inline std::list<std::unique_ptr<Entity>> &collectables() { return m_collectables; };
        /// \brief Gets the collectables of the scene as a const reference.
        /// \return The collectables of the scene as a const reference.
        inline const std::list<std::unique_ptr<Entity>> &collectables() const { return m_collectables; };

        /// \brief Gets the skybox of the scene.
        /// \return The skybox of the scene.
        inline std::unique_ptr<CubeMap> &skybox() { return m_skybox; };
        /// \brief Gets the skybox of the scene as a const reference.
        /// \return The skybox of the scene as a const reference.
        inline const std::unique_ptr<CubeMap> &skybox() const { return m_skybox; };

        /// \brief Add a player to be rendered in the scene.
        inline void add(std::unique_ptr<Player> player) { m_player = std::move(player); };
        /// \brief Add a skybox to be rendered in the scene.
        inline void add(std::unique_ptr<CubeMap> skybox) { m_skybox = std::move(skybox); };

        /// \brief Handles the collision between two entities of the scene.
        /// \param firstEntity : The first entity which has collided the other.
        /// \param secondEntity : The second entity which has collided the first one.
        template <typename T, typename U>
        void handleCollision(T &firstEntity, U &secondEntity);

        /// \brief Clears the entire scene.
        void clearScene();

        /// \brief Updates the scene.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void update(const float dt);

        /// \brief Updates the obstacles list.
        /// \param obstaclesList : The list of entities representing the obstacles in the scene.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void updateObstaclesList(std::list<std::unique_ptr<Entity>> &obstaclesList, const float dt);

        /// \brief Updates the collectables list.
        /// \param collectablesList : The list of entities representing the collectables in the scene.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void updateCollectablesList(std::list<std::unique_ptr<Entity>> &collectablesList, const float dt);

        /// \brief Renders the scene.
        void render();

        /// \brief Renders all the entities of a given list.
        /// \param entitiesList : The list of entities to be rendered.
        template <typename T>
        void renderEntitiesList(const std::list<std::unique_ptr<Entity>> &entitiesList);
        
    };

} // namespace engine

#endif /* _Scene_HPP_ */