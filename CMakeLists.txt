cmake_minimum_required(VERSION 3.11)
set(PROJECT_NAME project_base)
project(${PROJECT_NAME})

function(watch)
    set_property(
            DIRECTORY
            APPEND
            PROPERTY CMAKE_CONFIGURE_DEPENDS ${ARGV}
    )
endfunction()

set(CMAKE_POLICY_DEFAULT_CMP0012 NEW)
set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -O3")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

file(GLOB SOURCES "src/*.cpp" "src/*.c" src/main.cpp)
file(GLOB HEADERS "include/*.h" "include/*.hpp")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(ASSIMP REQUIRED)

add_subdirectory(libs/glad)
add_subdirectory(libs/imgui)

add_definitions(${OPENGL_DEFINITIONS})

add_library(STB_IMAGE libs/stb_image.cpp)
set_source_files_properties(libs/stb_image.cpp include/stb_image.h
        PROPERTIES
        COMPILE_FLAGS
        "-Wno-shift-negative-value -Wno-implicit-fallthrough")

set(LIBS glfw glad OpenGL::GL X11 Xrandr Xinerama Xi Xxf86vm Xcursor dl pthread freetype ${ASSIMP_LIBRARIES} STB_IMAGE imgui)


configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)


include_directories(include/)
add_executable(${PROJECT_NAME}
        ${SOURCES} resources/buildings/Building.cpp resources/buildings/Building.h resources/buildings/BuildingBase.cpp resources/buildings/BuildingBase.h resources/buildings/BuildingRoof.cpp resources/buildings/BuildingRoof.h resources/terrains/Cobblestone.cpp resources/terrains/Cobblestone.h resources/terrains/Grass.cpp resources/terrains/Grass.h resources/terrains/Road.cpp resources/terrains/Road.h resources/buildings/SmallBuildingBase.cpp resources/buildings/SmallBuildingBase.h resources/buildings/MediumBuildingBase.cpp resources/buildings/MediumBuildingBase.h resources/buildings/LargeBuildingBase.cpp resources/buildings/LargeBuildingBase.h resources/buildings/Wall.cpp resources/buildings/Wall.h resources/buildings/SmallBuildingRoof.cpp resources/buildings/SmallBuildingRoof.h resources/buildings/MediumBuildingRoof.cpp resources/buildings/MediumBuildingRoof.h resources/buildings/LargeBuildingRoof.cpp resources/buildings/LargeBuildingRoof.h include/drawing.h resources/buildings/Door.cpp resources/buildings/Door.h resources/lights/pointLight/PointLight.cpp resources/lights/pointLight/PointLight.h resources/lights/pointLight/TestCube.cpp resources/lights/pointLight/TestCube.h include/commonOperations.h)

target_link_libraries(${PROJECT_NAME} ${LIBS})

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
file(GLOB SHADERS "shaders/*.vs"
        "shaders/*.fs")
foreach(SHADER ${SHADERS})
    # file(COPY ${SHADER} DESTINATION ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/shaders)
    watch(${SHADER})
endforeach()

