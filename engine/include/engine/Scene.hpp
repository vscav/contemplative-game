#pragma once
#ifndef _Scene_HPP_
#define _Scene_HPP_

#include <engine/Player.hpp>
#include <engine/Obstacle.hpp>
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

        std::list<std::unique_ptr<Entity>> m_obstacles;

        std::unique_ptr<DirectionalLight> m_directionalLight;

        std::unique_ptr<PointLights> m_pointLigths;

        std::unique_ptr<CubeMap> m_skybox = nullptr;

        std::unique_ptr<ParticleSystem> m_particleSystem;

        ParticleProps m_particle;

        float m_maxCollideDistance = endlessMaximumCollideDistance;

    public:
        /// \brief Constructor.
        Scene()
        {
            m_particle.colorBegin = {25 / 255.0f, 25 / 255.0f, 112 / 255.0f, 1.0f};
            m_particle.colorEnd = {100 / 255.0f, 149 / 255.0f, 237 / 255.0f, 1.0f};
            m_particle.sizeBegin = 0.5f;
            m_particle.sizeVariation = 0.3f;
            m_particle.sizeEnd = 0.0f;
            m_particle.lifeTime = 10.0f;
            m_particle.velocity = {0.0f, 0.0f, 0.0f};
            m_particle.velocityVariation = {3.0f, 1.0f, 1.0f};
            m_particle.position = {0.0f, 0.0f, 0.0f};
        };
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
        inline std::list<std::unique_ptr<Entity>> &obstacles() { return m_obstacles; };
        /// \brief
        inline const std::list<std::unique_ptr<Entity>> &obstacles() const { return m_obstacles; };

        /// \brief
        inline std::unique_ptr<CubeMap> &skybox() { return m_skybox; };
        /// \brief
        inline const std::unique_ptr<CubeMap> &skybox() const { return m_skybox; };

        /// \brief
        inline std::unique_ptr<ParticleSystem> &particleSystem() { return m_particleSystem; };
        /// \brief
        inline const std::unique_ptr<ParticleSystem> &particleSystem() const { return m_particleSystem; };

        /// \brief
        inline ParticleProps &particle() { return m_particle; };
        /// \brief
        inline const ParticleProps &particle() const { return m_particle; };

        /// \brief Add the player in the scene.
        inline void add(std::unique_ptr<Player> player) { m_player = std::move(player); };
        /// \brief Add point lights to be rendered in the scene.
        inline void add(std::unique_ptr<CubeMap> skybox) { m_skybox = std::move(skybox); };
        /// \brief Add a renderable entity to the list of entities to be displayed in the scene.
        inline void add(std::unique_ptr<Entity> obstacle) { m_obstacles.push_back(std::move(obstacle)); };
        /// \brief Add a directional light to the scene.
        inline void add(std::unique_ptr<DirectionalLight> directionalLight) { m_directionalLight = std::move(directionalLight); };
        /// \brief Add a point lights container to the scene. The point ligths that it contains will then be rendered.
        inline void add(std::unique_ptr<PointLights> pointLights) { m_pointLigths = std::move(pointLights); };
        /// \brief
        inline void add(std::unique_ptr<ParticleSystem> particleSystem) { m_particleSystem = std::move(particleSystem); };

        /// \brief
        template <typename T, typename U>
        void handleCollision(T &firstObject, U &secondObject);

        /// \brief
        void update(const float dt);

        /// \brief
        void updateObstaclesList(std::list<std::unique_ptr<Entity>> &obstaclesList, const float dt);

        /// \brief
        void render();
    };

} // namespace engine

#endif /* _Scene_HPP_ */