#include "ChunkLoader.hpp"

ChunkLoader::ChunkLoader(std::mutex &mesh_lock_reference, std::vector<offset> &mesh_reference, glm::vec3 &camera_position)
        : mesh_lock(mesh_lock_reference), total_mesh(mesh_reference), camera_position(camera_position) {}

void ChunkLoader::unloadRegions(const std::vector<Position> &positions) {
    std::vector<Position> remove_positions{};

    for (auto &region: regions) {
        bool remove = true;

        for (auto position: positions) {
            if (region.x == position.x && region.z == position.z) {
                remove = false;
            }
        }

        if (remove) {
            remove_positions.push_back({region.x, 0, region.z});
        }
    }

    for (auto position: remove_positions) {
        int remove_index = 0;

        for (int i = 0; i < regions.size(); i++) {
            if (regions[i].x == position.x && regions[i].z == position.z) {
                remove_index = i;
            }
        }

        regions.erase(regions.begin() + remove_index);
    }
}

void ChunkLoader::setRenderQueue() {
    int next_x_chunk = std::floor(camera_position.x / (float) CHUNK_SIZE);
    int next_z_chunk = std::floor(camera_position.z / (float) CHUNK_SIZE);

    if (next_x_chunk != x_chunk || next_z_chunk != z_chunk) {
        x_chunk = next_x_chunk;
        z_chunk = next_z_chunk;

        int x_region = x_chunk / POSITION_REGION_SIZE;
        int z_region = z_chunk / POSITION_REGION_SIZE;

        std::vector<Position> new_positions{};

        int region_radius = radius / POSITION_REGION_SIZE;

        for (int x = x_region - region_radius; x < x_region + region_radius; x++) {
            for (int z = z_region - region_radius; z < z_region + region_radius; z++) {
                new_positions.push_back({x, 0, z});
            }
        }

        unloadRegions(new_positions);

        for (auto position: new_positions) {
            bool add_to_queue = true;

            for (const auto &region: regions) {
                if (region.x == position.x && region.z == position.z) {
                    add_to_queue = false;
                }
            }

            if (add_to_queue) {
                PositionRegion region{};
                region.x = position.x;
                region.z = position.z;

                for (int x = 0; x < CHUNK_SIZE; x++) {
                    for (int z = 0; z < CHUNK_SIZE; z++) {
                        region.position_queue.push_back({position.x * POSITION_REGION_SIZE + x, 0,
                                                         position.z * POSITION_REGION_SIZE + z});
                    }
                }

                regions.push_back(region);
            }
        }
    }
}

void ChunkLoader::renderQueue() {
    std::sort(regions.begin(), regions.end(), QueueSorter(*this));

    std::vector<offset>::size_type mesh_size = 0;

    for (auto &region : regions) {
        if (!region.position_queue.empty()) {
            Position position = region.position_queue.front();

            region.position_queue.pop_front();

            Chunk chunk{position};

            region.chunks.push_back(chunk);

            std::vector<offset> new_mesh{};

            Cube::chunkToMesh(chunk, new_mesh, chunks);

            region.meshes.push_back({position, new_mesh});
        }
    }

    for (auto &region : regions) {
        for (const auto &mesh: region.meshes) {
            mesh_size += mesh.mesh.size();
        }
    }

    std::unique_lock<std::mutex> mesh_unique_lock(mesh_lock);

    total_mesh.clear();
    total_mesh.reserve(mesh_size);

    for (auto &region : regions) {
        for (const Mesh &mesh: region.meshes) {
            total_mesh.insert(total_mesh.end(), mesh.mesh.begin(), mesh.mesh.end());
        }
    }
}

[[noreturn]] void ChunkLoader::chunkLoop() {
    while (true) {
        setRenderQueue();
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

bool ChunkLoader::QueueSorter::operator()(const PositionRegion &region_1, const PositionRegion &region_2) const {
    return sqrt(pow(region_1.x - chunk_loader.x_chunk, 2) +
                pow(region_1.z - chunk_loader.z_chunk, 2))
        < sqrt(pow(region_2.x - chunk_loader.x_chunk, 2) +
               pow(region_2.z - chunk_loader.z_chunk, 2));
}
