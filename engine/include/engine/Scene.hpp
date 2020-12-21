#pragma once
#ifndef _Scene_HPP_
#define _Scene_HPP_

#include <engine/Entity.hpp>
#include <engine/CubeMap.hpp>
#include <engine/Shader.hpp>

#include <list>
#include <memory>

namespace engine
{

    class Scene
    {
    private:
        // to do : create class Player
        // std::unique_ptr<Player> m_player;

        std::list<std::unique_ptr<Entity>> m_entities;

        // to do : create class Collectable
        // std::vector<std::pair<std::unique_ptr<Collectable>, std::unique_ptr<Shader>>> m_collectables;

        std::unique_ptr<CubeMap> m_skybox = nullptr;

    public:
        /// \brief Constructor.
        // to do : use entity constructor to define the inherited object Player
        Scene() = default;
        /// \brief Destructor.
        ~Scene() = default;

        inline std::list<std::unique_ptr<Entity>> &entities() { return m_entities; };
        inline const std::list<std::unique_ptr<Entity>> &entities() const { return m_entities; };

        inline std::unique_ptr<CubeMap> &skybox() { return m_skybox; };
        inline const std::unique_ptr<CubeMap> &skybox() const { return m_skybox; };

        /// \brief Add a renderable entity to the list of entities to be displayed in the scene.
        void add(std::unique_ptr<Entity> entity) { m_entities.push_back(std::move(entity)); };
        /// \brief Add a cubemap/skybox to be rendered in the scene.
        void add(std::unique_ptr<CubeMap> skybox) { m_skybox = std::move(skybox); };

        void render()
        {
            if (skybox() != nullptr)
            {
                skybox()->render();
            }

            if (!m_entities.empty())
            {
                auto it = m_entities.begin();
                for (it = m_entities.begin(); it != m_entities.end(); ++it)
                {
                    if (it->get() != nullptr)
                    {
                        it->get()->render();
                    }
                }
            }
        };
    };

} // namespace engine

#endif /* _Scene_HPP_ */