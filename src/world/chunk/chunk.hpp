#pragma once

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
        return x * 16 * 16 + y * 128 + z;
    }

    struct chunk_location {
        int x;
        int z;
    };
}

/*
 * Storage:
 *      current chunk data
 *      current mesh
 *
 *      chunk locations
 *      chunk meshes
 *
 */
