cmake_minimum_required(VERSION 3.15)

project(capstone-sdl VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

find_package(BULLET REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/pid)

add_library(app)
target_sources(app
        PUBLIC
        src/app.hpp

        src/managers/physicsManager.hpp
        src/managers/displayManager.hpp
        src/managers/sceneManager.hpp
        src/managers/modelManager.hpp
        src/managers/shaderManager.hpp

        src/logic/gameLogic.hpp
        src/logic/Enemy.hpp
        src/logic/collisionEvent.hpp

        src/gfx/modelType.hpp
        src/gfx/shaderType.hpp
        src/gfx/Shader.hpp

        src/scene/Camera.hpp
        src/scene/sceneObject.hpp

        PRIVATE
        src/app.cpp

        src/managers/physicsManager.cpp
        src/managers/displayManager.cpp
        src/managers/sceneManager.cpp
        src/managers/modelManager.cpp
        src/managers/shaderManager.cpp

        src/logic/gameLogic.cpp
        src/logic/Enemy.cpp
        src/logic/collisionEvent.cpp

        src/gfx/modelType.cpp
        src/gfx/Shader.cpp

        src/scene/Camera.cpp
        src/scene/sceneObject.cpp
        )

target_include_directories(app
        PUBLIC
        src
        PRIVATE
        ${BULLET_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIR}
        )
target_link_libraries(app PRIVATE
        ${BULLET_LIBRARIES}
        ${SDL2_LIBRARY}
        OpenGL::GL
        OpenGL::GLU
        GLEW::GLEW
        glm
        pid
        )
target_compile_features(app PUBLIC cxx_std_17)

add_executable(main)
target_sources(main PUBLIC src/main.cpp)
target_link_libraries(main PUBLIC app)

#target_link_options(main PUBLIC "-mconsole")
