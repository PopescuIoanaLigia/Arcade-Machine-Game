#include "objects_3D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


// Simple Cuboid
Mesh* objects_3D::CreateCuboid(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length, //lungime
    float width, //latime
    float height, //inaltime
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color),
        VertexFormat(corner + glm::vec3(0, 0, height), color),
        VertexFormat(corner + glm::vec3(length, 0, height), color),
        VertexFormat(corner + glm::vec3(length, width, height), color),
        VertexFormat(corner + glm::vec3(0, width, height), color),
    };

    Mesh* cuboid = new Mesh(name);
    std::vector<unsigned int> indices = { 
    // Bottom face
    0, 1, 2,
    0, 2, 3,

    // Top face
    4, 5, 6,
    4, 6, 7,

    // Front face
    0, 1, 5,
    0, 5, 4,

    // Back face
    3, 2, 6,
    3, 6, 7,

    // Left face
    0, 3, 7,
    0, 7, 4,

    // Right face
    1, 2, 6,
    1, 6, 5
    };

    cuboid->InitFromData(vertices, indices);
    return cuboid;
}