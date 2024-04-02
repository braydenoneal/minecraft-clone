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

    void setRenderQueue();

    void unloadMeshes(const std::vector<Position> &positions);

    void unloadChunks(const std::vector<Position> &positions);

    void unloadQueue(const std::vector<Position> &positions);

    void renderQueue();

    void chunkLoop();

private:
    WorldState &world_state;
    std::vector<Chunk> chunks{};
    std::vector<Mesh> meshes{};
    std::deque<Position> queue{};
    int x_chunk{-1};
    int y_chunk{-1};
    int z_chunk{-1};
    int radius = 24;
    std::vector<offset> &mesh;
    std::mutex &mesh_lock;

    class QueueSorter {
    public:
        ChunkLoader &chunk_loader;

        explicit QueueSorter(ChunkLoader &chunk_loader_reference);

        bool operator() (Position position_1, Position position_2) const;
    };
};
