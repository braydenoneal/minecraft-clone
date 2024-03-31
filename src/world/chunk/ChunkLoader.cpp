#include "ChunkLoader.hpp"

ChunkLoader::ChunkLoader(WorldState &world_state_reference, Cube &cube_reference)
        : world_state(world_state_reference), cube(cube_reference) {}

void ChunkLoader::setRenderQueue() {
    int next_x_chunk = std::floor(world_state.camera_position.x / (float) CHUNK_SIZE);
    int next_z_chunk = std::floor(world_state.camera_position.z / (float) CHUNK_SIZE);

    if (next_x_chunk != x_chunk || next_z_chunk != z_chunk) {
        x_chunk = next_x_chunk;
        z_chunk = next_z_chunk;

        std::vector<Position> positions{};

        for (int x = x_chunk - radius; x <= x_chunk + radius; x++) {
            for (int z = z_chunk - radius; z <= z_chunk + radius; z++) {
                if (pow(x - x_chunk, 2) + pow(z - z_chunk, 2) < pow(radius + 1, 2)) {
                    positions.push_back({x, 0, z});
                }
            }
        }

        unloadMeshes(positions);
        unloadChunks(positions);
        unloadQueue(positions);

        std::deque<Position> previous_queue = queue;

        for (auto position: positions) {
            bool add_to_queue = true;

            for (auto &chunk: chunks) {
                if (chunk.position.x == position.x && chunk.position.z == position.z) {
                    add_to_queue = false;
                }
            }

            for (auto &queue_position: previous_queue) {
                if (queue_position.x == position.x && queue_position.z == position.z) {
                    add_to_queue = false;
                }
            }

            if (add_to_queue) {
                queue.push_back(position);
            }
        }
    }
}

void ChunkLoader::unloadMeshes(const std::vector<Position> &positions) {
    std::vector<Position> remove_meshes{};

    for (auto &mesh: meshes) {
        bool remove = true;

        for (auto position: positions) {
            if (mesh.position.x == position.x && mesh.position.z == position.z) {
                remove = false;
            }
        }

        if (remove) {
            remove_meshes.push_back(mesh.position);
        }
    }

    for (auto position: remove_meshes) {
        int remove_index = 0;

        for (int i = 0; i < meshes.size(); i++) {
            if (meshes[i].position.x == position.x && meshes[i].position.z == position.z) {
                remove_index = i;
            }
        }

        meshes.erase(meshes.begin() + remove_index);
    }
}

void ChunkLoader::unloadChunks(const std::vector<Position> &positions) {
    std::vector<Position> remove_chunks{};

    for (auto &chunk: chunks) {
        bool remove = true;

        for (auto position: positions) {
            if (chunk.position.x == position.x && chunk.position.z == position.z) {
                remove = false;
            }
        }

        if (remove) {
            remove_chunks.push_back(chunk.position);
        }
    }

    for (auto position: remove_chunks) {
        int remove_index = 0;

        for (int i = 0; i < chunks.size(); i++) {
            if (chunks[i].position.x == position.x && chunks[i].position.z == position.z) {
                remove_index = i;
            }
        }

        chunks.erase(chunks.begin() + remove_index);
    }
}

void ChunkLoader::unloadQueue(const vector<Position> &positions) {
    std::vector<Position> remove_positions{};

    for (auto &queue_position: queue) {
        bool remove = true;

        for (auto position: positions) {
            if (queue_position.x == position.x && queue_position.z == position.z) {
                remove = false;
            }
        }

        if (remove) {
            remove_positions.push_back(queue_position);
        }
    }

    for (auto position: remove_positions) {
        int remove_index = 0;

        for (int i = 0; i < queue.size(); i++) {
            if (queue[i].x == position.x && queue[i].z == position.z) {
                remove_index = i;
            }
        }

        queue.erase(queue.begin() + remove_index);
    }
}

void ChunkLoader::renderQueue() {
    if (!queue.empty()) {
        Position position = queue.front();

        queue.pop_front();

        Chunk chunk(position);

        chunks.push_back(chunk);

        std::vector<offset> mesh{};

        Cube::chunkToMesh(chunk, mesh);

        meshes.push_back({position, mesh});

        cube.combineMeshes(meshes);
    }
}
