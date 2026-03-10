#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"


namespace m1
{
    class Lab5 : public gfxc::SimpleScene
    {
     public:
        Lab5();
        ~Lab5();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        implemented::Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float fov = 60.0f;
        float orthoWidth = 10.0f;
        float orthoHeight = 10.0f;

        enum class GridType {
            Grass,
            Water,
            Mountain
        };

        enum class RailOrientation {
            X,
            Z
        };

        struct GridObject {
            std::string name;
            Mesh* mesh;
            int i;  // a[i][j] - line and column in matrix of grids
            int j;
            glm::vec3 position;  // coordinates
            GridType type;
        };

        struct RailObject {
            std::string name;
            Mesh* mesh;
            GridType railType;
            glm::vec3 startPosition;
            glm::vec3 endPosition;
            RailOrientation orientation;

            RailObject* forward = nullptr;
            RailObject* left = nullptr;
            RailObject* right = nullptr;
            RailObject* back = nullptr;
        };

        struct TrainObject {
            std::string name;
            Mesh* mesh;
            RailObject* rail;
            glm::vec3 position;  // coordinates
            RailOrientation orientation;
            float speed;
            float progress;
        };

        std::vector<GridObject> gridObjects;
        std::vector<RailObject> railObjects;
        std::vector<TrainObject> trainObjects;

        float unit;


    };
}   // namespace m1
