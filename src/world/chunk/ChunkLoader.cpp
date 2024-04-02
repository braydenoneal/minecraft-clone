#include <iostream>
#include "ChunkLoader.hpp"

ChunkLoader::ChunkLoader(WorldState &world_state_reference, std::mutex &mesh_lock_reference, std::vector<offset> &mesh_reference)
        : world_state(world_state_reference), mesh_lock(mesh_lock_reference), mesh(mesh_reference) {}

void ChunkLoader::setRenderQueue() {
    int next_x_chunk = std::floor(world_state.camera_position.x / (float) CHUNK_SIZE);
    int next_y_chunk = std::floor(world_state.camera_position.y / (float) CHUNK_SIZE);
    int next_z_chunk = std::floor(world_state.camera_position.z / (float) CHUNK_SIZE);

    if (next_x_chunk != x_chunk || next_z_chunk != z_chunk) {
        x_chunk = next_x_chunk;
        y_chunk = next_y_chunk;
        z_chunk = next_z_chunk;

        std::vector<Position> mesh_positions{};
        std::vector<Position> chunk_positions{};

        for (int x = x_chunk - radius - 1; x <= x_chunk + radius + 1; x++) {
            for (int z = z_chunk - radius - 1; z <= z_chunk + radius + 1; z++) {
                if (pow(x - x_chunk, 2) + pow(z - z_chunk, 2) < pow(radius + 1, 2)) {
                    mesh_positions.push_back({x, 0, z});
                }
                if (pow(x - x_chunk, 2) + pow(z - z_chunk, 2) < pow(radius + 2, 2)) {
                    chunk_positions.push_back({x, 0, z});
                }
            }
        }

        unloadMeshes(mesh_positions);
        unloadChunks(chunk_positions);
        unloadQueue(mesh_positions);

        std::deque<Position> previous_queue = queue;

        for (auto position: mesh_positions) {
            bool add_to_queue = true;

            for (auto &chunk: meshes) {
                if (chunk.position == position) {
                    add_to_queue = false;
                }
            }

            for (auto &queue_position: previous_queue) {
                if (queue_position == position) {
                    add_to_queue = false;
                }
            }

            if (add_to_queue) {
                queue.push_back(position);
            }
        }

        for (auto position: chunk_positions) {
            bool add_to_queue = true;

            for (auto &chunk: chunks) {
                if (chunk.position == position) {
                    add_to_queue = false;
                }
            }

            for (auto &queue_position: previous_queue) {
                if (queue_position == position) {
                    add_to_queue = false;
                }
            }

            if (add_to_queue) {
                Chunk chunk(position);
                chunks.push_back(chunk);
            }
        }

        QueueSorter queue_sorter(*this);
        std::sort(queue.begin(), queue.end(), queue_sorter);
    }
}

void ChunkLoader::unloadMeshes(const std::vector<Position> &positions) {
    std::vector<Position> remove_meshes{};

    for (auto &mesh: meshes) {
        bool remove = true;

        for (auto position: positions) {
            if (mesh.position == position) {
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
            if (meshes[i].position == position) {
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
            if (chunk.position == position) {
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
            if (chunks[i].position == position) {
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
            if (queue_position == position) {
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
            if (queue[i] == position) {
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

        for (const auto &chunk: chunks) {
            if (position == chunk.position) {
                std::vector<offset> new_mesh1{};

                Cube::chunkToMesh(chunk, new_mesh1, chunks);

                meshes.push_back({position, new_mesh1});

                // TODO: Chunk culling: Combine only the meshes of chunks that are in the camera frustum
                std::vector<offset>::size_type mesh_size = 0;

                for (const auto &new_mesh: meshes) {
                    mesh_size += new_mesh.mesh.size();
                }

                vector<offset> total_mesh;
                total_mesh.reserve(mesh_size);

                for (const Mesh &new_mesh: meshes) {
                    total_mesh.insert(total_mesh.end(), new_mesh.mesh.begin(), new_mesh.mesh.end());
                }

                mesh_lock.lock();
                mesh = total_mesh;
                mesh_lock.unlock();
            }
        }
    }
}

void ChunkLoader::chunkLoop() {
    while (true) {
        setRenderQueue();
        renderQueue();
    }
}

ChunkLoader::QueueSorter::QueueSorter(ChunkLoader &chunk_loader_reference) : chunk_loader(chunk_loader_reference) {}

bool ChunkLoader::QueueSorter::operator()(Position position_1, Position position_2) const {
    return sqrt(pow(position_1.x - chunk_loader.x_chunk, 2) +
                pow(position_1.y - chunk_loader.y_chunk, 2) +
                pow(position_1.z - chunk_loader.z_chunk, 2))
        < sqrt(pow(position_2.x - chunk_loader.x_chunk, 2) +
                pow(position_2.y - chunk_loader.y_chunk, 2) +
                pow(position_2.z - chunk_loader.z_chunk, 2));
}