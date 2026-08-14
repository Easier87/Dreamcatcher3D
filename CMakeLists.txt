cmake_minimum_required(VERSION 4.1.2 FATAL_ERROR)
project(Dreamcatcher3D VERSION 0.0.1)

project(a.out)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_MINIZIP ON CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/stb_image.cpp
  src/skybox.cpp

  src/core/camera.cpp
  src/core/window.cpp
  src/core/texture_loader.cpp
  src/core/framebuffer.cpp

  src/models/mesh.cpp
  src/models/model.cpp
  src/models/triangle.cpp
  src/models/plane.cpp
  src/models/cube.cpp
)

add_subdirectory(thirdparty/glfw-3.4)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/assimp)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} assimp)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/thirdparty/glfw-3.4/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/thirdparty/glad/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/thirdparty/glm")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/thirdparty/assimp")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include/")

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

if(APPLE)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wno-deprecated-declarations)
endif()
