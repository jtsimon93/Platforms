cmake_minimum_required(VERSION 3.15)
project(Platforms)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Handle sub directories
add_subdirectory(external/raylib)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Include your headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


# Copy assets to the output directory
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rm -rf $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    )
endif()


if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    
    target_link_options(${PROJECT_NAME} PRIVATE
        "-sUSE_GLFW=3"
        "-sASYNCIFY"
        "-sALLOW_MEMORY_GROWTH"
            "--preload-file=${CMAKE_SOURCE_DIR}/assets@/assets"
    )
endif()

