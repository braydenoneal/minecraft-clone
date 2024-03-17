#pragma once

namespace math {
    glm::vec3 translate_in_direction_by_amount(glm::vec3 position, float angle, glm::vec3 amount) {
        glm::mat4 rotate_mat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 rotated_amount = rotate_mat * glm::vec4(amount, 1.0f);
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), rotated_amount);
        return translation * glm::vec4(position, 1.0f);
    }

    glm::vec3 translate_in_angle_by_amount(glm::vec3 position, glm::vec3 angle, glm::vec3 amount) {
        auto rotate = glm::mat4(1.0f);

        rotate = glm::rotate(rotate, angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotate = glm::rotate(rotate, angle.x, glm::vec3(1.0f, 0.0f, 0.0f));

        glm::vec3 rotated_amount = rotate * glm::vec4(amount, 1.0f);
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), rotated_amount);

        return translation * glm::vec4(position, 1.0f);
    }
}
