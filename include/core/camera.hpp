#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Dreamcatcher{

enum Camera_Movement{
  FORWARD,
  BACKWARD,
  RIGHT,
  LEFT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENSITIVITY = 0.1f;
const float SPEED = 4.5f;
const float ZOOM = 45.0F;

class Camera{
public:
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  float Yaw;
  float Pitch;

  float Zoom;
  float Sensitivity;
  float MovementSpeed;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
         Sensitivity(SENSITIVITY), Zoom(ZOOM)
  {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
  }

  glm::mat4 GetViewMatrix() noexcept;
  void ProcessKeyboard(Camera_Movement direction, float deltaTime) noexcept;
  void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
  void ProcessMouseScroll(float yoffset);

private:
  void updateCameraVectors() noexcept;
};


}
