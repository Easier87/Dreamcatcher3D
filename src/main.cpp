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

    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);

    // TEXTURE LOADING
    stbi_set_flip_vertically_on_load(true);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("../assets/png_image.png", &width, &height, &nrChannels, 0);
    
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture!" << std::endl;
    }
    stbi_image_free(data);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
    Triangle triangle;
    Rectangle rectangle;
    Shader defaultShader("../shaders/defaultVertexShader.glsl", "../shaders/defaultFragmentShader.glsl");

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
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        defaultShader.use();
        // glm::mat4 transform = glm::mat4(1.0f);
        // transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));

        // defaultShader.setMat4("transform", transform);
        
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = defaultCamera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(defaultCamera.Zoom),
                (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

        defaultShader.setMat4("model", model);
        defaultShader.setMat4("view", view);
        defaultShader.setMat4("projection", projection);
        
        glBindTexture(GL_TEXTURE_2D, texture);

        // triangle.draw();
        rectangle.draw();

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
