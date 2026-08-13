#include <skybox.hpp>

using namespace Dreamcatcher;

Skybox::Skybox() : skyboxVertices{
                      -1.0f, -1.0f, -1.0f, // bottom-left
                       1.0f,  1.0f, -1.0f, // bottom-right    
                       1.0f, -1.0f, -1.0f, // top-right              
                       1.0f,  1.0f, -1.0f, // top-right
                      -1.0f, -1.0f, -1.0f, // top-left
                      -1.0f,  1.0f, -1.0f, // bottom-left                
                      // front face
                      -1.0f, -1.0f,  1.0f, // bottom-left
                       1.0f, -1.0f,  1.0f, // top-right
                       1.0f,  1.0f,  1.0f, // bottom-right        
                       1.0f,  1.0f,  1.0f, // top-right
                      -1.0f,  1.0f,  1.0f, // bottom-left
                      -1.0f, -1.0f,  1.0f, // top-left        
                      // left face
                      -1.0f,  1.0f,  1.0f, // top-right
                      -1.0f,  1.0f, -1.0f, // top-left
                      -1.0f, -1.0f, -1.0f, // bottom-left
                      -1.0f, -1.0f, -1.0f, // bottom-left
                      -1.0f, -1.0f,  1.0f, // bottom-right
                      -1.0f,  1.0f,  1.0f, // top-right
                      // right face
                       1.0f,  1.0f,  1.0f, // top-left
                       1.0f, -1.0f, -1.0f, // bottom-right
                       1.0f,  1.0f, -1.0f, // top-right
                       1.0f, -1.0f, -1.0f, // bottom-right
                       1.0f,  1.0f,  1.0f, // top-left
                       1.0f, -1.0f,  1.0f, // bottom-left
                      // bottom face
                      -1.0f, -1.0f, -1.0f, // top-right
                       1.0f, -1.0f, -1.0f, // top-left
                       1.0f, -1.0f,  1.0f, // bottom-left
                       1.0f, -1.0f,  1.0f, // bottom-left
                      -1.0f, -1.0f,  1.0f, // bottom-right
                      -1.0f, -1.0f, -1.0f, // top-right
                      // top face
                      -1.0f,  1.0f, -1.0f, // top-left
                       1.0f,  1.0f,  1.0f, // bottom-right
                       1.0f,  1.0f, -1.0f, // top-right
                       1.0f,  1.0f,  1.0f, // bottom-right
                      -1.0f,  1.0f, -1.0f, // top-left
                      -1.0f,  1.0f,  1.0f, // bottom-left       
}

{
  std::vector<std::string> faces
  {
      "../assets/skybox/right.jpg",
      "../assets/skybox/left.jpg",
      "../assets/skybox/top.jpg",
      "../assets/skybox/bottom.jpg",
      "../assets/skybox/front.jpg",
      "../assets/skybox/back.jpg"
  };

  // before loading faces, make this function to flip side faces
  stbi_set_flip_vertically_on_load(false);
  
  cubemapTexture = loadCubemap(faces);

  stbi_set_flip_vertically_on_load(true);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glBindVertexArray(0);
}

void Skybox::draw(){
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
}

GLuint Skybox::loadCubemap(std::vector<std::string> faces){
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID); 

  int width, height, nrChannels;
  for (unsigned int i = 0; i < faces.size(); i++){
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
        }

        else
        {
                std::cout << "Failed to load cubemap texture at path: " << faces[i] << std::endl;
                stbi_image_free(data);
        }
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return textureID;
}
