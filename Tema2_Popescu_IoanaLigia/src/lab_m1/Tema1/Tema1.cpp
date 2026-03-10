#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // aspect makes the screen proportional with the logic space
    glm::ivec2 resolution = window->GetResolution();
    float aspect = (float)resolution.x / resolution.y;

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 30;   // logic width
    logicSpace.height = logicSpace.width / aspect; // logic height

    // global variables for the sizing of the meshes (in order to be proporional with the SCREEN and EACHOTHER)
    glm::vec3 corner = glm::vec3(0, 0, 0);
    lengthScreen = logicSpace.width;   // the length of the screen
    heightScreen = logicSpace.height;  // the height of the screen
    unit = lengthScreen / 26.0f;

    lengthSinus = unit;

    lengthRedBox = (lengthScreen - 0.2f) / 5;
    heightRedBox = (heightScreen - 0.2f) / 4;

    lengthBlueBox = unit * 19 -0.2f;
    heightBlueBox = unit * 11 -0.2f;


    Mesh* squareBlue = object2D::CreateSquare("squareBlue", corner - glm::vec3(0, 0, 0.012f), unit - 0.2f, glm::vec3(0.25f, 0.45f, 1),true);
    AddMeshToList(squareBlue);

    Mesh* squareGrey = object2D::CreateSquare("squareGrey", corner, unit, glm::vec3(0.5f, 0.5f, 0.5f), true);
    AddMeshToList(squareGrey);

    Mesh* squareGreen = object2D::CreateSquare("squareGreen", corner, unit, glm::vec3(0.2f, 1.0f, 0.2f), true);
    AddMeshToList(squareGreen);

    Mesh* projectileGreen = object2D::CreateSquare("projectileGreen", corner, unit / 2.0f, glm::vec3(0.2f, 1.0f, 0.2f), true);
    AddMeshToList(projectileGreen);

    Mesh* projectileRed = object2D::CreateSquare("projectileRed", corner, unit / 2.0f, glm::vec3(1.0f, 2.0f, 0.2f), true);
    AddMeshToList(projectileRed);

    Mesh* squareRed = object2D::CreateSquare("squareRed", corner, unit, glm::vec3(1.0f, 0.3f, 0.2f), true);
    AddMeshToList(squareRed);

    Mesh* startButtonGreen = object2D::CreateStartButton("startButtonGreen", corner, unit, glm::vec3(0.2f, 1.0f, 0.2f), true);
    AddMeshToList(startButtonGreen);

    Mesh* startButtonRed = object2D::CreateStartButton("startButtonRed", corner, unit, glm::vec3(1, 0.2f, 0.2f), true);
    AddMeshToList(startButtonRed);

    /*Mesh* rectangleGrey = object2D::CreateRectangle("rectangleGrey", corner, length, height, glm::vec3(0.9f, 0.9f, 0.9f), true);
    AddMeshToList(rectangleGrey);*/

    /*Mesh* semicircleGrey = object2D::CreateSemicircle("semicircleGrey", corner, 2, 2, 50, glm::vec3(0.9f, 0.9f, 0.9f), true);
    AddMeshToList(semicircleGrey);*/

    Mesh* motorOrange = object2D::CreateMotor("motorOrange", corner, unit, glm::vec3(1, 0.55f, 0.25f), glm::vec3(1, 0.40f, 0.20f), true);
    AddMeshToList(motorOrange);

    Mesh* tunGrey = object2D::CreateTun("tunGrey", corner, unit, 3 * unit, glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(0.2f, 0.2f, 0.2f), true);
    AddMeshToList(tunGrey);

    Mesh* bumperGrey = object2D::CreateBumper("bumperGrey", corner, 3 * unit, unit, glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.5f), true);
    AddMeshToList(bumperGrey);

    Mesh* rectangleRed = object2D::CreateRectangle("rectangleRed", corner - glm::vec3(0, 0, 0.012f), lengthScreen - 0.2f, heightScreen - 0.2f, glm::vec3(1.0f, 0.2f, 0.2f), false);
    AddMeshToList(rectangleRed);

    Mesh* rectangleRed2 = object2D::CreateRectangle("rectangleRed2", corner - glm::vec3(0, 0, 0.012f), lengthRedBox, heightRedBox, glm::vec3(1.0f, 0.2f, 0.2f), false);
    AddMeshToList(rectangleRed2);

    Mesh* rectangleBlueBox = object2D::CreateRectangle("rectangleBlueBox", corner - glm::vec3(0, 0, 0.012f), lengthBlueBox, heightBlueBox, glm::vec3(0.2f, 0.2f, 1.0f), false);
    AddMeshToList(rectangleBlueBox);

    //chicken Invader
    Mesh* chickenInvader = object2D::CreateChickenInvader("chickenInvader", corner, unit * 2.5, glm::vec3(0, 0, 1), glm::vec3(0.6f), glm::vec3(0.8f), glm::vec3(1, 0.5f, 0), true);
    AddMeshToList(chickenInvader);

    // Blue Squares
    startBlueX = 7 * unit;
    startBlueY = 3 * unit / 2.0f;
    for (i = 0; i < 17; i++) {
        for (j = 0; j < 9; j++) {
            NonDragableObject squareB;
            squareB.name = "squareBlue";
            squareB.mesh = meshes["squareBlue"];
            squareB.position = glm::vec2(startBlueX + unit * i, startBlueY + unit * j);

            nonDragableObjects.push_back(squareB);
        }
    }

    // Green Squares + Red Squares
    startGreenY = heightBlueBox + ((heightScreen - heightBlueBox) / 2.0f);
    startGreenX = lengthRedBox + (lengthScreen - lengthRedBox - 17.66f * unit) / 2.0f;
    for (i = 0; i < 10; i++) {
        //Green Squares
        NonDragableObject squareG;
        squareG.name = "squareGreen";
        squareG.mesh = meshes["squareGreen"];
        squareG.idForGreenSquare = i;
        squareG.position = glm::vec2(startGreenX + (unit * 1.66f) * i, startGreenY);
        nonDragableObjects.push_back(squareG);

        //Red Squares
        NonDragableObject squareR;
        squareR.name = "squareRed";
        squareR.mesh = meshes["squareRed"];
        squareR.idForGreenSquare = i;
        squareR.position = glm::vec2(startGreenX + (unit * 1.66f) * i, startGreenY);
        nonDragableObjects.push_back(squareR);

        
    }

    //Chicken Invaders
    startChickenY = heightBlueBox + ((heightScreen - heightBlueBox) / 2.0f);
    startChickenX = 4 * unit;
    for (i = 0; i < 6; i++) {
        ChickenInvaders chicken;
        chicken.name = "chickenInvader";
        chicken.mesh = meshes["chickenInvader"];
        chicken.id = i;
        chicken.position = glm::vec2(startChickenX + (unit * 3.5f) * i, startChickenY);
        chicken.base = chicken.position;
        chicken.attackCooldown = 2 + rand() % 7;
        chicken.size = glm::vec2(unit * 3, unit * 3);
        chickenInvadersObjs.push_back(chicken);
    }

    for (i = 0; i < 3; i++) {
        ChickenInvaders chicken;
        chicken.name = "chickenInvader";
        chicken.mesh = meshes["chickenInvader"];
        chicken.id = i + 6;
        chicken.position = glm::vec2(startChickenX + (unit * 3.5f) * i + 5.5f * unit, startChickenY -  2 * unit);
        chicken.base = chicken.position;
        chicken.size = glm::vec2(unit, unit);
        chickenInvadersObjs.push_back(chicken);
    }

    // Green Start button + Red Start button
    StartButtonObject startG;
    startG.name = "startButtonGreen";
    startG.mesh = meshes["startButtonGreen"];
    startG.position = glm::vec2(startGreenX + (unit * 1.66f) * 10, startGreenY);
    startButtonObjects.push_back(startG);

    StartButtonObject startR;
    startR.name = "startButtonRed";
    startR.mesh = meshes["startButtonRed"];
    startR.position = glm::vec2(startGreenX + (unit * 1.66f) * 10, startGreenY);
    startButtonObjects.push_back(startR);


    // Solid Block
    DragableObject block;
    block.name = "squareGrey";
    block.mesh = meshes["squareGrey"];
    block.position = glm::vec2(2 * unit + 0.2f, startBlueY);
    block.size = glm::vec2(unit, unit);
    dragableObjects.push_back(block);

    // Motor
    DragableObject motor;
    motor.name = "motorOrange";
    motor.mesh = meshes["motorOrange"];
    motor.position = glm::vec2(2 * unit + 0.2f, heightRedBox + startBlueY + 1 / 4.0f * unit);
    motor.size = glm::vec2(unit, unit * 2);
    dragableObjects.push_back(motor);

    // Tun
    DragableObject tun;
    tun.name = "tunGrey";
    tun.mesh = meshes["tunGrey"];
    tun.position = glm::vec2(2 * unit + 0.2f, heightRedBox * 2 + (heightRedBox - 3 * unit) / 2.0f);
    tun.size = glm::vec2(unit, unit * 3);
    dragableObjects.push_back(tun);

    // Bumper
    DragableObject bumper;
    bumper.name = "bumperGrey";
    bumper.mesh = meshes["bumperGrey"];
    bumper.position = glm::vec2(2 * unit + 0.2f, heightRedBox * 3 + (heightRedBox - 2 * unit) / 2.0f);
    bumper.size = glm::vec2(unit, unit);
    dragableObjects.push_back(bumper);

    // Red outline
    //   -the big outline
    NonDragableObject redOutline;
    redOutline.name = "rectangleRed";
    redOutline.mesh = meshes["rectangleRed"];
    redOutline.position = glm::vec2(0.1f, 0.1f);
    nonDragableObjects.push_back(redOutline);

    //   -the smaller outlines
    for (i = 0; i < 4; i++) {
        offsetY = i * 4.15;
        NonDragableObject redSmallOutline;
        redSmallOutline.name = "rectangleRed2";
        redSmallOutline.mesh = meshes["rectangleRed2"];
        redSmallOutline.position = glm::vec2(0.1f, 0.1f + offsetY);
        nonDragableObjects.push_back(redSmallOutline);
    }

    // Blue outline
    NonDragableObject blueOutline;
    blueOutline.name = "rectangleBlueBox";
    blueOutline.mesh = meshes["rectangleBlueBox"];
    blueOutline.position = glm::vec2(6 * unit, unit / 2.0f);
    nonDragableObjects.push_back(blueOutline);

    
}


// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw - the left half of the window
    viewSpace = ViewportSpace(0, 0, resolution.x , resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    // Compute the 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

    DrawScene(visMatrix, deltaTimeSeconds);
}


void Tema1::FrameEnd()
{
}


void Tema1::DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    // SPACESHIP BUILDER
    if (!chickenInvaders) {

        for (auto& obj : nonDragableObjects) {
            if (obj.name != "squareGreen" && obj.name != "squareRed") {
                modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
                RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
            }
            // for the visual disappearing of the green blocks
            else if (obj.name == "squareGreen" && obj.idForGreenSquare < blocksAvailable) {
                modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
                RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
            }
            else if (obj.name == "squareRed" && (10 - obj.idForGreenSquare) < -blocksAvailable) {
                modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
                RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
            }
        }

        for (auto& obj : dragableObjects) {
            modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
            RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
        }

        for (auto& obj : dragableTempObjects) {
            modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
            RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
        }

        for (auto& obj : startButtonObjects) {
            if (obj.name == "startButtonRed" && blocksAvailable < 0) {
                modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
                RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
            }
            else if (obj.name == "startButtonGreen" && blocksAvailable >= 0) {
                modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
                RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
            }

        }

    }
    // CHICKEN INVADERS
    else if (chickenInvaders) {
        for (auto& obj : dragableTempObjects) {
            obj.position.x = firstObj.position.x + obj.offset.x;
            obj.position.y = firstObj.position.y + obj.offset.y;
            modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
            RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
        }

        float projectileSpeed = 5.0f;
        for (auto& obj : projectiles) {

            if (obj.name == "projectileGreen") {
                obj.position.y += projectileSpeed * deltaTimeSeconds;
                modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
                RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
            }
            else if (obj.name == "projectileRed") {
                obj.position.y -= projectileSpeed * deltaTimeSeconds;
                modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
                RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
            }
            
        }

        
        timeSin += deltaTimeSeconds;

        for (auto& obj : chickenInvadersObjs) {
            // sin movement
            obj.position.y -= fallSpeed * deltaTimeSeconds;
            //obj.base.y = obj.position.y;
            obj.position.x = obj.base.x + sin(timeSin * speedSinus) * lengthSinus;
            modelMatrix = visMatrix * transform2D::Translate(obj.position.x, obj.position.y);
            RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);

            if (obj.position.y <= 0) {
                chickenInvaders = false;
            }

            // fire egg projectile
            obj.attackCooldown -= deltaTimeSeconds;
            if (obj.attackCooldown <= 0) {
                Projectiles egg;
                egg.size = glm::vec2(unit / 2.0f, unit / 2.0f);
                egg.position = obj.position - glm::vec2(0, obj.size.y);
                egg.name = "projectileRed";
                egg.mesh = meshes["projectileRed"];
                projectiles.push_back(egg);

                // reset cooldown at random
                obj.attackCooldown = 2 + rand() % 7;
            }
        }

        //collisions for chickens
        for (int c = 0; c < chickenInvadersObjs.size(); c++) {
            auto& obj = chickenInvadersObjs[c];
            for (int p = 0; p < projectiles.size(); p++) {
                auto& projectile = projectiles[p];
                if (projectile.name == "projectileGreen" &&
                    projectile.position.x >= obj.position.x - 1.5f * unit && projectile.position.x <= obj.position.x + obj.size.x - 0.5f * unit &&
                    projectile.position.y >= obj.position.y - 1.5f * unit && projectile.position.y <= obj.position.y + obj.size.y - 0.5f * unit) {
                    chickenInvadersObjs.erase(chickenInvadersObjs.begin() + c);

                    projectiles.erase(projectiles.begin() + p);
                    c--;
                    p--;
                }
            }
        }

        //collision for the ship
        for (int c = 0; c < dragableTempObjects.size(); c++) {
            auto& ship = dragableTempObjects[c];
            for (int p = 0; p < projectiles.size(); p++) {
                auto& projectile = projectiles[p];
                if (projectile.name == "projectileRed" &&
                    projectile.position.x >= ship.position.x && projectile.position.x <= ship.position.x + ship.size.x &&
                    projectile.position.y >= ship.position.y && projectile.position.y <= ship.position.y + ship.size.y ) {

                    chickenInvaders = false;
                    break;
                }
            }
        }

    }
    

}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

