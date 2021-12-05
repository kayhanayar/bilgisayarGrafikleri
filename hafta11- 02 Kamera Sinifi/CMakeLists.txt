cmake_minimum_required(VERSION 3.2)

project(Deneme)



set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(DEPENDENCIES_DIR ${PROJECT_DIR}/../../Dependencies)

set(IMGUI_DIR ${DEPENDENCIES_DIR}/imgui)



set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
file(GLOB IMGUI_SOURCEFILES ${IMGUI_DIR}/*.cpp)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

set(glfw3_DIR ${DEPENDENCIES_DIR}/GLFW/lib/cmake/glfw3)

find_package(glfw3 3.2 REQUIRED)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

set(PROJECT_SOURCES ${SOURCE_FILES}
                    ${PROJECT_SOURCE_DIR}/glad.c
                    ${IMGUI_SOURCEFILES}
                    )



include_directories(${PROJECT_INCLUDE_DIR} ${DEPENDENCIES_DIR} )

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})


target_link_libraries(${PROJECT_NAME} glfw)