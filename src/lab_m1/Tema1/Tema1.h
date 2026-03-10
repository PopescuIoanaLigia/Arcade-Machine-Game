#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        }; 

    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        bool IsShipValid();     // Func for checking if the ship is correctly drawn

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        float lengthScreen, heightScreen, lengthRedBox, heightRedBox, unit, offsetY;
        float lengthBlueBox, heightBlueBox, startBlueX, startBlueY, startGreenY, startGreenX;
        float spaceshipPositionX, spaceshipPositionY, startChickenY, startChickenX;
        int i, j;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;

        struct DragableObject {
            std::string name;
            glm::vec2 position;  // coordinates
            glm::vec2 size;     // hitbox
            Mesh* mesh;
        };

        struct NonDragableObject {
            std::string name;
            int idForGreenSquare = 0;
            glm::vec2 position;  // coordinates
            Mesh* mesh;
        };

        struct BlueSquare {
            int i = 0, j = 0;   // for the Position Matrix m[i][j]
            glm::vec2 position;  // coordinates
            Mesh* mesh;
        };

        struct DragableTempObject {   
            std::string name;
            glm::vec2 position;  // coordinates
            glm::vec2 size;     // hitbox
            glm::vec2 offset = glm::vec2(0, 0);
            Mesh* mesh;
        };

        struct Projectiles {
            std::string name;
            glm::vec2 position;  // coordinates
            glm::vec2 size;     // hitbox
            Mesh* mesh;
        };

        struct StartButtonObject {
            std::string name;
            glm::vec2 position;  // coordinates
            glm::vec2 size;     // hitbox
            Mesh* mesh;
        };

        struct ChickenInvaders {
            std::string name;
            glm::vec2 position;  // coordinates
            glm::vec2 size;     // hitbox
            int id;
            glm::vec2 base;    // for sinus movement
            Mesh* mesh;

            float attackCooldown = 0;
        };


        enum class ObjectType {
            Original,
            Temporary,
            Nothing
        };


        std::vector<DragableObject> dragableObjects; // the meshes that can be used to build the spaceship
        std::vector<NonDragableObject> nonDragableObjects; // stationary meshes
        std::vector<DragableTempObject> dragableTempObjects; //the new pieces that appear when you click on motor/ tun/ bumper/ greyblock
        std::vector<StartButtonObject> startButtonObjects;
        std::vector<BlueSquare> blueSquares; // the building space
        std::vector<Projectiles> projectiles;
        std::vector<ChickenInvaders> chickenInvadersObjs;

        bool isDragging = false;
        bool chickenInvaders = false;
        bool shouldLoseLife = false;
        ObjectType typeObj = ObjectType::Nothing;   //tells us if we are dragging FROM the original static mesh or a copy
        int selectedObject = -1;
        int selectedPosition = -1;
        int blocksAvailable = 10;

        float timeSin = 0;
        float fallSpeed = 0.3f;
        float lengthSinus = 0;
        float speedSinus = 2.0f;

        bool shake = false;
        float shakeAmount = 0.5f;
        LogicSpace originalLogicSpace = logicSpace;

        DragableTempObject firstObj;
        glm::vec2 dragOffset;
    };
}   // namespace m1
