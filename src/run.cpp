#include "window/window.hpp"
#include "input/input.hpp"

using namespace std;

struct chunkz {
    int x;
    int z;
    int blocks[6];
};

struct region {
    unsigned long chunk_quantity;
    vector<chunkz> chunks;
};

void write_initial() {
    ofstream wf("test.dat", ofstream::trunc | ofstream::binary);

    unsigned long chunk_quantity = 4;

    wf.write((char *) &chunk_quantity, sizeof(chunk_quantity));

    for (int i = 0; i < chunk_quantity; i++) {
        chunkz wc = {i, i};
        for (int j = 0; j < 6; j++) {
            wc.blocks[j] = j;
        }
        wf.write((char *) &wc, sizeof(wc));
    }

    wf.close();
}

region read_all() {
    ifstream rf("test.dat", ifstream::in | ifstream::binary);

    region read_region{};

    unsigned long chunk_quantity;

    rf.read((char *) &chunk_quantity, sizeof(unsigned long));

    read_region.chunk_quantity = chunk_quantity;

    for (int i = 0; i < chunk_quantity; i++) {
        chunkz wc{};
        rf.read((char *) &wc, sizeof(chunkz));
        read_region.chunks.push_back(wc);
        cout << wc.x << ", " << wc.z << endl;
        for (int block : wc.blocks) {
            cout << block << endl;
        }
    }

    rf.close();

    return read_region;
}

void write_append() {
    region r = read_all();

    ofstream wf("test.dat", ofstream::app | ofstream::binary);

    int q = (int) r.chunk_quantity;

    chunkz wc = {q, q};
    for (int j = 0; j < 6; j++) {
        wc.blocks[j] = j;
    }

    wf.write((char *) &wc, sizeof(wc));

    wf.seekp(0);

    unsigned long chunk_quantity = r.chunk_quantity + 1;

    wf.write((char *) &chunk_quantity, sizeof(chunk_quantity));

    wf.close();
}

int main() {
//    write_initial();
//    write_append();
//    read_all();

    window::create_context();
    input::create_context();

    while (!window::should_close()) {
        input::get_input();
        input::update_game_state();
        window::render();
    }

    window::terminate();

    return 0;
}
