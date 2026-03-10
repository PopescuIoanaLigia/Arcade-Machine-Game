#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


// Simple Square
Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

// Start Button
Mesh* object2D::CreateStartButton(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, length/2.0f, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* start = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        start->SetDrawMode(GL_LINE_LOOP);
        indices.push_back(3);
        indices.push_back(4);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(4);
    }

    start->InitFromData(vertices, indices);
    return start;
}

// Simple  Rectangle
Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

// Elipse Semicircle
Mesh* object2D::CreateSemicircle(
    const std::string& name,
    glm::vec3 center,
    float rx, //horizontal radix
    float ry, //vertical radix
    int segments,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= segments; i++) {
        float angle = glm::pi<float>() * i / segments;    // from 0->pi for semicircle
        float x = center.x + rx * cos(angle);  // x=cx+rx⋅cos(θ)y=cy+ry⋅sin(θ)
        float y = center.y + ry * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    Mesh* circle = new Mesh(name);

    if (!fill) {
        for (int i = 1; i <= segments; i++) {
            indices.push_back(i);
        }
        indices.push_back(1);
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        for (int i = 1; i <= segments; i++) {
            indices.push_back(0);       // center
            indices.push_back(i);       // current vertex
            indices.push_back(i + 1);   // next vertex
        }

    }

    circle->InitFromData(vertices, indices);
    return circle;
}

// Motor
Mesh* object2D::CreateMotor(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 colorSquare,
    glm::vec3 colorFire,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // Square section

    std::vector<VertexFormat> verticesSquare =
    {
        VertexFormat(corner, colorSquare),
        VertexFormat(corner + glm::vec3(length, 0, 0), colorSquare),
        VertexFormat(corner + glm::vec3(length, length, 0), colorSquare),
        VertexFormat(corner + glm::vec3(0, length, 0), colorSquare)
    };

    std::vector<unsigned int> indicesSquare = { 0, 1, 2, 3 };

    if (fill) {
        // Draw 2 triangles. Add the remaining 2 indices
        indicesSquare.push_back(0);
        indicesSquare.push_back(2);
    }

    // adding the indices and vertices for the square in the global mesh indx and vert
    vertices.insert(vertices.end(), verticesSquare.begin(), verticesSquare.end());
    for (auto idx : indicesSquare)
        indices.push_back(idx);

    // FIRE SECTION

    glm::vec3 cornerFire = corner + glm::vec3(0.1f, -0.01f, 0);
    float fireLength = length - 0.2f;

    float xOffset = length / 6.0f;
    float yOffset = length / 4.0f;

    std::vector<VertexFormat> verticesFire =
    {
        VertexFormat(cornerFire, colorFire),
        VertexFormat(cornerFire + glm::vec3(fireLength, 0, 0), colorFire),
        VertexFormat(cornerFire + glm::vec3(fireLength, -fireLength, 0), colorFire),
        VertexFormat(cornerFire + glm::vec3(0, -fireLength, 0), colorFire),
        VertexFormat(cornerFire + glm::vec3(0, -fireLength -yOffset, 0), colorFire), //4
        VertexFormat(cornerFire + glm::vec3(xOffset, -fireLength, 0), colorFire), // 5
        VertexFormat(cornerFire + glm::vec3(xOffset * 2, -fireLength - yOffset, 0), colorFire), //6
        VertexFormat(cornerFire + glm::vec3(xOffset * 3, -fireLength, 0), colorFire), //7
        VertexFormat(cornerFire + glm::vec3(xOffset * 4, -fireLength - yOffset, 0), colorFire), //8
        VertexFormat(cornerFire + glm::vec3(xOffset * 5, -fireLength, 0), colorFire), //9
        VertexFormat(cornerFire + glm::vec3(fireLength, -fireLength - yOffset, 0), colorFire) //10
    };

    std::vector<unsigned int> indicesFire = { 0, 1, 2 };

    if (!fill) {
        indicesFire.push_back(10);
        indicesFire.push_back(9);
        indicesFire.push_back(8);
        indicesFire.push_back(7);
        indicesFire.push_back(6);
        indicesFire.push_back(5);
        indicesFire.push_back(4);
        indicesFire.push_back(3);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indicesFire.push_back(3);
        indicesFire.push_back(0);
        indicesFire.push_back(2);

        indicesFire.push_back(3);
        indicesFire.push_back(4);
        indicesFire.push_back(5);

        indicesFire.push_back(6);
        indicesFire.push_back(5);
        indicesFire.push_back(7);

        indicesFire.push_back(8);
        indicesFire.push_back(7);
        indicesFire.push_back(9);

        indicesFire.push_back(2);
        indicesFire.push_back(9);
        indicesFire.push_back(10);
    }

    // adding the idx and vert in the globar mesh
    int startFire = vertices.size(); // offset for fire vertices
    vertices.insert(vertices.end(), verticesFire.begin(), verticesFire.end());
    for (auto idx : indicesFire)
        indices.push_back(startFire + idx);

    Mesh* motor = new Mesh(name);
    if (!fill) {
        motor->SetDrawMode(GL_LINE_LOOP);
    }
    motor->InitFromData(vertices, indices);
    return motor;
}

