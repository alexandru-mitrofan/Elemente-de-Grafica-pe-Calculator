#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    Mesh* CreateS(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateHead(const std::string &name, glm::vec3 center, float radiusX, float radiusY, glm::vec3 color);
    Mesh* CreateTriangle(const std::string &name, glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 color);
    Mesh* CreateRectangle(const std::string &name, glm::vec3 center, float height, float width, glm::vec3 color, bool fill);
}
