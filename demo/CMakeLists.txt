cmake_minimum_required(VERSION 3.14)
project(SFMLDemo VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGL -lglew")

set(SOURCE_FILES main.cpp)
add_executable(SFMLDemo ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIRS})
endif()

target_link_libraries(SFMLDemo PUBLIC sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_custom_command(TARGET SFMLDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:SFMLDemo>/resources
    VERBATIM)