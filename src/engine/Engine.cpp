#include "Engine.h"

Engine::Engine(const int window_width, const int window_height) {
    // Initialize GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Imagin3D", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);

    // Initialize GLAD
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
        }

    // Configure Viewport
        glViewport(0, 0, window_width, window_height);
        glfwSetFramebufferSizeCallback(window,
            [](GLFWwindow*, const int width, const int height) -> void {
                glViewport(0, 0, width, height);
            }
        );


    this->window = window;
}

void Engine::ProcessInput() {
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
}

void Engine::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    this->Triangle();
}

void Engine::Triangle() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // VERTEX ARRAY OBJECT
        /**
         * A vertex array object stores the following:
         * - Calls to glEnableVertexAttribArray or glDisableVertexAttribArray
         * - Vertex attribute configurations via glVertexAttribPointer
         * - Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer
         */
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

    // VERTEX BUFFER OBJECT
        // vertex buffer objects (VBO) -> gpu memory used to store vertices
            unsigned int VBO;
            glGenBuffers(1, &VBO);
            // the buffer type of vertex buffer object is GL_ARRAY_BUFFER
            glBindBuffer(GL_ARRAY_BUFFER, VBO); // From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used to configure the currently bound buffer, which is VBO.

        /**
         * Params:
         * 1) Its first argument is the type of the buffer we want to copy data into: the vertex buffer object currently bound to the GL_ARRAY_BUFFER target.
         * 2) The second argument specifies the size of the data (in bytes) we want to pass to the buffer
         * 3) The third parameter is the actual data we want to send.
         * 4) The fourth parameter specifies how we want the graphics card to manage the given data. This can take 3 forms (GL_STREAM_DRAW, GL_STATIC_DRAW, GL_DYNAMIC_DRAW)
         *      GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
         *      GL_STATIC_DRAW: the data is set only once and used many times.
         *      GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
         *      The position data of the triangle does not change, is used a lot, and stays the same for every render call so its usage type should best be GL_STATIC_DRAW. If, for instance, one would have a buffer with data that is likely to change frequently, a usage type of GL_DYNAMIC_DRAW ensures the graphics card will place the data in memory that allows for faster writes.
         */
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // LINKING VERTEX ATTRIBUTES
        // we have to manually specify what part of our input data goes to which vertex attribute in the vertex shader

        // index for the POSITION attribute (index of aPos)
        constexpr int index_aPos = 0;

        /** vertex attribute is POSITION.
          * Params:
          * 1) index of POSITION
          * 2) POSITION is a VEC3 (size 3)
          * 3) Type of Data of each POSITION element
          * 4) Normalize to 0 and 1
          * 5) Stride = Step = Next Position in the array
          * 6) Offset
          *
          * glVertexAttribPointer takes date from the current GL_ARRAY_BUFFER, which is the VBO at this point.
        **/
        glVertexAttribPointer(index_aPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));

        // We are enabling the POSITION attribute
        glEnableVertexAttribArray(index_aPos);

        // since the VBO is already registered to the VAO, we can unbind it safely.
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // same for VAO.
        glBindVertexArray(0);

    // CREATE SHADER PROGRAM
        // CREATE VERTEX SHADER
            const auto *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

            const auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
            // 1) shader object, 2) # of strings, 3) source, 4) ?
            glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
            glCompileShader(vertexShader);

            int  success;
            char infoLog[512];

            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
                std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

        // CREATE FRAGMENT SHADER
            const auto fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";

            const auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);

            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
                std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

        // CREATE PROGRAM
            const auto shaderProgram = glCreateProgram();

            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
                std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        /**
         * Params:
         * 1) the OpenGL primitive type we would like to draw
         * 2) specifies the starting index of the vertex array we'd like to draw
         * 3) how many vertices we want to draw, which is 3 (we only render 1 triangle from our data, which is exactly 3 vertices long).
         */
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
}

void Engine::Run() {
    if (this->window == nullptr) std::cerr << "could not run engine: window is null" << std::endl;
    else {
        while(!glfwWindowShouldClose(this->window))
        {
            this->ProcessInput();
            this->Render();

            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }
    }
}

Engine::~Engine() {
    glfwTerminate();
}