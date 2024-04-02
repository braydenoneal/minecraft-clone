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
    ChunkLoader(WorldState &world_state_reference, std::mutex &mesh_lock_reference, std::vector<offset> &mesh_reference);

    void unloadMeshes(const std::vector<Position> &positions);

    void unloadChunks(const std::vector<Position> &positions);

    void unloadQueue(const std::vector<Position> &positions);

    void setRenderQueue();

    void renderQueue();

    void chunkLoop();

private:
    WorldState &world_state;
    std::vector<Chunk> chunks{};
    std::vector<Mesh> meshes{};
    std::deque<Position> queue{};
    std::deque<Position> chunk_queue{};
    int x_chunk{-1};
    int y_chunk{-1};
    int z_chunk{-1};
    int radius = 16;
    std::mutex &mesh_lock;
    std::vector<offset> &total_mesh;

    class QueueSorter {
    public:
        ChunkLoader &chunk_loader;

        explicit QueueSorter(ChunkLoader &chunk_loader_reference);

        bool operator() (Position position_1, Position position_2) const;
    };
};
