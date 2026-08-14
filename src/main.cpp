#include <header_files/main.hpp>

using namespace Dreamcatcher;

Camera defaultCamera(glm::vec3(0.0f, 0.0f, 6.0f));
float lastX = static_cast<float>(WIN_WIDTH)  / 2.0f;
float lastY = static_cast<float>(WIN_HEIGHT) / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
int frameCount = 0;
float fpsTimer = 0;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main(void)
{
    Window defaultWindow;
    glfwSetCursorPosCallback(defaultWindow.GetHandle(), mouse_callback);
    glfwSetScrollCallback(defaultWindow.GetHandle(), scroll_callback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


    // glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    // glStencilFunc(GL_ALWAYS, 1, 0xFF);
    // glStencilMask(0xFF);

    // TEXTURE LOADING
    stbi_set_flip_vertically_on_load(true);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  -1.0f,  0.0f, 0.0f,
        -1.0f,   1.0f,  0.0f, 1.0f,
         1.0f,   1.0f,  1.0f, 1.0f,

         1.0f,   1.0f,  1.0f, 1.0f,
         1.0f,  -1.0f,  1.0f, 0.0f,
        -1.0f,  -1.0f,  0.0f, 0.0f
    };

    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    int width, height, nrChannels;
    unsigned char *data = stbi_load("../assets/broken_brick_wall_1k/textures/broken_brick_wall_diff_1k.jpg", &width, &height, &nrChannels, 0);
    
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture!" << std::endl;
    }
    stbi_image_free(data);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
    Triangle triangle;
    Plane plane;
    Cube cube;

    Shader defaultShader("../shaders/defaultVertexShader.glsl", "../shaders/defaultFragmentShader.glsl");
    Shader screenShader("../shaders/framebufferVertex.glsl", "../shaders/framebufferFragment.glsl");
    Shader shaderSingleColor("../shaders/defaultVertexShader.glsl", "../shaders/shaderSingleColor.glsl");
    Shader cubemapShader("../shaders/skyboxVertexShader.glsl", "../shaders/skyboxFragmentShader.glsl");

    Framebuffer defaultFramebuffer;
    Skybox skybox;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Loop until the user closes the window */
    while (!defaultWindow.ShouldClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        frameCount++;
        fpsTimer += deltaTime;

        if (fpsTimer >= 1.0f){
            std::string title = "Dreamcatcher3D | fps: " + std::to_string(frameCount);
            glfwSetWindowTitle(defaultWindow.GetHandle(), title.c_str());
            frameCount = 0;
            fpsTimer = 0;
        }
        
     
        processInput(defaultWindow.GetHandle());

        /* Render here */
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer.GetBuffer());
        glEnable(GL_DEPTH_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glStencilMask(0x00);


        // defaultShader.setMat4("transform", transform);
        glm::mat4 projection = glm::perspective(glm::radians(defaultCamera.Zoom),
                             (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::mat4(glm::mat3(defaultCamera.GetViewMatrix()));

        glDepthMask(GL_FALSE);
        cubemapShader.use();
        
        cubemapShader.setMat4("view", view);
        cubemapShader.setMat4("projection", projection);

        skybox.draw(); 
        glDepthMask(GL_TRUE);


        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
        view = defaultCamera.GetViewMatrix();



        defaultShader.use();
        defaultShader.setVec3("viewPos", defaultCamera.Position);
        defaultShader.setFloat("shininess", 32.0f);


        // direct light
        defaultShader.setVec3("directLight.direction", -1.0f, -1.0f, -1.0f);
        defaultShader.setVec3("directLight.ambient", 0.2f, 0.2f, 0.2f);
        defaultShader.setVec3("directLight.diffuse", 0.8f, 0.8f, 0.8f);
        defaultShader.setVec3("directLight.specular", 1.0f, 1.0f, 1.0f);



        // point light
        defaultShader.setVec3 ("pointLight.position", -3.0f, 4.0f, -1.0f);
        defaultShader.setFloat("pointLight.constant", 1.0f);
        defaultShader.setFloat("pointLight.linear", 0.09f);
        defaultShader.setFloat("pointLight.quadratic", 0.045f);

        defaultShader.setVec3 ("pointLight.ambient", 0.2f, 0.2f, 0.2f);
        defaultShader.setVec3 ("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
        defaultShader.setVec3 ("pointLight.specular", 1.0f, 1.0f, 1.0f);


        // spotlight
        defaultShader.setVec3 ("spotLight.position", defaultCamera.Position);
        defaultShader.setVec3 ("spotLight.direction", defaultCamera.Front);
        defaultShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        defaultShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(18.5f)));

        defaultShader.setFloat("spotLight.constant", 1.0f);
        defaultShader.setFloat("spotLight.linear", 0.09f);
        defaultShader.setFloat("spotLight.quadratic", 0.045f);

        defaultShader.setVec3 ("spotLight.ambient", 0.1f, 0.1f, 0.1f);
        defaultShader.setVec3 ("spotLight.diffuse", 0.8f, 0.8f, 0.8f);
        defaultShader.setVec3 ("spotLight.specular", 1.0f, 1.0f, 1.0f);

        defaultShader.setMat4("projection", projection);
        defaultShader.setMat4("view", view);

        glBindTexture(GL_TEXTURE_2D, texture);


        glm::mat4 planeModel = glm::mat4(1.0f);

        planeModel = glm::translate(planeModel, glm::vec3(0.0f, -2.0f, 0.0f));
        planeModel = glm::scale(planeModel, glm::vec3(10.0f, 1.0f, 10.0f));

        // for (unsigned int i = 0; i < 24; i++){
        //     for (unsigned int j = 0; j < 24; j++) {
        //         planeModel = glm::mat4((float)j);
        //         planeModel = glm::translate(planeModel, glm::vec3(-24.0f + (float)i * 2, -2.0f, -24.0f + (float)j * 2));
        //         defaultShader.setMat4("model", planeModel);
        //         plane.draw();
        //     }
        // }
        defaultShader.setMat4("model", planeModel);
        plane.draw();


        glm::mat4 cubeModel = glm::mat4(1.0f);
        cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, 2.0f, 0.0f));
        defaultShader.setMat4("model", cubeModel);


        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        cube.draw();

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        // glDisable(GL_DEPTH_TEST);
        shaderSingleColor.use();

        cubeModel = glm::scale(cubeModel, glm::vec3(1.01f, 1.01f, 1.01f));
        shaderSingleColor.setVec3("viewPos", defaultCamera.Position);
        shaderSingleColor.setMat4("projection", projection);
        shaderSingleColor.setMat4("view", view);
        shaderSingleColor.setMat4("model", cubeModel);
        
        cube.draw();
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // glEnable(GL_DEPTH_TEST);



        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
        glBindVertexArray(quadVAO);
        glBindTexture(GL_TEXTURE_2D, defaultFramebuffer.GetTexture());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // rectangle.draw();

        /* Swap front and back buffers */
        defaultWindow.SwapBuffers();

        /* Poll for and process events */
        defaultWindow.PollEvents();
    }

    return 0;
}

void processInput(GLFWwindow *window) {
  
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    defaultCamera.ProcessKeyboard(FORWARD, deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    defaultCamera.ProcessKeyboard(BACKWARD, deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    defaultCamera.ProcessKeyboard(RIGHT, deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    defaultCamera.ProcessKeyboard(LEFT, deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
    defaultCamera.ProcessKeyboard(UP, deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
      defaultCamera.ProcessKeyboard(DOWN, deltaTime);
  }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    defaultCamera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset){
    defaultCamera.ProcessMouseScroll(yoffset);
}
