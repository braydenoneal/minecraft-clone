class Cube {
public:
    int tris_count = 12;

    float positions[210] = {
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

    unsigned int indices[36] = {
            0, 1, 2, 3, 4, 1,
            5, 6, 7, 8, 9, 6,
            10, 11, 12, 13, 14, 11,
            15, 16, 17, 18, 19, 16,
            20, 21, 22, 23, 24, 21,
            25, 26, 27, 28, 29, 26
    };

    VertexArray va = VertexArray();
    Shader shader = Shader("../res/shaders/Basic.glsl");
    IndexBuffer ib = IndexBuffer(indices, tris_count * 3);

    Cube() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        VertexBuffer vb(positions, 30 * 7 * sizeof(float));

        VertexBufferLayout layout;
        layout.push(GL_FLOAT, 3, GL_FALSE);
        layout.push(GL_FLOAT, 3, GL_FALSE);
        layout.push(GL_FLOAT, 1, GL_FALSE);
        va.add_buffer(vb, layout);

        std::vector<std::string> texture_paths = {"../res/textures/grass_block_side.png", "../res/textures/grass_block_top.png", "../res/textures/dirt.png"};

        Texture textures(texture_paths);
        textures.bind(0);
        shader.set_uniform_1i("u_Textures", 0);

        VertexArray::unbind();
        VertexBuffer::unbind();
        IndexBuffer::unbind();
        Shader::unbind();
    }

    void draw(glm::mat4 mvp) {
        shader.bind();
        shader.set_uniform_matrix_4fv("u_MVP", mvp);
        Renderer::draw(va, ib, shader);
    }
};
