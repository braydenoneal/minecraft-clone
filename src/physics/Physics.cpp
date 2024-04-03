#include "Physics.hpp"


Physics::Physics(Input &input_reference, WorldState &world_state_reference)
        : input(input_reference), world_state(world_state_reference) {}

void Physics::updateLoop() {
    while (true) {
        world_state.camera_position = world_state.previous_camera_position;
        previous_time_factor = 0;
        moving = false;

        for (std::pair<const int, int> key: input.keys) {
            if (key.second) {
                switch (key.first) {
                    case GLFW_KEY_W:
                        moving = true;
                        last_update = steady_clock::now();
                        world_state.previous_camera_position = world_state.camera_position;
                        break;
                    case GLFW_KEY_A:
                        world_state.camera_position = Math::translate_in_direction_by_amount(
                                world_state.camera_position, world_state.camera_angle.y,
                                glm::vec3(-world_state.camera_speed, 0.0f, 0.0f));
                        break;
                    case GLFW_KEY_S:
                        world_state.camera_position = Math::translate_in_direction_by_amount(
                                world_state.camera_position, world_state.camera_angle.y,
                                glm::vec3(0.0f, 0.0f, world_state.camera_speed));
                        break;
                    case GLFW_KEY_D:
                        world_state.camera_position = Math::translate_in_direction_by_amount(
                                world_state.camera_position, world_state.camera_angle.y,
                                glm::vec3(world_state.camera_speed, 0.0f, 0.0f));
                        break;
                    case GLFW_KEY_SPACE:
                        world_state.camera_position.y += world_state.camera_speed;
                        break;
                    case GLFW_KEY_LEFT_SHIFT:
                        world_state.camera_position.y -= world_state.camera_speed;
                        break;
                    default:
                        break;
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::microseconds(update_frequency_microseconds));
    }
}

glm::vec3 Physics::getIntermediatePosition() {
    auto now_time = steady_clock::now();

    auto difference_microseconds = duration_cast<microseconds>(now_time - last_update).count();

    float time_factor = (float) difference_microseconds / (float) update_frequency_microseconds;

    if (moving) {
        world_state.previous_camera_position = Math::translate_in_direction_by_amount(
                world_state.previous_camera_position, world_state.camera_angle.y,
                glm::vec3(0.0f, 0.0f, -world_state.camera_speed * (time_factor - previous_time_factor)));
    }

    previous_time_factor = time_factor;

    return world_state.previous_camera_position;
}

/*   w
 *   p1                p2                p3                p4                p5
 *
 *      f1  f2       f3    f4                                   f5             f6
 */

/*
 * p1: set moving, set position and direction
 * f1: move factor f1 - p1 in direction of p1
 * f2: move factor f2 - f1 in direction of f1
 * f3: move factor f3 - f2 in direction of f2
 * p2: move factor p2 - f3 in direction of f3 (if previously moving)
 *     set moving, set position and direction
 * f4: move factor f4 - p2 in direction of p2
 * p3: move factor p3 - f4 in direction of f4 (if previously moving)
 *     set moving, set position and direction
 * p4: move factor p4 - p3 in direction of p3 (if previously moving)
 *     set moving, set position and direction
 * f5: move factor f5 - p4 in direction of p4
 * p5: move factor p5 - f5 in direction of f5 (if previously moving)
 *     set moving, set position and direction
 * f6: move factor f6 - p5 in direction of p5
 */
