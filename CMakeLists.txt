cmake_minimum_required(VERSION 3.18.0)

project(CMakeTinyXML2 VERSION 0.1.0)

add_subdirectory(external/tinyxml2)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/tinyxml2
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE external/tinyxml2
)

target_link_libraries(${PROJECT_NAME} tinyxml2)