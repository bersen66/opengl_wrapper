cmake_minimum_required(VERSION 3.16)

project(
        APIGL
        VERSION 0.0.1
        DESCRIPTION "RAII wrappers over OpenGL objects"
)

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


set(
        SOURCES
        shaders/shader_program.cpp

        buffers/vbo.cpp
        buffers/attribute_layout.cpp
        buffers/vao.cpp
        buffers/ibo.cpp
)

set(
        HEADERS
        shaders/shader.h
        shaders/shader_program.h

        buffers/vbo.h
        buffers/vao.h
        buffers/attribute_layout.h
        buffers/ibo.h

        apigl.h
        bytes.h
)


add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ..
        buffers
        shaders
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    message("GLEW found")
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    message("Found OpenGL")
    target_link_libraries(${PROJECT_NAME} OpenGL::GL)
endif (OpenGL_FOUND)

find_package(glm REQUIRED)
if (GLM_FOUND)
    message("GLM FOUND")
    include_directories(${GLM_INCLUDE_DIR})
endif(GLM_FOUND)
