#include "Pig.hpp"

PigPhysics::PigPhysics(ChunkLoader &chunk_loader, Pig &pig) : chunk_loader(chunk_loader), pig(pig) {
    position = getRandomDestination();

    auto x_position = (float) std::round(position.x);
    auto z_position = (float) std::round(position.z);

    float vertical_scale = 15;
    float horizontal_scale = 24;
    float noise_value = glm::perlin(glm::vec2(x_position / horizontal_scale, z_position / horizontal_scale));
    float surface_y = vertical_scale + vertical_scale * noise_value;

    position.y = (float) std::round(surface_y) + 1;
    previous_pig_position = position;
}

glm::vec3 PigPhysics::getRandomDestination() const {
    int x = std::floor(position.x);
    int z = std::floor(position.z);

    return {x + glm::linearRand(-max_travel_distance, max_travel_distance), 0,
            z + glm::linearRand(-max_travel_distance, max_travel_distance)};
}

glm::vec3 PigPhysics::getNextBlockPosition() {
    int x = std::floor(position.x);
    int y = std::floor(position.y);
    int z = std::floor(position.z);

    std::deque<glm::vec3> next_positions = {
        {x - 1, y, z},
        {x, y, z - 1},
        {x + 1, y, z},
        {x, y + 1, z},
        {x, y, z + 1},
    };

    std::sort(next_positions.begin(), next_positions.end(), [this](const glm::vec3 &a, glm::vec3 &b) {
        return glm::distance({a.x, 0, a.z}, this->current_destination) < glm::distance({b.x, 0, b.z}, this->current_destination);
    });

    if (!jumping) {
        next_positions.emplace_front(x, y - 1, z);
    }

    for (const auto next_position: next_positions) {
        if (chunk_loader.getBlockAtPosition(next_position).id == 0) {
            jumping = next_position.y > (float) y;
            return next_position;
        }
    }

    return position;
}

void PigPhysics::stepAnimation(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle) {
    if (pig_rotation > 1) {
        pig_rotation_direction = -1;
    } else if (pig_rotation < -1) {
        pig_rotation_direction = 1;
    }
    pig_rotation += 0.05f * pig_rotation_direction;
    pig_counter++;
    if (pig_counter > anim_time) {
        anim_time = glm::linearRand(90, 110);
        pos_int = {0, 0, 0};
        rot_int = {0, 0, 0};
        pig_counter = 0;
        rot_counter = 0;
        previous_pig_position = position;
        position = getNextBlockPosition();
        if (previous_pig_position.y == position.y) {
            previous_pig_rotation = rotation;
            rotation = {0, glm::radians(90.0f) +
                                       glm::atan(position.x - previous_pig_position.x,
                                                 -(position.z - previous_pig_position.z)), 0};
        } else {
            previous_pig_rotation = rotation;
        }
        if (position.x == current_destination.x && position.z == current_destination.z) {
            current_destination = getRandomDestination();
        }
//        current_destination = camera_position;
    }
    pos_int += (position - previous_pig_position) / (float) anim_time;
    if (rot_counter < 40) {
        glm::vec3 rot1 = rotation - previous_pig_rotation;
        glm::vec3 rot2 = {0, -(glm::radians(360.0f) - rot1.y), 0};
        if (rot1.y < 0) {
            rot2 = {0, glm::radians(360.0f) + rot1.y, 0};
        }
        if (abs(rot1.y) < abs(rot2.y)) {
            rot_int += rot1 / 40.0f;
        } else {
            rot_int += rot2 / 40.0f;
        }
    }
    rot_counter++;
    glm::vec3 new_pos = previous_pig_position + pos_int;
    pig.shader.bind();
    pig.vertex_array.bind();
    pig.texture.bind();
    pig.setLegBackRightRotation(0, 0, -pig_rotation);
    pig.setLegBackLeftRotation(0, 0, pig_rotation);
    pig.setLegFrontRightRotation(0, 0, pig_rotation);
    pig.setLegFrontLeftRotation(0, 0, -pig_rotation);
    pig.setUniforms(aspect_ratio, camera_position, camera_angle,
                    {new_pos.x + 0.5, new_pos.y, new_pos.z + 0.5}, previous_pig_rotation + rot_int);
    pig.draw();
    Texture::unbind();
    VertexArray::unbind();
    Shader::unbind();
}
