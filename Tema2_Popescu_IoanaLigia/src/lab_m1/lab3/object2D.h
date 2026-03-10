#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateStartButton(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateSemicircle(const std::string& name, glm::vec3 center, float rx, float ry, int segments, glm::vec3 color, bool fill = false);
    Mesh* CreateMotor(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 colorSquare, glm::vec3 colorFire, bool fill = false);
    Mesh* CreateTun(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 colorRectangle, glm::vec3 colorSemicircle, glm::vec3 colorBarrel, bool fill = false);
    Mesh* CreateBumper(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 colorSquare, glm::vec3 colorSemicircle, bool fill = false);
    Mesh* CreateChickenInvader(const std::string& name, glm::vec3 centerCircle, float r, glm::vec3 colorBody, glm::vec3 colorHead, glm::vec3 colorWings, glm::vec3 colorFeet, bool fill = false);
}
