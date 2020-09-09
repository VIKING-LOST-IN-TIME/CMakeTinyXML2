cmake_minimum_required(VERSION 3.18.0)

project(CMakeTinyXML2 VERSION 0.1)

configure_file(CMakeTinyXML2Config.h.in CMakeTinyXML2Config.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#           CHECK ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/tinyxml2/CMakeLists.txt")
    message(FATAL_ERROR "The tinyxml2 submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()


add_subdirectory(external/tinyxml2)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/tinyxml2
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE external/tinyxml2
)

target_link_libraries(${PROJECT_NAME} tinyxml2)