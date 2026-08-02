#include <header_files/main.hpp>

void processInput(GLFWwindow* window);

using namespace Dreamcatcher;

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Dreamcatcher3D", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to load GLFW Window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD!" << std::endl;
        glfwTerminate();
        return -1;
    }

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
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        defaultShader.use();
        // glm::mat4 transform = glm::mat4(1.0f);
        // transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));

        // defaultShader.setMat4("transform", transform);
        
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

        defaultShader.setMat4("model", model);
        defaultShader.setMat4("view", view);
        defaultShader.setMat4("projection", projection);
        
        glBindTexture(GL_TEXTURE_2D, texture);

        // triangle.draw();
        rectangle.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
