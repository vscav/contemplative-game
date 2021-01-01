#include <engine/Serializer.hpp>
#include <engine/EngineException.hpp>
#include <engine/utils/common.hpp>

namespace engine
{

    std::shared_ptr<Scene> Serializer::load(std::string sceneFilePath)
    {
        if (applicationDebug)
            std::cout << "[Serializer] Serializer is loading the scene" << std::endl;

        auto res = std::shared_ptr<Scene>(new Scene());

        try
        {
            tao::json::value data = tao::json::parse_file(sceneFilePath);

            if (data.find("entities") != nullptr)
            {
                deserializeArrayIntoList(data.at("entities"), res->obstacles());
            }

            if (data.find("player") != nullptr)
            {
                deserializePlayer(data.at("player"), res->player());
            }

            if (data.find("directionalLight") != nullptr)
            {
                deserializeDirectionalLight(data.at("directionalLight"), res->directionalLight());
            }

            if (data.find("pointLights") != nullptr)
            {
                res->pointLights() = std::unique_ptr<PointLights>(new PointLights());
                deserializePointLights(data.at("pointLights"), res->pointLights());
            }

            if (data.find("cubemap") != nullptr)
            {
                deserializeCubeMap(data.at("cubemap"), res);
            }
        }
        catch (tao::json_pegtl::input_error &err)
        {
            throw EngineException("Unable to read json file at: " + sceneFilePath, __FILE__, __LINE__);
        }

        if (applicationDebug)
            std::cout << "[Serializer] Serializer is done loading the scene" << std::endl;

        return res;
    }

    void Serializer::deserializeArrayIntoList(const tao::json::value &data, std::list<std::unique_ptr<Entity>> &destinationList)
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
            }

            ++it;
        }
    }

    void Serializer::deserializePlayer(const tao::json::value &data, std::unique_ptr<Player> &destination)
    {
        std::string modelName = deserializeString(data.at("model"));

        destination = std::make_unique<Player>(Player(
            Entity(
                new Model("application/res/models/" + modelName + "/scene.gltf"),
                new Shader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag"),
                false)));
    }

    void Serializer::deserializeDirectionalLight(const tao::json::value &data, std::unique_ptr<DirectionalLight> &destination)
    {
        glm::vec3 intensity = (data.find("intensity") != nullptr) ? deserializeVector3(data.at("intensity")) : glm::vec3(1.0f);
        glm::vec3 color = (data.find("color") != nullptr) ? deserializeVector3(data.at("color")) : glm::vec3(1.0f);
        glm::vec3 direction = (data.find("direction") != nullptr) ? deserializeVector3(data.at("direction")) : glm::vec3(1.0f);

        bool isStatic = (data.find("isStatic") != nullptr) ? deserializeBoolean(data.at("isStatic")) : true;

        destination = std::make_unique<DirectionalLight>(DirectionalLight(intensity,
                                                                          color,
                                                                          direction,
                                                                          isStatic));
    }

    void Serializer::deserializePointLights(const tao::json::value &data, std::unique_ptr<PointLights> &destination)
    {
        std::vector<tao::json::value> pointLights = data.get_array();

        auto it = pointLights.begin();
        while (it != pointLights.end())
        {
            glm::vec3 position = ((*it).find("position") != nullptr) ? deserializeVector3((*it).at("position")) : glm::vec3(0.0f);
            glm::vec3 scale = ((*it).find("scale") != nullptr) ? deserializeVector3((*it).at("scale")) : glm::vec3(0.25f);
            glm::vec3 ambient = ((*it).find("ambient") != nullptr) ? deserializeVector3((*it).at("ambient")) : glm::vec3(1.0f);
            glm::vec3 diffuse = ((*it).find("diffuse") != nullptr) ? deserializeVector3((*it).at("diffuse")) : glm::vec3(1.0f);

            float constant = ((*it).find("constant") != nullptr) ? deserializeFloat((*it).at("constant")) : 1.0f;
            float linear = ((*it).find("linear") != nullptr) ? deserializeFloat((*it).at("linear")) : 0.01f;
            float quadratic = ((*it).find("quadratic") != nullptr) ? deserializeFloat((*it).at("quadratic")) : 0.025f;

            destination->addPointLight(position,
                                       scale,
                                       constant,
                                       linear,
                                       quadratic,
                                       ambient,
                                       diffuse);

            ++it;
        }
    }

    Entity &Serializer::deserializeEntity(const tao::json::value &data)
    {
        Entity *res;

        std::string type = deserializeString(data.at("type"));

        if (type == "obstacle")
        {
            res = &deserializeObstacle(data);
        }
        // else if (type == "collectable")
        //     res = &deserializeCollectable(data);
        else
        {
            throw EngineException("[Serializer] Invalid entity type: " + type, __FILE__, __LINE__);
        }

        return *res;
    }

    Obstacle &Serializer::deserializeObstacle(const tao::json::value &data)
    {
        std::string modelName = deserializeString(data.at("model"));

        bool isStatic = (nullptr != data.find("isStatic")) ? deserializeBoolean(data.at("isStatic")) : true;

        return *new Obstacle(
            Entity(
                new engine::Model("application/res/models/" + modelName + "/scene.gltf"),
                new engine::Shader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag"),
                isStatic,
                deserializeTransform(data.at("transform"))));
    }

    void Serializer::deserializeCubeMap(const tao::json::value &data, std::shared_ptr<Scene> &destination)
    {
        std::string type = (data.find("type") != nullptr) ? deserializeString(data.at("type")) : "space";

        std::string cubemapPath = "application/res/textures/skybox/" + type + "/";

        std::unique_ptr<engine::CubeMap> skybox(
            new CubeMap(
                (cubemapPath + "front.png").c_str(),
                (cubemapPath + "left.png").c_str(),
                (cubemapPath + "back.png").c_str(),
                (cubemapPath + "bottom.png").c_str(),
                (cubemapPath + "right.png").c_str(),
                (cubemapPath + "top.png").c_str(),
                new Shader("application/res/shaders/skybox.vert", "application/res/shaders/skybox.frag")));

        destination->add(std::move(skybox));
    }

} // namespace engine