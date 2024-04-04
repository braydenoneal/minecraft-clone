#include "Crosshair.hpp"


Crosshair::Crosshair() {
    shader.setShaders("../res/shaders/crosshair/vertex.glsl", "../res/shaders/crosshair/fragment.glsl");
    shader.bind();

    std::vector<Vertex> vertex_buffer_data = {
        {-2, 2},
        {-2, 18},
        {2, 2},

        {2, 18},
        {2, 2},
        {-2, 18},


        {-18, -2},
        {-18, 2},
        {18, -2},

        {18, 2},
        {18, -2},
        {-18, 2},


        {-2, -18},
        {-2, -2},
        {2, -18},

        {2, -2},
        {2, -18},
        {-2, -2},
    };

    vertex_count = (GLsizei) vertex_buffer_data.size();

    vertex_buffer.setData((GLsizeiptr) (vertex_buffer_data.size() * sizeof(Vertex)), &vertex_buffer_data[0]);

    vertex_array.addAttributes(vertex_buffer, {{2, GL_FLOAT, GL_FALSE}}, 0);
}

void Crosshair::draw() const {
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void Crosshair::setUniforms(float aspect_ratio, float width) const {
    shader.setUniform1f("u_aspect_ratio", aspect_ratio);
    shader.setUniform1f("u_width", width);
}
