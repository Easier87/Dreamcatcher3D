#include <core/framebuffer.hpp>

using namespace Dreamcatcher;

Framebuffer::Framebuffer() : quad{ 
                                            -1.0f, -1.0f,   0.0f, 0.0f,
                                            -1.0f,  1.0f,   0.0f, 1.0f,
                                             1.0f,  1.0f,   1.0f, 1.0f,
                                             1.0f, -1.0f,   1.0f, 0.0f
}


{
  glGenFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);



  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
  // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);


  
  glGenRenderbuffers(1, &RBO);
  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIN_WIDTH, WIN_HEIGHT);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std:: endl;
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  
   
  // GLuint indices[] ={
  //   0, 1, 2,
  //   2, 3, 0
  // };
  //
  // glGenBuffers(1, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  //
  // glGenVertexArrays(1, &quadVAO);
  // glGenBuffers(1, &quadVBO);
  // glBindVertexArray(quadVAO);
  // glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, GL_STATIC_DRAW);
  // glEnableVertexAttribArray(0);
  // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  // glBindVertexArray(0);
}

// void Framebuffer::DrawFramebuffer(){
//   glBindVertexArray(quadVAO);
//   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//   glBindVertexArray(0);
// }

// GLuint Framebuffer::GetBuffer(){
//   return FBO;
// }
