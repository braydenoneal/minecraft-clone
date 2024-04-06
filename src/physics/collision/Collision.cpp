#include "Collision.hpp"

Collision::Collision(ChunkLoader &chunk_loader_reference) : chunk_loader(chunk_loader_reference) {}

Block Collision::getBlockAtPosition(glm::vec3 position) {
    int chunk_x = std::floor(position.x / (float) CHUNK_SIZE);
    int chunk_y = std::floor(position.y / (float) CHUNK_SIZE);
    int chunk_z = std::floor(position.z / (float) CHUNK_SIZE);

    for (const auto &chunk: chunk_loader.chunks) {
        if (chunk_x == chunk.position.x && chunk_y == chunk.position.y && chunk_z == chunk.position.z) {
            int x = (int) std::floor(position.x) % CHUNK_SIZE;
            int y = (int) std::floor(position.y) % CHUNK_SIZE;
            int z = (int) std::floor(position.z) % CHUNK_SIZE;

            if (x < 0) {
                x += CHUNK_SIZE;
            }
            if (y < 0) {
                y += CHUNK_SIZE;
            }
            if (z < 0) {
                z += CHUNK_SIZE;
            }

            return chunk.get(x, y, z);
        }
    }

    return {0};
}

glm::vec3 Collision::canMoveTo(glm::vec3 start_position, glm::vec3 end_position) {
    glm::vec3 player_min = {end_position.x - 0.3f, end_position.y - 1.6f, end_position.z - 0.3f};
    glm::vec3 player_max = {end_position.x + 0.3f, end_position.y + 0.2f, end_position.z + 0.3f};

    std::vector<glm::vec3> intersections{};

    for (int x = (int) std::floor(player_min.x); x < (int) std::ceil(player_max.x); x++) {
        for (int y = (int) std::floor(player_min.y); y < (int) std::ceil(player_max.y); y++) {
            for (int z = (int) std::floor(player_min.z); z < (int) std::ceil(player_max.z); z++) {
                if (getBlockAtPosition(glm::vec3((float) x, (float) y, (float) z)).id != 0) {
                    glm::vec3 block_min = {x, y, z};
                    glm::vec3 block_max = {x + 1, y + 1, z + 1};

                    glm::vec3 intersection_point = moveTo(start_position, end_position, {x, y, z});

                    if (intersection_point != end_position) {
                        intersections.push_back(intersection_point);
                    }
                }
            }
        }
    }

    glm::vec3 position = end_position;

    for (auto intersection: intersections) {
        if (glm::length(intersection - start_position) < glm::length(position - start_position)) {
            position = intersection;
        }
    }

    return position;
}

bool Collision::intersect(glm::vec3 plane_point, glm::vec3 plane_normal, glm::vec3 ray_point, glm::vec3 ray_direction,
                          glm::vec3 &intersection_point) {
    float d = glm::dot(plane_point, -plane_normal);
    float b = glm::dot(ray_direction, plane_normal);

    if (b == 0) {
        return false;
    }

    float t0 = -(d + glm::dot(ray_point, plane_normal));

    if (b > 0 || t0 > 0) {
        return false;
    }

    float t = t0 / b;
    intersection_point = ray_point + t * ray_direction;

    return true;
}

glm::vec3 Collision::moveTo(glm::vec3 start_position, glm::vec3 end_position, glm::vec3 cube_position) {
    glm::vec3 ray_point = start_position;
    glm::vec3 ray_direction = glm::normalize(end_position - start_position);
    glm::vec3 intersection_point = end_position;

    glm::vec3 plane_point = cube_position + glm::vec3(-0.3, 0.5, 0.5);
    glm::vec3 plane_normal = {-1, 0, 0};
    bool intersects = intersect(plane_point, plane_normal, ray_point, ray_direction, intersection_point);
    if (intersects) {
        if (intersection_point.y < plane_point.y - 0.5 - 0.2 || intersection_point.y > plane_point.y + 0.5 + 1.6 ||
            intersection_point.z < plane_point.z - 0.5 - 0.3 || intersection_point.z > plane_point.z + 0.5 + 0.3) {
            intersection_point = end_position;
        }
    }

    plane_point = cube_position + glm::vec3(1.3, 0.5, 0.5);
    plane_normal = {+1, 0, 0};
    intersects = intersect(plane_point, plane_normal, ray_point, ray_direction, intersection_point);
    if (intersects) {
        if (intersection_point.y < plane_point.y - 0.5 - 0.2 || intersection_point.y > plane_point.y + 0.5 + 1.6 ||
            intersection_point.z < plane_point.z - 0.5 - 0.3 || intersection_point.z > plane_point.z + 0.5 + 0.3) {
            intersection_point = end_position;
        }
    }

    plane_point = cube_position + glm::vec3(0.5, -0.2, 0.5);
    plane_normal = {0, -1, 0};
    intersects = intersect(plane_point, plane_normal, ray_point, ray_direction, intersection_point);
    if (intersects) {
        if (intersection_point.x < plane_point.x - 0.5 - 0.3 || intersection_point.x > plane_point.x + 0.5 + 0.3 ||
            intersection_point.z < plane_point.z - 0.5 - 0.3 || intersection_point.z > plane_point.z + 0.5 + 0.3) {
            intersection_point = end_position;
        }
    }

    plane_point = cube_position + glm::vec3(0.5, 2.6, 0.5);
    plane_normal = {0, +1, 0};
    intersects = intersect(plane_point, plane_normal, ray_point, ray_direction, intersection_point);
    if (intersects) {
        if (intersection_point.x < plane_point.x - 0.5 - 0.3 || intersection_point.x > plane_point.x + 0.5 + 0.3 ||
            intersection_point.z < plane_point.z - 0.5 - 0.3 || intersection_point.z > plane_point.z + 0.5 + 0.3) {
            intersection_point = end_position;
        }
    }

    plane_point = cube_position + glm::vec3(0.5, 0.5, -0.3);
    plane_normal = {0, 0, -1};
    intersects = intersect(plane_point, plane_normal, ray_point, ray_direction, intersection_point);
    if (intersects) {
        if (intersection_point.x < plane_point.x - 0.5 - 0.3 || intersection_point.x > plane_point.x + 0.5 + 0.3 ||
            intersection_point.y < plane_point.y - 0.5 - 0.2 || intersection_point.y > plane_point.y + 0.5 + 1.6) {
            intersection_point = end_position;
        }
    }

    plane_point = cube_position + glm::vec3(0.5, 0.5, 1.3);
    plane_normal = {0, 0, +1};
    intersects = intersect(plane_point, plane_normal, ray_point, ray_direction, intersection_point);
    if (intersects) {
        if (intersection_point.x < plane_point.x - 0.5 - 0.3 || intersection_point.x > plane_point.x + 0.5 + 0.3 ||
            intersection_point.y < plane_point.y - 0.5 - 0.2 || intersection_point.y > plane_point.y + 0.5 + 1.6) {
            intersection_point = end_position;
        }
    }

    return intersection_point;
}
