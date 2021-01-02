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

    class Scene
    {
    private:
        std::unique_ptr<Player> m_player;

        std::list<std::unique_ptr<Obstacle>> m_obstacles;

        std::list<std::unique_ptr<Collectable>> m_collectables;

        std::unique_ptr<DirectionalLight> m_directionalLight;

        std::unique_ptr<PointLights> m_pointLigths;

        std::unique_ptr<CubeMap> m_skybox;

        float m_maxCollideDistance = endlessMaximumCollideDistance;

    public:
        /// \brief Constructor.
        Scene() = default;
        /// \brief Destructor.
        ~Scene() = default;

        /// \brief
        inline std::unique_ptr<Player> &player() { return m_player; };
        /// \brief
        inline const std::unique_ptr<Player> &player() const { return m_player; };

        /// \brief
        inline std::unique_ptr<DirectionalLight> &directionalLight() { return m_directionalLight; };
        /// \brief
        inline const std::unique_ptr<DirectionalLight> &directionalLight() const { return m_directionalLight; };

        /// \brief
        inline std::unique_ptr<PointLights> &pointLights() { return m_pointLigths; };
        /// \brief
        inline const std::unique_ptr<PointLights> &pointLights() const { return m_pointLigths; };

        /// \brief
        inline std::list<std::unique_ptr<Obstacle>> &obstacles() { return m_obstacles; };
        /// \brief
        inline const std::list<std::unique_ptr<Obstacle>> &obstacles() const { return m_obstacles; };

        /// \brief
        inline std::list<std::unique_ptr<Collectable>> &collectables() { return m_collectables; };
        /// \brief
        inline const std::list<std::unique_ptr<Collectable>> &collectables() const { return m_collectables; };

        /// \brief
        inline std::unique_ptr<CubeMap> &skybox() { return m_skybox; };
        /// \brief
        inline const std::unique_ptr<CubeMap> &skybox() const { return m_skybox; };

        // /// \brief
        // inline std::unique_ptr<ParticleSystem> &particleSystem() { return m_particleSystem; };
        // /// \brief
        // inline const std::unique_ptr<ParticleSystem> &particleSystem() const { return m_particleSystem; };

        // /// \brief
        // inline ParticleProps &particle() { return m_particle; };
        // /// \brief
        // inline const ParticleProps &particle() const { return m_particle; };

        /// \brief Add the player in the scene.
        inline void add(std::unique_ptr<Player> player) { m_player = std::move(player); };
        /// \brief Add point lights to be rendered in the scene.
        inline void add(std::unique_ptr<CubeMap> skybox) { m_skybox = std::move(skybox); };
        /// \brief Add a renderable entity to the list of entities to be displayed in the scene.
        inline void add(std::unique_ptr<Obstacle> obstacle) { m_obstacles.push_back(std::move(obstacle)); };
        /// \brief Add a renderable entity to the list of entities to be displayed in the scene.
        inline void add(std::unique_ptr<Collectable> collectable) { m_collectables.push_back(std::move(collectable)); };
        /// \brief Add a directional light to the scene.
        inline void add(std::unique_ptr<DirectionalLight> directionalLight) { m_directionalLight = std::move(directionalLight); };
        /// \brief Add a point lights container to the scene. The point ligths that it contains will then be rendered.
        inline void add(std::unique_ptr<PointLights> pointLights) { m_pointLigths = std::move(pointLights); };
        // /// \brief
        // inline void add(std::unique_ptr<ParticleSystem> particleSystem) { m_particleSystem = std::move(particleSystem); };

        /// \brief
        template <typename T, typename U>
        void handleCollision(T &firstObject, U &secondObject);

        /// \brief
        void update(const float dt);

        /// \brief
        void updateObstaclesList(std::list<std::unique_ptr<Obstacle>> &obstaclesList, const float dt);

        /// \brief
        void updateCollectablesList(std::list<std::unique_ptr<Collectable>> &collectablesList, const float dt);

        /// \brief
        void render();

        /// \brief 
        template <typename T>
        void renderEntitiesList(const std::list<std::unique_ptr<T>> &entitiesList);

        // TO DO: method: clear the scene
    };

} // namespace engine

#endif /* _Scene_HPP_ */