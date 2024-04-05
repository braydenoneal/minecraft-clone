#include "Physics.hpp"

Physics::Physics(Input &input_reference, WorldState &world_state_reference, Collision &collision_reference)
        : input(input_reference), world_state(world_state_reference), collision(collision_reference) {}

void Physics::processMovement() {
    auto now_time = steady_clock::now();
    auto difference_microseconds = duration_cast<microseconds>(now_time - last_update).count();
    float time_factor = (float) difference_microseconds / (float) update_frequency_microseconds;

    glm::vec3 previous_camera_position = world_state.camera_position;

    for (std::pair<const int, int> key: input.keys) {
        if (key.second) {
            switch (key.first) {
                case GLFW_KEY_W:
                    world_state.camera_position = Math::translate_in_direction_by_amount(
                            world_state.camera_position, world_state.camera_angle.y,
                            glm::vec3(0.0f, 0.0f, -world_state.camera_speed * (time_factor - previous_time_factor)));
                    break;
                case GLFW_KEY_A:
                    world_state.camera_position = Math::translate_in_direction_by_amount(
                            world_state.camera_position, world_state.camera_angle.y,
                            glm::vec3(-world_state.camera_speed * (time_factor - previous_time_factor), 0.0f, 0.0f));
                    break;
                case GLFW_KEY_S:
                    world_state.camera_position = Math::translate_in_direction_by_amount(
                            world_state.camera_position, world_state.camera_angle.y,
                            glm::vec3(0.0f, 0.0f, world_state.camera_speed * (time_factor - previous_time_factor)));
                    break;
                case GLFW_KEY_D:
                    world_state.camera_position = Math::translate_in_direction_by_amount(
                            world_state.camera_position, world_state.camera_angle.y,
                            glm::vec3(world_state.camera_speed * (time_factor - previous_time_factor), 0.0f, 0.0f));
                    break;
                case GLFW_KEY_SPACE:
                    world_state.camera_position.y += world_state.camera_speed * (time_factor - previous_time_factor);
                    break;
                case GLFW_KEY_LEFT_SHIFT:
                    world_state.camera_position.y -= world_state.camera_speed * (time_factor - previous_time_factor);
                    break;
                default:
                    break;
            }
        }
    }

    if (world_state.camera_position != previous_camera_position && !collision.canMoveTo(world_state.camera_position)) {
        world_state.camera_position = previous_camera_position;
    }

    previous_time_factor = time_factor;
}

void Physics::updateLoop() {
    while (true) {
        processMovement();

        last_update = steady_clock::now();
        previous_time_factor = 0;

        std::this_thread::sleep_for(std::chrono::microseconds(update_frequency_microseconds));
    }
}