bool Tema1::IsShipValid() 
{
    //first check if spaceship is correctly built

    bool hasBlock = false;
    firstObj.position.x = lengthScreen;
    for (i = 0; i < dragableTempObjects.size(); i++) {
        auto& obj = dragableTempObjects[i];

        //finding the leftmost obj
        if (firstObj.position.x > obj.position.x) {
            firstObj = obj;
        }

        // ship has to have at least 1 block
        if (obj.name == "squareGrey") {
            hasBlock = true;
        }

        // ship has to be connected
        bool connected = false;
        if (dragableTempObjects.size() == 1) {
            connected = true;
        }
        if (dragableTempObjects.size() > 1) {
            for (j = 0; j < dragableTempObjects.size(); j++) {
                auto& otherObj = dragableTempObjects[j];

                if (i == j) continue;

                // CHECK CONEX
                if (obj.position.x - 1 / 2.0f * unit >= otherObj.position.x && obj.position.x - 1 / 2.0f * unit <= otherObj.position.x + otherObj.size.x &&
                    obj.position.y >= otherObj.position.y && obj.position.y <= otherObj.position.y + otherObj.size.y) {

                    connected = true; //check left of block
                }

                if (obj.position.x + 3 / 2.0f * unit >= otherObj.position.x && obj.position.x + 3 / 2.0f * unit <= otherObj.position.x + otherObj.size.x &&
                    obj.position.y >= otherObj.position.y && obj.position.y <= otherObj.position.y + otherObj.size.y) {

                    connected = true; //check right of block
                }

                if (obj.position.x >= otherObj.position.x && obj.position.x <= otherObj.position.x + otherObj.size.x &&
                    obj.position.y - 1 / 2.0f * unit >= otherObj.position.y && obj.position.y - 1 / 2.0f * unit <= otherObj.position.y + otherObj.size.y) {

                    connected = true; //check under block
                }

                if (obj.position.x >= otherObj.position.x && obj.position.x <= otherObj.position.x + otherObj.size.x &&
                    obj.position.y + 3 / 2.0f * unit >= otherObj.position.y && obj.position.y + 3 / 2.0f * unit <= otherObj.position.y + otherObj.size.y) {

                    connected = true; //check over block
                }

                //CHECK SPECIAL BLOCK restrictions:
                //          -- tun restrictions
                std::cout << "               with " << otherObj.name << " at (" << otherObj.position.x << ", " << otherObj.position.y << ")\n";
                if (obj.name == "tunGrey" &&
                    obj.position.x == otherObj.position.x && obj.position.y <= otherObj.position.y) {
                    return false;
                }

                //          -- motor restrictions
                if (obj.name == "motorOrange" &&
                    obj.position.x == otherObj.position.x && obj.position.y >= otherObj.position.y) {
                    return false;
                }

                //          -- bumper restrictions
                if (obj.position.x - unit <= otherObj.position.x && obj.position.x + 2 * unit >= otherObj.position.x &&
                    obj.position.y <= otherObj.position.y && obj.position.y + 2 * unit >= otherObj.position.y && 
                    obj.name == "bumperGrey") {
                    return false;
                }
            }
        }

        if (connected == false) {
            return false;
        }

    }
    if (!hasBlock) {
        return false;
    }
    //init the ship position
    spaceshipPositionX = startBlueX + 5 * unit;
    spaceshipPositionY = startBlueY;
    for (auto& obj : dragableTempObjects) {
        obj.offset.x = (obj.position.x - firstObj.position.x);
        obj.offset.y = (obj.position.y - firstObj.position.y);
    }
    return true;
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // TODO(student): Move the logic window with W, A, S, D (up, left, down, right)
    if (window->KeyHold(GLFW_KEY_W)) {
        logicSpace.y += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        logicSpace.y -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        logicSpace.x -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        logicSpace.x += deltaTime;
    }

    // TODO(student): Zoom in and zoom out logic window with Z and X
    if (window->KeyHold(GLFW_KEY_Z)) {
        logicSpace.height -= deltaTime;
        logicSpace.width -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_X)) {
        logicSpace.height += deltaTime;
        logicSpace.width += deltaTime;
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    if (chickenInvaders) {

        if (key == GLFW_KEY_SPACE) {
            for (i = 0; i < dragableTempObjects.size(); i++) {
                auto& obj = dragableTempObjects[i];
                if (obj.name == "tunGrey") {
                    Projectiles newobj;
                    newobj.name = "projectileGreen";
                    newobj.size = glm::vec2(unit / 2.0f, unit / 2.0f);
                    newobj.position = obj.position + glm::vec2(0, obj.size.y);
                    newobj.mesh = meshes["projectileGreen"];
                    projectiles.push_back(newobj);
                }
            }
        }

    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (!chickenInvaders) {
        if (isDragging && selectedObject != -1) {
            glm::ivec2 resolution = window->GetResolution();
            float logicX = logicSpace.x + (float)mouseX / resolution.x * logicSpace.width;
            float logicY = logicSpace.y + (float)(resolution.y - mouseY) / resolution.y * logicSpace.height;

            glm::vec2 mouse(logicX, logicY);
            dragableTempObjects[selectedObject].position = mouse - dragOffset;
        }
    }
    else if (chickenInvaders) {
        if (isDragging && selectedObject != -1) {
            glm::ivec2 resolution = window->GetResolution();
            float logicX = logicSpace.x + (float)mouseX / resolution.x * logicSpace.width;
            float logicY = logicSpace.y + (float)(resolution.y - mouseY) / resolution.y * logicSpace.height;

            glm::vec2 mouse(logicX, logicY);
            firstObj.position = mouse - dragOffset; //only need to drag the first obj since the others are drawn with its coords
        }
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Find the position of the mouse in logic space
    glm::ivec2 resolution = window->GetResolution();
    float logicX = logicSpace.x + (float)mouseX / resolution.x * logicSpace.width;
    float logicY = logicSpace.y + (float)(resolution.y - mouseY) / resolution.y * logicSpace.height;
    glm::vec2 mouse(logicX, logicY);

    // Click LEFT MOUSE to move a dragable mesh
    if (button == 1) {
        typeObj = ObjectType::Nothing;
        for (i = 0; i < dragableObjects.size(); i++) {
            auto& obj = dragableObjects[i];
            if (mouse.x >= obj.position.x && mouse.x <= obj.position.x + obj.size.x &&
                mouse.y >= obj.position.y && mouse.y <= obj.position.y + obj.size.y) {

                //making copy of object
                DragableTempObject newobj;
                newobj.name = obj.name;
                newobj.size = obj.size;
                newobj.position = obj.position;
                newobj.mesh = meshes[obj.name];
                dragableTempObjects.push_back(newobj);

                isDragging = true;
                shouldLoseLife = true;
                typeObj = ObjectType::Original;
                selectedObject = dragableTempObjects.size() - 1;
                dragOffset = mouse - newobj.position;
                break;
            }
        }
        // temp dragable objects don't need to be copied so we dont make one
        //typeObj because otherwise the compiler thinks we clicked on the newly made temp obj
        if (typeObj == ObjectType::Nothing) {
            for (i = 0; i < dragableTempObjects.size(); i++) {
                auto& obj = dragableTempObjects[i];
                if (mouse.x >= obj.position.x && mouse.x <= obj.position.x + obj.size.x &&
                    mouse.y >= obj.position.y && mouse.y <= obj.position.y + obj.size.y) {

                    isDragging = true;
                    shouldLoseLife = false;
                    typeObj = ObjectType::Temporary;
                    selectedObject = i;
                    dragOffset = mouse - obj.position;
                    break;
                }
            }
        }

        // Check the start button
        if (typeObj == ObjectType::Nothing && !chickenInvaders) {

            for (i = 0; i < startButtonObjects.size(); i++) {
                auto& obj = startButtonObjects[i];
                if (mouse.x >= obj.position.x && mouse.x <= obj.position.x + unit &&
                    mouse.y >= obj.position.y && mouse.y <= obj.position.y + unit &&
                    obj.name == "startButtonGreen" && blocksAvailable >= 0) {

                    chickenInvaders = IsShipValid();
                    break;
                }
            }
        }
    }

    // click RIGHT MOUSE to delete a dragable temp mesh
    if (button == 2 && !chickenInvaders) {
        for (i = 0; i < dragableTempObjects.size(); i++) {
            auto& obj = dragableTempObjects[i];
            if (mouse.x >= obj.position.x && mouse.x <= obj.position.x + obj.size.x &&
                mouse.y >= obj.position.y && mouse.y <= obj.position.y + obj.size.y) {
                dragableTempObjects.erase(dragableTempObjects.begin() + i);
                blocksAvailable++;
                break;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == 1 && isDragging) {
        glm::ivec2 resolution = window->GetResolution();
        float logicX = logicSpace.x + (float)mouseX / resolution.x * logicSpace.width;
        float logicY = logicSpace.y + (float)(resolution.y - mouseY) / resolution.y * logicSpace.height;

        glm::vec2 mouse(logicX, logicY);

        bool disolve = true;
        for (i = 0; i < nonDragableObjects.size(); i++) {
            auto& obj = nonDragableObjects[i];
            if (mouse.x >= obj.position.x -0.1f && mouse.x <= obj.position.x + unit -0.1f &&
                mouse.y >= obj.position.y -0.1f && mouse.y <= obj.position.y + +unit - 0.1f &&
                obj.name == "squareBlue") {

                disolve = false;
                selectedPosition = i;
            }
        }

        if (disolve && !chickenInvaders) {
            //delete the mesh dragged outside the spaceship building area
            dragableTempObjects.erase(dragableTempObjects.begin() + selectedObject);
            if (typeObj == ObjectType::Temporary) {
                blocksAvailable++;    //if we drag a temp obj outside the building area it disolves and restores a life
            }
        }
        else if (!chickenInvaders){
            dragableTempObjects[selectedObject].position = nonDragableObjects[selectedPosition].position - glm::vec2(0.1f, 0.1f);
            if (shouldLoseLife) {
                blocksAvailable--;
            }
        }
        typeObj == ObjectType::Nothing;
        isDragging = false;
        selectedObject = -1;
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
