#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Math {
    glm::vec3 translate_in_direction_by_amount(glm::vec3 position, float angle, glm::vec3 amount);

    glm::vec3 translate_in_angle_by_amount(glm::vec3 position, glm::vec3 angle, glm::vec3 amount);
}
