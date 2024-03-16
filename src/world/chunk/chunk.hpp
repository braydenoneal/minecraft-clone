#pragma once

#include "../../render/models/cube.hpp"

namespace chunk {
    struct block {
        int id;
    };

    struct chunk {
        int x;
        int z;
        block blocks[16 * 128 * 16];
    };

    int pos(int x, int y, int z) {
        return x * 16 * 128 + y * 16 + z;
    }

    struct chunk_location {
        int x;
        int z;
    };

    struct chunk_mesh {
        int x;
        int z;
        std::vector<float> mesh;
    };
}

/*
 * Storage:
 *      chunk data for loaded chunks: vector<chunk>
 *      each chunk mesh: vector<chunk_mesh>
 *      current total mesh: vector<float>
 *      chunk locations to calculate mesh (chunk queue): vector<chunk_location>
 *
 *
 * each frame:
 *      when chunk region changed:
 *          get chunk locations around player:
 *              if chunk location not in chunk data:
 *                  add chunk location to queue
 *          for chunk in chunk datas not around player:
 *              delete chunk data
 *          for chunk in chunk meshes not around player:
 *              delete chunk mesh
 *
 *      for next chunk location in queue:
 *          calc chunk data, add to datas
 *          calc chunk mesh, add to meshes
 *          set total mesh to recombine meshes
 */
