#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include <mutex>

#include "../../graphics/models/cube/Cube.hpp"
#include "../WorldState.hpp"
#include "Chunk.hpp"

#define POSITION_REGION_SIZE 16

struct PositionRegion {
    int x;
    int z;
    std::deque<Position> position_queue;
    std::vector<Mesh> meshes;
    std::vector<Chunk> chunks;
};

class ChunkLoader {
public:
    std::vector<Chunk> chunks{};
    std::vector<PositionRegion> regions{};

    ChunkLoader(std::mutex &mesh_lock_reference, std::vector<offset> &mesh_reference, glm::vec3 &camera_position);

    void unloadRegions(const std::vector<Position> &positions);

    void setRenderQueue();

    void renderQueue();

    [[noreturn]] void chunkLoop();

    Block getBlockAtPosition(glm::vec3 position);

private:
    glm::vec3 &camera_position;
    std::vector<Mesh> meshes{};
    std::deque<Position> data_queue{};
    std::deque<Position> queue{};
    int x_chunk{-1};
    int z_chunk{-1};
    int radius = 16;
    std::mutex &mesh_lock;
    std::vector<offset> &total_mesh;

    class QueueSorter {
    public:
        ChunkLoader &chunk_loader;

        explicit QueueSorter(ChunkLoader &chunk_loader_reference);

        bool operator() (const PositionRegion &region_1, const PositionRegion &region_2) const;
    };
};
