#include "ChunkLoader.hpp"

ChunkLoader::ChunkLoader(std::mutex &mesh_lock_reference, std::vector<offset> &mesh_reference, glm::vec3 &camera_position)
        : mesh_lock(mesh_lock_reference), total_mesh(mesh_reference), camera_position(camera_position) {}

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

void ChunkLoader::unloadDataQueue(const std::vector<Position> &positions) {
    std::vector<Position> remove_positions{};

    for (auto &queue_position: data_queue) {
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

        for (int i = 0; i < data_queue.size(); i++) {
            if (data_queue[i] == position) {
                remove_index = i;
            }
        }

        data_queue.erase(data_queue.begin() + remove_index);
    }
}

void ChunkLoader::unloadQueue(const std::vector<Position> &positions) {
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

void ChunkLoader::setRenderQueue() {
    int next_x_chunk = std::floor(camera_position.x / (float) CHUNK_SIZE);
    int next_z_chunk = std::floor(camera_position.z / (float) CHUNK_SIZE);

    if (next_x_chunk != x_chunk || next_z_chunk != z_chunk) {
        x_chunk = next_x_chunk;
        z_chunk = next_z_chunk;

        std::vector<Position> mesh_positions{};
        std::vector<Position> chunk_positions{};

        for (int x = x_chunk - radius - 2; x <= x_chunk + radius + 2; x++) {
            for (int z = z_chunk - radius - 2; z <= z_chunk + radius + 2; z++) {
                if (pow(x - x_chunk, 2) + pow(z - z_chunk, 2) < pow(radius + 1, 2)) {
                    mesh_positions.push_back({x, 0, z});
                }
                if (pow(x - x_chunk, 2) + pow(z - z_chunk, 2) < pow(radius + 4, 2)) {
                    chunk_positions.push_back({x, 0, z});
                }
            }
        }

        unloadMeshes(mesh_positions);
        unloadChunks(chunk_positions);
        unloadQueue(mesh_positions);
        unloadDataQueue(chunk_positions);

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

        std::deque<Position> previous_data_queue = data_queue;

        for (auto position: chunk_positions) {
            bool add_to_queue = true;

            for (auto &chunk: chunks) {
                if (chunk.position == position) {
                    add_to_queue = false;
                }
            }

            for (auto &queue_position: previous_data_queue) {
                if (queue_position == position) {
                    add_to_queue = false;
                }
            }

            if (add_to_queue) {
                data_queue.push_back(position);
            }
        }

        std::sort(queue.begin(), queue.end(), QueueSorter(*this));
        std::sort(data_queue.begin(), data_queue.end(), QueueSorter(*this));
    }
}

void ChunkLoader::renderDataQueue() {
    if (!data_queue.empty()) {
        Position position = data_queue.front();

        data_queue.pop_front();

        chunks.emplace_back(position);
    }
}

void ChunkLoader::renderQueue() {
    if (!queue.empty()) {
        Position position = queue.front();

        queue.pop_front();

        for (const auto &chunk: chunks) {
            if (position == chunk.position) {
                std::vector<offset> new_mesh{};

                Cube::chunkToMesh(chunk, new_mesh, chunks);

                meshes.push_back({position, new_mesh});

                std::vector<offset>::size_type mesh_size = 0;

                for (const auto &mesh: meshes) {
                    mesh_size += mesh.mesh.size();
                }

                std::unique_lock<std::mutex> mesh_unique_lock(mesh_lock);

                total_mesh.clear();
                total_mesh.reserve(mesh_size);

                for (const Mesh &mesh: meshes) {
                    total_mesh.insert(total_mesh.end(), mesh.mesh.begin(), mesh.mesh.end());
                }
            }
        }
    }
}

[[noreturn]] void ChunkLoader::chunkLoop() {
    while (true) {
        setRenderQueue();
        for (int i = 0; i < 8; i++) {
            renderDataQueue();
        }
        renderQueue();
    }
}

Block ChunkLoader::getBlockAtPosition(glm::vec3 position) {
    int chunk_x = std::floor(position.x / (float) CHUNK_SIZE);
    int chunk_y = std::floor(position.y / (float) CHUNK_SIZE);
    int chunk_z = std::floor(position.z / (float) CHUNK_SIZE);

    for (const auto &chunk: chunks) {
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

ChunkLoader::QueueSorter::QueueSorter(ChunkLoader &chunk_loader_reference) : chunk_loader(chunk_loader_reference) {}

bool ChunkLoader::QueueSorter::operator()(Position position_1, Position position_2) const {
    return sqrt(pow(position_1.x - chunk_loader.x_chunk, 2) +
                pow(position_1.y - chunk_loader.y_chunk, 2) +
                pow(position_1.z - chunk_loader.z_chunk, 2))
        < sqrt(pow(position_2.x - chunk_loader.x_chunk, 2) +
                pow(position_2.y - chunk_loader.y_chunk, 2) +
                pow(position_2.z - chunk_loader.z_chunk, 2));
}
