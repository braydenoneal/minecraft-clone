class Cube {
public:
    float positions[1 * 5 * 7 * 6] = {
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.6f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.6f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.6f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f,

             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.6f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.6f,
            -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f,
            -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.6f,
            -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f,

            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.8f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.8f,
            -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f,
            -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.8f,
            -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f,

             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.8f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.8f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.8f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f,

            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,

             0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  2.0f,  0.4f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  2.0f,  0.4f,
            -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f,
            -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  2.0f,  0.4f,
            -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f,
    };

    unsigned int indices[1 * 6 * 6] = {
            0, 1, 2, 3, 4, 1,
            5, 6, 7, 8, 9, 6,
            10, 11, 12, 13, 14, 11,
            15, 16, 17, 18, 19, 16,
            20, 21, 22, 23, 24, 21,
            25, 26, 27, 28, 29, 26
    };

    std::vector<std::string> texture_paths = {"../res/textures/grass_block_side.png", "../res/textures/grass_block_top.png", "../res/textures/dirt.png"};

    VertexArray va = VertexArray();
    VertexBufferLayout layout = VertexBufferLayout();
    VertexBuffer vb; // = VertexBuffer(positions, 1 * 5 * 7 * sizeof(float));
    IndexBuffer ib; // = IndexBuffer(indices, 1 * 6);
    Shader shader = Shader("../res/shaders/Basic.glsl");
    Texture textures = Texture(texture_paths);

    Cube(int quad_count, float positions[], unsigned int indices[]) :
            vb(VertexBuffer(positions, quad_count * 5 * 7 * sizeof(float))),
            ib(IndexBuffer(indices, quad_count * 6)) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        layout.push(GL_FLOAT, 3, GL_FALSE);
        layout.push(GL_FLOAT, 3, GL_FALSE);
        layout.push(GL_FLOAT, 1, GL_FALSE);
        va.add_buffer(vb, layout);

        textures.bind(0);
        shader.set_uniform_1i("u_Textures", 0);
    }

    void draw(glm::mat4 perspective, unsigned int count, glm::vec3 camera_position, glm::vec3 camera_angle, glm::vec3 model_position, glm::vec3 model_angle) {
        glm::mat4 camera_rotate = Transform::rotate(camera_angle);
        glm::mat4 camera_translate = Transform::translate(glm::vec3(-camera_position.x, -camera_position.y, camera_position.z));
        glm::mat4 model_rotate = Transform::rotate(model_angle);

        shader.bind();
//        shader.set_uniform_matrix_4fv("u_cr", camera_rotate);
//        shader.set_uniform_matrix_4fv("u_ct", camera_translate);
//        shader.set_uniform_matrix_4fv("u_mr", model_rotate);
//        shader.set_uniform_matrix_4fv("u_p", perspective);
        shader.set_uniform_matrix_4fv("u_all", perspective * camera_rotate * camera_translate);

        for (unsigned int i = 0; i < count; i++) {
            for (unsigned int j = 0; j < count; j++) {
                glm::mat4 model_translate = Transform::translate(glm::vec3(model_position.x + ((float) i - (float) count / 2.0f) * 16, model_position.y, model_position.z + ((float) j - (float) count / 2.0f) * 16));
                shader.set_uniform_matrix_4fv("u_mt", model_translate);

                glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
            }
        }
    }
};
