#include "lab_m1/lab5/lab5.h"
#include "lab_m1/lab5/objects_3D.h"

#include <vector>
#include <string>
#include <iostream>
#include "../../../build/objects_3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab5::Lab5()
{
}


Lab5::~Lab5()
{
}


void Lab5::Init()
{
    renderCameraTarget = false;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    // useful variables
    unit = 0.5; // length & width of a grid piece
    int gridSize = 30;  // how many grids
    float startGridX = - (float)gridSize * unit / 2.0f;
    float startGridZ = - (float)gridSize * unit / 2.0f;

    RailObject* railSpawn = nullptr;
    

    /// Mesh Declare

    Mesh* wagon = objects_3D::CreateWagon("Wagon", glm::vec3(0, 0, 0), 0.2f, 0.3f, unit, 0.1f, 0.05f, 50, glm::vec3(1, 1, 0), glm::vec3(0.2f, 0.2f, 1));
    AddMeshToList(wagon);

    Mesh* engine = objects_3D::CreateEngine("Engine", glm::vec3(0, 0, 0), 0.2f, 0.3f, unit / 2.0f, 0.1f, unit / 2.0f, 0.1f, 0.05f, 50, glm::vec3(1, 1, 0), glm::vec3(0.2f, 0.2f, 1), glm::vec3(0.792f, 0.686f, 0.902f));
    AddMeshToList(engine);

    Mesh* grass = objects_3D::CreateCuboid("GrassGrid", glm::vec3(0, 0, 0), unit, 0.1f, unit, glm::vec3(0.322f, 0.91f, 0.322f));
    AddMeshToList(grass);

    Mesh* water = objects_3D::CreateCuboid("WaterGrid", glm::vec3(0, 0, 0), unit, 0.01f, unit, glm::vec3(0.322f, 0.322f, 0.91f));
    AddMeshToList(water);

    Mesh* mountain = objects_3D::CreateCuboid("MountainGrid", glm::vec3(0, 0, 0), unit, 0.2f, unit, glm::vec3(0.451f, 0.333f, 0.235f));
    AddMeshToList(mountain);

    Mesh* bridge = objects_3D::CreateRailsWater("Bridge", glm::vec3(0, 0, 0), unit, 0.05f, unit / 2.0f, glm::vec3(0.271, 0.239, 0.239), glm::vec3(1, 1, 1));
    AddMeshToList(bridge);

    Mesh* tunnel = objects_3D::CreateRailsMountain("Tunnel", glm::vec3(0, 0, 0), unit, 0.05f, unit / 2.0f, glm::vec3(0.271, 0.239, 0.239), glm::vec3(1, 1, 1));
    AddMeshToList(tunnel);

    Mesh* rails = objects_3D::CreateCuboid("Rails", glm::vec3(0, 0, 0), unit, 0.05f, unit / 2.0f, glm::vec3(0.271, 0.239, 0.239));
    AddMeshToList(rails);

    Mesh* gara1 = objects_3D::CreateCuboid("Gara1", glm::vec3(0, 0, 0), unit, unit, unit , glm::vec3(0.51f, 0.51f, 0.878f));
    AddMeshToList(gara1);

    Mesh* gara2 = objects_3D::CreateCylinder("Gara2", glm::vec3(0, 0, 0), unit, unit, 50, glm::vec3(0.725, 0.859, 0.643));
    AddMeshToList(gara2);

    Mesh* gara3 = objects_3D::CreateCuboid("Gara3", glm::vec3(0, 0, 0), unit, unit, 2 * unit, glm::vec3(0.9f, 0.3f, 0.3f));
    AddMeshToList(gara3);

    // Grids

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            GridObject grid;
            //mountain grids
            if (i <= 10 && i >= 2 && j <= 15 && j >= 2) {
                grid.name = "MountainGrid";
                grid.mesh = meshes["MountainGrid"];
                grid.type = GridType::Mountain;
            }
            //river grids
            else if (i == 3 * gridSize / 4 || j == 3 * gridSize / 4) {
                grid.name = "WaterGrid";
                grid.mesh = meshes["WaterGrid"];
                grid.type = GridType::Water;
            }
            //grass grids
            else {
                grid.name = "GrassGrid";
                grid.mesh = meshes["GrassGrid"];
                grid.type = GridType::Grass;
            }

            grid.i = i;
            grid.j = j;
            grid.position = glm::vec3(startGridX + unit * j, 0, startGridZ + unit * i);

            gridObjects.push_back(grid);
        }
    }


    // Rails

    //corners of the rail system that have more pointers
    RailObject* corner1 = nullptr;
    RailObject* corner2 = nullptr;
    RailObject* corner3 = nullptr;
    RailObject* corner4 = nullptr;
    RailObject* corner5 = nullptr;
    RailObject* corner6 = nullptr;
    RailObject* corner7 = nullptr;
    RailObject* corner8 = nullptr;
    RailObject* corner9 = nullptr;

    RailObject* previous = nullptr; // to connect the rails
    for (int j = 6; j <= 24; j++) {
        for (int i = 6; i <= 24; i++) {
            if (i == 24 || i == 6 || i == 16) {
                railObjects.emplace_back();
                RailObject* rail = &railObjects.back();
                int gridNo = i * 30 + j;
                if (gridObjects.at(gridNo).name == "MountainGrid") {
                    rail->name = "Tunnel";
                    rail->mesh = meshes["Tunnel"];
                    rail->railType = GridType::Mountain;
                }
                if (gridObjects.at(gridNo).name == "WaterGrid") {
                    rail->name = "Bridge";
                    rail->mesh = meshes["Bridge"];
                    rail->railType = GridType::Water;
                }
                if (gridObjects.at(gridNo).name == "GrassGrid") {
                    rail->name = "Rails";
                    rail->mesh = meshes["Rails"];
                    rail->railType = GridType::Grass;
                }

                rail->startPosition = glm::vec3(startGridX + unit * j, 0.1f, startGridZ + unit * i);
                rail->endPosition = glm::vec3(startGridX + unit * (j + 1) - 0.001f, 0.3f, startGridZ + unit * i);
                rail->orientation = RailOrientation::X;

                if (j != 6) { //previous rails for j=4 rails don't exist right now
                    previous->forward = rail;
                    rail->back = previous;
                }
                previous = rail;

                //finding all corner rails
                if (j == 6) {
                    if (i == 6) {
                        corner1 = rail;
                    }
                    else if (i == 16) {
                        corner4 = rail;
                    }
                    else if (i == 24) {
                        corner7 = rail;
                    }
                }
                else if (j == 16) {
                    if (i == 6) {
                        corner2 = rail;
                    }
                    else if (i == 16) {
                        corner5 = rail;
                    }
                    else if (i == 24) {
                        corner8 = rail;
                    }
                }
                else if (j == 24) {
                    if (i == 6) {
                        corner3 = rail;
                    }
                    else if (i == 16) {
                        corner6 = rail;
                    }
                    else if (i == 24) {
                        corner9 = rail;
                    }
                }


            }
        }
    }

        for (int i = 6; i <= 24; i++) {
            for (int j = 6; j <= 24; j++) {
                if (j == 24 || j == 6 || j == 16) {
                    railObjects.emplace_back();
                    RailObject* rail = &railObjects.back();
                    int gridNo = i * 30 + j;
                    if (gridObjects.at(gridNo).name == "MountainGrid") {
                        rail->name = "Tunnel";
                        rail->mesh = meshes["Tunnel"];
                        rail->railType = GridType::Mountain;
                    }
                    if (gridObjects.at(gridNo).name == "WaterGrid") {
                        rail->name = "Bridge";
                        rail->mesh = meshes["Bridge"];
                        rail->railType = GridType::Water;
                    }
                    if (gridObjects.at(gridNo).name == "GrassGrid") {
                        rail->name = "Rails";
                        rail->mesh = meshes["Rails"];
                        rail->railType = GridType::Grass;
                    }

                    rail->startPosition = glm::vec3(startGridX + unit * j, 0.1f, startGridZ + unit * i);
                    rail->endPosition = glm::vec3(startGridX + unit * (j + 1) - 0.001f, 0.3f, startGridZ + unit * i);
                    rail->orientation = RailOrientation::Z;

                    if (i != 6) { //previous rails for i=6 rails don't exist right now
                        previous->forward = rail;
                        rail->back = previous;
                    }

                    if (i == 10 && j == 24) {
                        railSpawn = rail;
                    }

                    if (i == 6 && j == 6) {
                        corner1->left = rail;
                        rail->right = corner1;
                    }
                    if (i == 6 && j == 16) {
                        corner2->left = rail;
                        corner2->right = rail;
                        rail->right = corner2;
                        rail->left = corner2;
                    }
                    if (i == 6 && j == 24) {
                        corner3->right = rail;
                        rail->left = corner3;
                    }
                    if (i == 16 && j == 6) {
                        corner4->left = rail;
                        corner4->right = rail;
                        rail->right = corner4;
                        rail->left = corner4;
                    }
                    if (i == 16 && j == 16) {
                        corner5->left = rail;
                        corner5->right = rail;
                        rail->right = corner5;
                        rail->left = corner5;
                    }
                    if (i == 16 && j == 24) {
                        corner6->left = rail;
                        corner6->right = rail;
                        rail->right = corner6;
                        rail->left = corner6;
                    }
                    if (i == 24 && j == 6) {
                        corner7->right = rail;
                        rail->left = corner7;
                    }
                    if (i == 24 && j == 16) {
                        corner8->left = rail;
                        corner8->right = rail;
                        rail->right = corner8;
                        rail->left = corner8;
                    }
                    if (i == 24 && j == 24) {
                        corner9->right = rail;
                        rail->left = corner9;
                    }

                    previous = rail;
                }
            }
        }
    
    ////Train
    //    //- engine
    //TrainObject trainEngine;
    //trainEngine.name = "Engine";
    //trainEngine.mesh = meshes["Engine"];
    //trainEngine.rail = railSpawn;
    //trainEngine.position = trainEngine.rail->startPosition;
    //trainEngine.orientation = trainEngine.rail->orientation;
    //trainEngine.progress = 0;
    //trainEngine.speed = 0.5f;
    //trainObjects.push_back(trainEngine);
    //    //-wagons
    //for (int i = 0; i < 3; i++) {
    //    TrainObject trainWagon;
    //    trainWagon.name = "Wagon";
    //    trainWagon.mesh = meshes["Wagon"];
    //    //trainWagon.rail = railSpawn->back;
    //    trainWagon.position = trainEngine.position - glm::vec3(0, 0, -unit * (i + 1));
    //    trainWagon.orientation = RailOrientation::Z;
    //    trainWagon.progress = 0;
    //    trainWagon.speed = 0.5f;

    //    trainObjects.push_back(trainWagon);
    //    //railSpawn = railSpawn->back;
    //}
    

    /*Mesh* mesh = new Mesh("sphere");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
    meshes[mesh->GetMeshID()] = mesh;*/

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

}


