#include "Utility.h"
#include "PreShader.h"
#include "Shader.h"
#include <iostream>

void Utility::Framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Utility::ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int Utility::CompileSucceed(unsigned int shaderOBj)
{
    int  success;
    glGetShaderiv(shaderOBj, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderOBj, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return success;
}

int Utility::LinkSucceed(unsigned int shaderProgram)
{
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::Shader_Program Link fails\n" << infoLog << std::endl;
    }
    return success;
}

void ShaderUtility::ShaderingOrange(GLFWwindow* window)
{
    // build and compile our shader program
    // -----------------------------------------------------------------
    // vertex shader without color passed in
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    Utility::CompileSucceed(vertexShader); // check if succeed to compile

    // fragment shader Orange
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderOrange);
    Utility::CompileSucceed(fragmentShaderOrange); // check if succeed to compile

    // shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);         // link the first program object
    glAttachShader(shaderProgram, fragmentShaderOrange);
    glLinkProgram(shaderProgram);
    Utility::LinkSucceed(shaderProgram); // check if succeed to link

    // delete the shader objects once we've linked them into the program object
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);

    // draw a triangle
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window)) // check if GLFW exits? if yes, close the windows
    {
        Utility::ProcessInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 4. draw the object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);  // bind Vertex Array Object
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        //check if there are any IO events coming
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ShaderUtility::ShaderingConnectedTriangle(GLFWwindow* window)
{
    // build and compile our shader program
// -----------------------------------------------------------------
// vertex shader without color passed in
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    Utility::CompileSucceed(vertexShader); // check if succeed to compile

    // vertex shader with color passed in
    unsigned int vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader1, 1, &vertexShader1Source, nullptr);
    glCompileShader(vertexShader1);
    Utility::CompileSucceed(vertexShader1); // check if succeed to compile

    //// fragment shader Orange
    //unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSource, nullptr);
    //glCompileShader(fragmentShaderOrange);
    //Utility::CompileSucceed(fragmentShaderOrange); // check if succeed to compile

    // response to vertexShader1
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShader1Source, nullptr);
    glCompileShader(fragmentShader1);
    Utility::CompileSucceed(fragmentShader1); // check if succeed to compile

    // fragment shader Yellow
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, nullptr);
    glCompileShader(fragmentShaderYellow);
    Utility::CompileSucceed(fragmentShaderYellow); // check if succeed to compile

    // fragment shader Uniform
    unsigned int fragmentShaderUniform = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderUniform, 1, &fragmentShaderUniformSource, nullptr);
    glCompileShader(fragmentShaderUniform);
    Utility::CompileSucceed(fragmentShaderUniform); // check if succeed to compile

    // shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader1);         // link the first program object
    glAttachShader(shaderProgram, fragmentShader1);
    glLinkProgram(shaderProgram);
    Utility::LinkSucceed(shaderProgram); // check if succeed to link

    // shader program Yellow
    unsigned int shaderProgramYellow = glCreateProgram();
    // then link the second program object using a different fragment shader (but same vertex shader)
    // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    Utility::LinkSucceed(shaderProgramYellow); // check if succeed to link

    // shader program Uniform
    unsigned int shaderProgramUniform = glCreateProgram();
    // then link the second program object using a different fragment shader (but same vertex shader)
    // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
    glAttachShader(shaderProgramUniform, vertexShader);
    glAttachShader(shaderProgramUniform, fragmentShaderUniform);
    glLinkProgram(shaderProgramUniform);
    Utility::LinkSucceed(shaderProgramUniform); // check if succeed to link

    // delete the shader objects once we've linked them into the program object
    glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShaderYellow);
    glDeleteShader(fragmentShaderUniform);

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
            // position          // color
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
        };

        float secondTriangle[] = {
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.0f, -1.0f, 0.0f
        };

        float thirdTriangle[] = {
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            1.0f, 0.5f, 0.0f
        };

        // :: Initialization code, done once unless your object frequently changes
        unsigned int VBOs[3], VAOs[3];
        glGenVertexArrays(3, VAOs);  // we can also generate multiple VAOs or buffers at the same time
        glGenBuffers(3, VBOs);

        // first triangle setup
        // --------------------
        glBindVertexArray(VAOs[0]);  // bind the Vertex Array Object first
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
        //position attribute
        //6 * sizeof(float) is offset from start position
        //6: vertex XYZ + color RGB
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   // Vertex attributes stay the same
        glEnableVertexAttribArray(0);
        //color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines

        // second triangle setup
        // ---------------------
        glBindVertexArray(VAOs[1]);             // note that we bind to a different VAO now
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // and a different VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
        glEnableVertexAttribArray(0);

        // third triangle setup
        // ---------------------
        glBindVertexArray(VAOs[2]);             // note that we bind to a different VAO now
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]); // and a different VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(thirdTriangle), thirdTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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

            glUseProgram(shaderProgramUniform);
            //Update uniform color along with time change
            float timeValue = (float)glfwGetTime();
            float greenValue = sin(timeValue) / 2.0f + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgramUniform, "ourColor");
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

            // then we draw the second triangle using the data from the third VAO
            glBindVertexArray(VAOs[2]);
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
}

void ShaderUtility::ShaderingByCustomerizedShader(GLFWwindow* window)
{
    Shader ourShader("./path/shader.vs", "./path/shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

    // 1. bind the Vertex Array Object first,
    // 2. bind and set vertex buffer(s),
    // 3. configure vertex attributes(s).
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        Utility::ProcessInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
