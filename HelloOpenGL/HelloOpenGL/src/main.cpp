#include "Utility.h"
#include "Shader.h"
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    // glfw: configure the glfw information
    // -----------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // fix compilation on OS X
#endif

    // create glfw window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    // call this function when adjusing windows size
    glfwSetFramebufferSizeCallback(window, Utility::Framebuffer_size_callback);

    // glad: init glad to load the openGL function pointer
    // -----------------------------------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    // build and compile our shader program
    // -----------------------------------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    Utility::CompileSucceed(vertexShader); // check if succeed to compile

    // fragment shader Orange
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderOrange);
    Utility::CompileSucceed(fragmentShaderOrange); // check if succeed to compile

    // fragment shader Yellow
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, nullptr);
    glCompileShader(fragmentShaderYellow);
    Utility::CompileSucceed(fragmentShaderYellow); // check if succeed to compile

    // shader program Orange
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);         // link the first program object
    glAttachShader(shaderProgram, fragmentShaderOrange);
    glLinkProgram(shaderProgram);
    Utility::LinkSucceed(fragmentShaderOrange); // check if succeed to link

    // shader program Yellow
    unsigned int shaderProgramYellow = glCreateProgram();
    // then link the second program object using a different fragment shader (but same vertex shader)
    // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    Utility::LinkSucceed(shaderProgramYellow); // check if succeed to link

    // delete the shader objects once we've linked them into the program object
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);

    int id = 4;
    // draw a triangle
    if (id == 1) {
        // set up vertex data (and buffer(s)) and configure vertex attributes
         // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,  // left
             0.5f, -0.5f, 0.0f,  // right
             0.0f,  0.5f, 0.0f   // top
        };

        // :: Initialization code, done once unless your object frequently changes
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO); // 1. bind the Vertex Array Object first

        // 2. then bind and set vertex buffer(s),
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        // copy vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 3. and then configure vertex attributes(s)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        //draw in wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // render loop
        while (!glfwWindowShouldClose(window)) // check if GLFW exits? if yes, close the windows
        {
            Utility::ProcessInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT); \

            // 4. draw the object
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);  // bind Vertex Array Object
            glDrawArrays(GL_TRIANGLES, 0, 4);

            glfwSwapBuffers(window);
            //check if there are any IO events coming
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    // draw two connected triangles
    if (id == 2) {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            // first triangle
            -0.5f, -0.5f, 0.0f,  // left
             0.5f, -0.5f, 0.0f,  // right
             0.0f,  0.5f, 0.0f,   // top
             // second triangle
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.0f, -1.0f, 0.0f
        };

        // :: Initialization code, done once unless your object frequently changes
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO); // 1. bind the Vertex Array Object first

        // 2. then bind and set vertex buffer(s),
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        // copy vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 3. and then configure vertex attributes(s)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        //draw in wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // render loop
        while (!glfwWindowShouldClose(window)) // check if GLFW exits? if yes, close the windows
        {
            Utility::ProcessInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT); \

            // 4. draw the object
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);  // bind Vertex Array Object
            glDrawArrays(GL_TRIANGLES, 0, 6); // draw six vertex

            glfwSwapBuffers(window);
            //check if there are any IO events coming
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    if (id == 3)
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
             0.5f,  0.5f, 0.0f,  // top right     (0)
             0.5f, -0.5f, 0.0f,  // bottom right  (1)
            -0.5f, -0.5f, 0.0f,  // bottom left   (2)
            -0.5f,  0.5f, 0.0f   // top left      (3)
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        // :: Initialization code, done once unless your object frequently changes
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO); // 1. bind the Vertex Array Object first

        // 2. then bind and set vertex buffer(s),
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        // copy vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 3. and then configure vertex attributes(s)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // 4. create and bind the EBO
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        //draw in wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // render loop
        while (!glfwWindowShouldClose(window)) // check if GLFW exits? if yes, close the windows
        {
            Utility::ProcessInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT); \

            // 4. draw the object
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);  // bind Vertex Array Object
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);
            //check if there are any IO events coming
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    if (id == 4)
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float firstTriangle[] = {
            // first triangle
            -0.5f, -0.5f, 0.0f,  // left
             0.5f, -0.5f, 0.0f,  // right
             0.0f,  0.5f, 0.0f   // top
        };

        float secondTriangle[] = {
             // second triangle
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.0f, -1.0f, 0.0f
        };

        // :: Initialization code, done once unless your object frequently changes
        unsigned int VBOs[2], VAOs[2];
        glGenVertexArrays(2, VAOs);  // we can also generate multiple VAOs or buffers at the same time
        glGenBuffers(2, VBOs);

        // first triangle setup
        // --------------------
        glBindVertexArray(VAOs[0]);  // bind the Vertex Array Object first
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);   // Vertex attributes stay the same
        glEnableVertexAttribArray(0);
        // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines

        // second triangle setup
        // ---------------------
        glBindVertexArray(VAOs[1]);             // note that we bind to a different VAO now
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // and a different VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
        glEnableVertexAttribArray(0);

        //draw in wireframe mode
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // render loop
        while (!glfwWindowShouldClose(window)) // check if GLFW exits? if yes, close the windows
        {
            Utility::ProcessInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT); 

            // 4. draw the object
            glUseProgram(shaderProgram);
            // draw first triangle using the data from the first VAO
            glBindVertexArray(VAOs[0]);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glUseProgram(shaderProgramYellow);
            // then we draw the second triangle using the data from the second VAO
            glBindVertexArray(VAOs[1]);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            //check if there are any IO events coming
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(2, VAOs);
        glDeleteBuffers(2, VBOs);
    }

    // clear all previously allocated GLFW resources
    glfwTerminate();

    return 0;
}