void Lab5::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab5::Update(float deltaTimeSeconds)
{
    for (auto& obj : gridObjects) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(obj.position.x, obj.position.y, obj.position.z));
        RenderMesh(obj.mesh, shaders["VertexColor"], modelMatrix);
    }

    for (auto& obj : railObjects) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(obj.startPosition.x, obj.startPosition.y, obj.startPosition.z));
        if (obj.orientation == RailOrientation::Z) {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(unit / 2.0f, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-unit, 0, 0));
        }
        if (obj.name == "Tunnel") {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.1f, 0));
        }
        
        RenderMesh(obj.mesh, shaders["VertexColor"], modelMatrix);
    }

    /*for (auto& obj : trainObjects) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(obj.position.x, obj.position.y, obj.position.z));
        if (obj.orientation == RailOrientation::Z) {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(unit / 2.0f, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-unit, 0, 0));
        }
        if (obj.rail->name == "Tunnel") {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.1f, 0));
        }

        RenderMesh(obj.mesh, shaders["VertexColor"], modelMatrix);
    }*/

    {
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix = glm::translate(modelMatrix, glm::vec3(4.75f, 0.3f, -unit-0.1f));
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Wagon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);

        modelMatrix = glm::translate(modelMatrix, glm::vec3(4.75f, 0.3f,2*( - unit - 0.1f)));
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Wagon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);

        modelMatrix = glm::translate(modelMatrix, glm::vec3(4.75f, 0.3f, 3 * (-unit - 0.1f)));
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Wagon"], shaders["VertexColor"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(5.25f, 0.15f, 0));
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Gara1"], shaders["VertexColor"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(5.75f, 0.3f, 4));
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Gara2"], shaders["VertexColor"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-5.75f, 0.15f, -0.5f));
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Gara3"], shaders["VertexColor"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(4.75f, 0.3f, 0));
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Engine"], shaders["VertexColor"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Bridge"], shaders["VertexColor"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Tunnel"], shaders["VertexColor"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        //modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["Rails"], shaders["VertexColor"], modelMatrix);
    }

    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }
}


