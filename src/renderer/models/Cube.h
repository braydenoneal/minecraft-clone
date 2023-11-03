class Cube {
public:
    static void draw(glm::mat4 perspective, unsigned int count, glm::vec3 camera_position, glm::vec3 camera_angle, glm::vec3 model_position, glm::vec3 model_angle) {
        unsigned int tris_count = 12;

        float positions[] = {
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

        unsigned int indices[] = {
                0, 1, 2, 3, 4, 1,
                5, 6, 7, 8, 9, 6,
                10, 11, 12, 13, 14, 11,
                15, 16, 17, 18, 19, 16,
                20, 21, 22, 23, 24, 21,
                25, 26, 27, 28, 29, 26
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        VertexArray va = VertexArray();
        VertexBuffer vb(positions, 30 * 7 * sizeof(float));

        VertexBufferLayout layout;
        layout.push(GL_FLOAT, 3, GL_FALSE);
        layout.push(GL_FLOAT, 3, GL_FALSE);
        layout.push(GL_FLOAT, 1, GL_FALSE);
        va.add_buffer(vb, layout);

        IndexBuffer ib = IndexBuffer(indices, tris_count * 3);

        Shader shader = Shader("../res/shaders/Basic.glsl");

        std::vector<std::string> texture_paths = {"../res/textures/grass_block_side.png", "../res/textures/grass_block_top.png", "../res/textures/dirt.png"};

        Texture textures(texture_paths);
        textures.bind(0);
        shader.set_uniform_1i("u_Textures", 0);


        for (unsigned int i = 0; i < count; i++) {
            for (unsigned int j = 0; j < count; j++) {
                glm::mat4 model_view = Transform::render_transformation(camera_position, camera_angle, glm::vec3(model_position.x + i, model_position.y, model_position.z + j), model_angle);

                shader.bind();
                shader.set_uniform_matrix_4fv("u_MVP", perspective * model_view);

                glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
            }
        }

        VertexArray::unbind();
        VertexBuffer::unbind();
        IndexBuffer::unbind();
        Shader::unbind();
//        Renderer::draw(va, ib, shader);
    }
};
