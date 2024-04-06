#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include <mutex>

#include "../../graphics/models/cube/Cube.hpp"
#include "../WorldState.hpp"
#include "Chunk.hpp"

class ChunkLoader {
public:
    std::vector<Chunk> chunks{};

    ChunkLoader(std::mutex &mesh_lock_reference, std::vector<offset> &mesh_reference, glm::vec3 &camera_position);

    void unloadMeshes(const std::vector<Position> &positions);

    void unloadChunks(const std::vector<Position> &positions);

    void unloadQueue(const std::vector<Position> &positions);

    void setRenderQueue();

    void renderQueue();

    void chunkLoop();

private:
    glm::vec3 &camera_position;
    std::vector<Mesh> meshes{};
    std::deque<Position> queue{};
    int x_chunk{-1};
    int y_chunk{-1};
    int z_chunk{-1};
    int radius = 12;
    std::mutex &mesh_lock;
    std::vector<offset> &total_mesh;

    class QueueSorter {
    public:
        ChunkLoader &chunk_loader;

        explicit QueueSorter(ChunkLoader &chunk_loader_reference);

        bool operator() (Position position_1, Position position_2) const;
    };
};