void Lab5::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Lab5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab5::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->TranslateForward(cameraSpeed * deltaTime);

        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(cameraSpeed * deltaTime);

        }
    }

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.

    float fovStep = 30.0f * deltaTime;

    // Zoom in
    if (window->KeyHold(GLFW_KEY_Z)) {
        fov -= fovStep;
        if (fov < 10.0f) fov = 10.0f;
        projectionMatrix = glm::perspective(glm::radians(fov), window->props.aspectRatio, 0.01f, 200.0f);
    }

    // Zoom out
    if (window->KeyHold(GLFW_KEY_X)) {
        fov += fovStep;
        if (fov > 120.0f) fov = 120.0f;
        projectionMatrix = glm::perspective(glm::radians(fov), window->props.aspectRatio, 0.01f, 200.0f);
    }

    float orthoStep = 10.0f * deltaTime;

    if (window->KeyHold(GLFW_KEY_U)) {
        orthoHeight += orthoStep;
        projectionMatrix = glm::ortho(-orthoWidth / 2, orthoWidth / 2, -orthoHeight / 2, orthoHeight / 2, 0.01f, 200.0f);
    }

    if (window->KeyHold(GLFW_KEY_H)) {
        orthoWidth -= orthoStep;
        projectionMatrix = glm::ortho(-orthoWidth / 2, orthoWidth / 2, -orthoHeight / 2, orthoHeight / 2, 0.01f, 200.0f);
    }

    if (window->KeyHold(GLFW_KEY_J)) {
        orthoHeight -= orthoStep;
        projectionMatrix = glm::ortho(-orthoWidth / 2, orthoWidth / 2, -orthoHeight / 2, orthoHeight / 2, 0.01f, 200.0f);
    }

    if (window->KeyHold(GLFW_KEY_K)) {
        orthoWidth += orthoStep;
        projectionMatrix = glm::ortho(-orthoWidth / 2, orthoWidth / 2, -orthoHeight / 2, orthoHeight / 2, 0.01f, 200.0f);
    }

}


void Lab5::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections

    // Proiectie Ortografica
    if (key == GLFW_KEY_O)
    {
        float left = -5.0f;
        float right = 5.0f;
        float bottom = -5.0f;
        float top = 5.0f;
        float near = 0.01f;
        float far = 200.0f;

        projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
    }

    // Proiectie Perspectiva
    if (key == GLFW_KEY_P)
    {
        float fov = RADIANS(60.0f);
        float aspect = window->props.aspectRatio;
        float near = 0.01f;
        float far = 200.0f;

        projectionMatrix = glm::perspective(fov, aspect, near, far);
    }

}


void Lab5::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OY(-deltaX * sensivityOY);

            camera->RotateFirstPerson_OX(-deltaY * sensivityOX);

        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OY(-deltaX * sensivityOY);

            camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
        }
    }
}


void Lab5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab5::OnWindowResize(int width, int height)
{
}

/*{
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
        RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
    }

    // Box1
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1.5f, -2));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f * deltaTimeSeconds), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    // Box2
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0.3f, 2));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(30.0f), glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f, 1.2f, 0.7f));
        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }*/