Mesh* object2D::CreateTun(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 colorRectangle,
    glm::vec3 colorSemicircle,
    glm::vec3 colorBarrel,
    bool fill)
{
    // Rectangle init
    glm::vec3 cornerRectangle = leftBottomCorner;
    float heightRectangle = height / 5.0f;
    float lengthRectangle = length;

    // Barrel init
    glm::vec3 centerSemicircle = cornerRectangle + glm::vec3( lengthRectangle / 2.0f, heightRectangle + 0.01f, 0);
    float heightSemicircle = heightRectangle;
    float lengthSemicircle = lengthRectangle;

    // Semicircle init
    glm::vec3 cornerBarrel = cornerRectangle + glm::vec3( 0.15f, heightRectangle + 0.01f, -0.001);
    float heightBarrel = heightRectangle * 4;
    float lengthBarrel = lengthRectangle - 0.3f;

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // Rectangle section

    std::vector<VertexFormat> verticesRectangle =
    {
        VertexFormat(cornerRectangle, colorRectangle),
        VertexFormat(cornerRectangle + glm::vec3(lengthRectangle, 0, 0), colorRectangle),
        VertexFormat(cornerRectangle + glm::vec3(lengthRectangle, heightRectangle, 0), colorRectangle),
        VertexFormat(cornerRectangle + glm::vec3(0, heightRectangle, 0), colorRectangle)
    };

    std::vector<unsigned int> indicesRectangle = { 0, 1, 2, 3 };

    if (fill) {
        // Draw 2 triangles. Add the remaining 2 indices
        indicesRectangle.push_back(0);
        indicesRectangle.push_back(2);
    }

    // adding the indices and vertices for the rectangle in the global mesh indx and vert
    vertices.insert(vertices.end(), verticesRectangle.begin(), verticesRectangle.end());
    for (auto idx : indicesRectangle)
        indices.push_back(idx);

    // SEMICIRCLE SECTION

    std::vector<VertexFormat> verticesSemicircle;
    std::vector<unsigned int> indicesSemicircle;

    int segments = 50;
    float rx = lengthSemicircle / 2.0f;
    float ry = heightSemicircle;

    for (int i = 0; i <= segments; i++) {
        float angle = glm::pi<float>() * i / segments;    // from 0->pi for semicircle
        float x = centerSemicircle.x + rx * cos(angle);  // x=cx+rx⋅cos(θ)y=cy+ry⋅sin(θ)
        float y = centerSemicircle.y + ry * sin(angle);
        verticesSemicircle.push_back(VertexFormat(glm::vec3(x, y, 0), colorSemicircle));
    }

    if (!fill) {
        for (int i = 1; i <= segments; i++) {
            indicesSemicircle.push_back(i);
        }
        indicesSemicircle.push_back(1);
    }
    else {
        for (int i = 1; i <= segments; i++) {
            indicesSemicircle.push_back(0);       // center
            indicesSemicircle.push_back(i);       // current vertex
            indicesSemicircle.push_back(i + 1);   // next vertex
        }

    }

    // adding the idx and vert in the global mesh
    int startSemicircle = vertices.size(); // offset for semicircle vertices
    vertices.insert(vertices.end(), verticesSemicircle.begin(), verticesSemicircle.end());
    for (auto idx : indicesSemicircle)
        indices.push_back(startSemicircle + idx);

    // BARREL SECTION

    std::vector<VertexFormat> verticesBarrel =
    {
        VertexFormat(cornerBarrel, colorBarrel),
        VertexFormat(cornerBarrel + glm::vec3(lengthBarrel, 0, 0), colorBarrel),
        VertexFormat(cornerBarrel + glm::vec3(lengthBarrel, heightBarrel, 0), colorBarrel),
        VertexFormat(cornerBarrel + glm::vec3(0, heightBarrel, 0), colorBarrel)
    };

    std::vector<unsigned int> indicesBarrel = { 0, 1, 2, 3 };

    if (fill) {
        // Draw 2 triangles. Add the remaining 2 indices
        indicesBarrel.push_back(0);
        indicesBarrel.push_back(2);
    }

    // adding the idx and vert in the global mesh
    int startBarrel = vertices.size(); // offset for barrel vertices
    vertices.insert(vertices.end(), verticesBarrel.begin(), verticesBarrel.end());
    for (auto idx : indicesBarrel)
        indices.push_back(startBarrel + idx);

    // creating the mesh
    Mesh* tun = new Mesh(name);
    if (!fill) {
        tun->SetDrawMode(GL_LINE_LOOP);
    }
    tun->InitFromData(vertices, indices);
    return tun;
}

