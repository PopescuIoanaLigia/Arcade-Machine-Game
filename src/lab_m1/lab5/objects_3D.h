#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objects_3D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateCuboid(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, float height, glm::vec3 color);
}