// Bumper
Mesh* object2D::CreateBumper(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 colorSquare,
    glm::vec3 colorSemicircle,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    // Square init
    glm::vec3 cornerSquare = corner + glm::vec3(0, 0, -0.01f);
    float lengthSquare = length / 3.0f;

    // Semicircle init
    glm::vec3 centerSemicircle = corner + glm::vec3(length / 6.0f, height + 0.01f, 0);
    float lengthSemicircle = length;
    float heightSemicircle = height;

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // SQUARE SECTION

    std::vector<VertexFormat> verticesSquare =
    {
        VertexFormat(cornerSquare, colorSquare),
        VertexFormat(cornerSquare + glm::vec3(lengthSquare, 0, 0), colorSquare),
        VertexFormat(cornerSquare + glm::vec3(lengthSquare, lengthSquare, 0), colorSquare),
        VertexFormat(cornerSquare + glm::vec3(0, lengthSquare, 0), colorSquare)
    };

    std::vector<unsigned int> indicesSquare = { 0, 1, 2, 3 };

    if (fill) {
        // Draw 2 triangles. Add the remaining 2 indices
        indicesSquare.push_back(0);
        indicesSquare.push_back(2);
    }

    // adding the indices and vertices for the square in the global mesh indx and vert
    vertices.insert(vertices.end(), verticesSquare.begin(), verticesSquare.end());
    for (auto idx : indicesSquare)
        indices.push_back(idx);

    // SEMICIRCLE SECTION

    std::vector<VertexFormat> verticesSemicircle;
    std::vector<unsigned int> indicesSemicircle;

    int segments = 50;
    float rx = lengthSemicircle / 2.0f;
    float ry = heightSemicircle;

    verticesSemicircle.push_back(VertexFormat(centerSemicircle, colorSemicircle));
    for (int i = 0; i <= segments; i++) {
        float angle = glm::pi<float>() * i / segments;    // from 0->pi for semicircle
        float x = centerSemicircle.x + rx * cos(angle);  // x=cx+rx⋅cos(θ)y=cy+ry⋅sin(θ)
        float y = centerSemicircle.y + ry * sin(angle);
        verticesSemicircle.push_back(VertexFormat(glm::vec3(x, y, 0), colorSemicircle));
    }

    if (!fill) {
        for (int i = 0; i <= segments; i++) {
            indicesSemicircle.push_back(i);
        }
        indicesSemicircle.push_back(1);
    }
    else {
        for (int i = 0; i <= segments; i++) {
            indicesSemicircle.push_back(0);       // center
            indicesSemicircle.push_back(i);       // current vertex
            indicesSemicircle.push_back(i + 1);   // next vertex
        }

    }

    // adding the idx and vert in the global mesh
    int startSemicircle = vertices.size(); // offset for semicircle vertices
    vertices.insert(vertices.end(), verticesSemicircle.begin(), verticesSemicircle.end());
    for (auto idx : indicesSemicircle)
        indices.push_back(startSemicircle + idx);

    Mesh* bumper = new Mesh(name);
    if (!fill) {
        bumper->SetDrawMode(GL_LINE_LOOP);
    }
    bumper->InitFromData(vertices, indices);
    return bumper;
}

Mesh* object2D::CreateChickenInvader(
    const std::string& name,
    glm::vec3 centerCircle,
    float r,
    glm::vec3 colorBody,
    glm::vec3 colorHead,
    glm::vec3 colorWings,
    glm::vec3 colorFeet,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    int indexOffset = 0;
    float u = r / 3.0f; // we'll make the body out of 3 * u = r;

    // BODY - SQUARE
    glm::vec3 bodyCorner = centerCircle - glm::vec3(u / 2.0f, u / 2.0f, 0); // centerCircle is in the center of the square
    std::vector<VertexFormat> vBody = {
        VertexFormat(bodyCorner, colorBody),
        VertexFormat(bodyCorner + glm::vec3(u, 0, 0), colorBody),
        VertexFormat(bodyCorner + glm::vec3(u, u, 0), colorBody),
        VertexFormat(bodyCorner + glm::vec3(0, u, 0), colorBody)
    };
    vertices.insert(vertices.end(), vBody.begin(), vBody.end());

    std::vector<unsigned int> iBody = { 0, 1, 2, 3 };
    if (fill) {
        iBody.push_back(0);
        iBody.push_back(2);
    }

    for (auto i : iBody) {
        indices.push_back(i + indexOffset);
    }
    indexOffset += vBody.size();

    // 2. HEAD - CIRCLE
    float headR = u / 2.0f;
    glm::vec3 headCenter = centerCircle + glm::vec3(0, u, 0);

    int segments = 50;
    std::vector<VertexFormat> vHead;
    vHead.push_back(VertexFormat(headCenter, colorHead));

    for (int i = 0; i <= segments; i++) {
        float angle = 2 * glm::pi<float>() * i / segments;
        float x = headCenter.x + headR * cos(angle);
        float y = headCenter.y + headR * sin(angle);
        vHead.push_back(VertexFormat(glm::vec3(x, y, 0), colorHead));
    }
    vertices.insert(vertices.end(), vHead.begin(), vHead.end());

    if (!fill) {
        for (int i = 0; i <= segments; i++) {
            indices.push_back(indexOffset + i);
        }
        indices.push_back(indexOffset + 1);
    }
    else {
        for (int i = 0; i <= segments; i++) {
            indices.push_back(indexOffset);       // center
            indices.push_back(indexOffset + i);       // current vertex
            indices.push_back(indexOffset + i + 1);   // next vertex
        }

    }
    indexOffset += vHead.size();


    // 3. LEFT WING

    glm::vec3 cornerWing = centerCircle + glm::vec3( - u * 3 / 2.0f, 0, 0);

    std::vector<VertexFormat> vWingLeft = {
        VertexFormat(cornerWing + glm::vec3(0, u * 1/ 5.0f, 0), colorWings),
        VertexFormat(cornerWing + glm::vec3(u * 1 / 5.0f, u * 3 / 2.0f, 0), colorWings),
        VertexFormat(cornerWing + glm::vec3(u, 0, 0), colorWings)
    };

    vertices.insert(vertices.end(), vWingLeft.begin(), vWingLeft.end());

    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 1);
    indices.push_back(indexOffset + 2);
    indexOffset += 3;

    // 3. RIGHT WING
    cornerWing = centerCircle + glm::vec3(u * 3 / 2.0f, 0, 0);

    std::vector<VertexFormat> vWingRight = {
        VertexFormat(cornerWing + glm::vec3(0, u * 1 / 5.0f, 0), colorWings),
        VertexFormat(cornerWing + glm::vec3(-u * 1 / 5.0f, u * 3 / 2.0f, 0), colorWings),
        VertexFormat(cornerWing + glm::vec3(-u, 0, 0), colorWings)
    };

    vertices.insert(vertices.end(), vWingRight.begin(), vWingRight.end());

    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 1);
    indices.push_back(indexOffset + 2);
    indexOffset += 3;

    // 3. FEET
    //       -- left + right rectagles

    //          left
    glm::vec3 footCornerRectangle = centerCircle + glm::vec3(-u * 1 / 2.0f + u * 1/5.0f, -u * 1/2.0f, 0);
    std::vector<VertexFormat> vFootRectangleL = {
        VertexFormat(footCornerRectangle, colorFeet),
        VertexFormat(footCornerRectangle + glm::vec3(u * 1 / 5.0f, 0, 0), colorFeet),
        VertexFormat(footCornerRectangle + glm::vec3(u * 1 / 5.0f, - u / 2.0f, 0), colorFeet),
        VertexFormat(footCornerRectangle + glm::vec3(0, -u / 2.0f, 0), colorFeet)
    };
    vertices.insert(vertices.end(), vFootRectangleL.begin(), vFootRectangleL.end());

    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 1);
    indices.push_back(indexOffset + 2);
    indices.push_back(indexOffset + 3);
    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 2);
    indexOffset += 4;

    //            right
    footCornerRectangle = footCornerRectangle + glm::vec3(u * 2 / 5.0f, 0, 0);
    std::vector<VertexFormat> vFootRectangleR = {
        VertexFormat(footCornerRectangle, colorFeet),
        VertexFormat(footCornerRectangle + glm::vec3(u * 1 / 5.0f, 0, 0), colorFeet),
        VertexFormat(footCornerRectangle + glm::vec3(u * 1 / 5.0f, -u / 2.0f, 0), colorFeet),
        VertexFormat(footCornerRectangle + glm::vec3(0, -u / 2.0f, 0), colorFeet)
    };
    vertices.insert(vertices.end(), vFootRectangleR.begin(), vFootRectangleR.end());

    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 1);
    indices.push_back(indexOffset + 2);
    indices.push_back(indexOffset + 3);
    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 2);
    indexOffset += 4;

    //       -- left + right triangles
    //          left
    glm::vec3 footCornerTriangle = centerCircle + glm::vec3(-u * 1 / 2.0f + u * 2 / 5.0f, -u, 0);
    std::vector<VertexFormat> vFootTriangleL = {
        VertexFormat(footCornerTriangle, colorFeet),
        VertexFormat(footCornerTriangle + glm::vec3(- u * 1/5.0f, - u * 1/4.0f, 0), colorFeet),
        VertexFormat(footCornerTriangle + glm::vec3(- u * 2 / 5.0f, 0, 0), colorFeet)
    };
    vertices.insert(vertices.end(), vFootTriangleL.begin(), vFootTriangleL.end());

    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 1);
    indices.push_back(indexOffset + 2);
    indexOffset += 3;

    //            right
    footCornerTriangle = footCornerTriangle + glm::vec3(u * 1 / 5.0f, 0, 0);
    std::vector<VertexFormat> vFootTriangleR = {
        VertexFormat(footCornerTriangle, colorFeet),
        VertexFormat(footCornerTriangle + glm::vec3(u * 1 / 5.0f, -u * 1 / 4.0f, 0), colorFeet),
        VertexFormat(footCornerTriangle + glm::vec3(u * 2 / 5.0f, 0, 0), colorFeet)
    };
    vertices.insert(vertices.end(), vFootTriangleR.begin(), vFootTriangleR.end());

    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 1);
    indices.push_back(indexOffset + 2);
    indexOffset += 3;

    // 2. EYES
    //      --left
    float eyeR = u / 15.0f;
    glm::vec3 eyeCenter = headCenter + glm::vec3(- u * 1/8.0f, u * 1/4.0f, 0.001f);
    glm::vec3 colorEyes = glm::vec3(0, 0, 0);

    segments = 30;
    std::vector<VertexFormat> vEyes;
    vEyes.push_back(VertexFormat(eyeCenter, colorEyes));

    for (int i = 0; i <= segments; i++) {
        float angle = 2 * glm::pi<float>() * i / segments;
        float x = eyeCenter.x + eyeR * cos(angle);
        float y = eyeCenter.y + eyeR * sin(angle);
        vEyes.push_back(VertexFormat(glm::vec3(x, y, 0), colorEyes));
    }
    vertices.insert(vertices.end(), vEyes.begin(), vEyes.end());

    if (!fill) {
        for (int i = 0; i <= segments; i++) {
            indices.push_back(indexOffset + i);
        }
        indices.push_back(indexOffset + 1);
    }
    else {
        for (int i = 0; i <= segments; i++) {
            indices.push_back(indexOffset);       // center
            indices.push_back(indexOffset + i);       // current vertex
            indices.push_back(indexOffset + i + 1);   // next vertex
        }

    }
    indexOffset += vEyes.size();

    //      --right
    eyeCenter = headCenter + glm::vec3(u * 1 / 8.0f, u * 1 / 4.0f, 0.001f);
    std::vector<VertexFormat> vEyesR;
    vEyesR.push_back(VertexFormat(eyeCenter, colorEyes));

    for (int i = 0; i <= segments; i++) {
        float angle = 2 * glm::pi<float>() * i / segments;
        float x = eyeCenter.x + eyeR * cos(angle);
        float y = eyeCenter.y + eyeR * sin(angle);
        vEyesR.push_back(VertexFormat(glm::vec3(x, y, 0), colorEyes));
    }
    vertices.insert(vertices.end(), vEyesR.begin(), vEyesR.end());

    if (!fill) {
        for (int i = 0; i <= segments; i++) {
            indices.push_back(indexOffset + i);
        }
        indices.push_back(indexOffset + 1);
    }
    else {
        for (int i = 0; i <= segments; i++) {
            indices.push_back(indexOffset);       // center
            indices.push_back(indexOffset + i);       // current vertex
            indices.push_back(indexOffset + i + 1);   // next vertex
        }

    }
    indexOffset += vEyesR.size();

    // BEAK
    glm::vec3 beakCorner = headCenter + glm::vec3(-u * 1 / 5.0f, 0, 0.01f);
    std::vector<VertexFormat> vBeak = {
        VertexFormat(beakCorner, colorFeet),
        VertexFormat(beakCorner + glm::vec3(u * 2 / 4.0f, 0, 0), colorFeet),
        VertexFormat(beakCorner + glm::vec3(u * 1 / 6.0f, u * 1 / 6.0f, 0), colorFeet)
    };
    vertices.insert(vertices.end(), vBeak.begin(), vBeak.end());

    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 1);
    indices.push_back(indexOffset + 2);
    indexOffset += 3;

    // HEAD CREST
    glm::vec3 colorCrest = glm::vec3(1, 0, 0);
    glm::vec3 crestCorner = headCenter + glm::vec3(-u * 1 / 5.0f, u * 1/2.0f, 0.01f);
    std::vector<VertexFormat> vCrest = {
        VertexFormat(crestCorner, colorCrest),
        VertexFormat(crestCorner + glm::vec3(u * 1 / 6.0f, u * 1 / 2.0f, 0), colorCrest),
        VertexFormat(crestCorner + glm::vec3(u * 1 / 6.0f, 0, 0), colorCrest),
        VertexFormat(crestCorner + glm::vec3(u * 1 / 3.0f, u * 1 / 1.5f, 0), colorCrest),
        VertexFormat(crestCorner + glm::vec3(u * 1 / 4.0f, 0, 0), colorCrest),
    };
    vertices.insert(vertices.end(), vCrest.begin(), vCrest.end());

    indices.push_back(indexOffset + 0);
    indices.push_back(indexOffset + 1);
    indices.push_back(indexOffset + 2);
    indices.push_back(indexOffset + 3);
    indices.push_back(indexOffset + 4);
    indices.push_back(indexOffset + 2);
    indexOffset += 5;



    Mesh* chicken = new Mesh(name);
    if (!fill) chicken->SetDrawMode(GL_LINE_LOOP);
    chicken->InitFromData(vertices, indices);

    return chicken;
}
