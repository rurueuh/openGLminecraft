cmake_minimum_required(VERSION 3.9)

project(lib VERSION 0.1.0)

file(GLOB_RECURSE libsrc
    "lib/*.cpp"
    "lib/*.hpp"
)

foreach (file ${libsrc})
    set(MYFILE_DIR)
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
endforeach()

add_library(myOpengl ${libsrc})


project(game VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE helloworld_SRC
    "src/*.cpp"
    "src/*.hpp"
)

foreach (file ${helloworld_SRC})
    set(MYFILE_DIR)
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
endforeach()


include_directories("./SFML/include")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_LIB_DIR "./SFML/lib")

IF (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    link_directories(${SFML_LIB_DIR})
ENDIF()

add_executable(game ${helloworld_SRC})

target_link_libraries(game myOpengl)

if (WIN32)
    target_link_libraries(game sfml-graphics sfml-window sfml-system sfml-network sfml-audio opengl32 winmm gdi32)
else ()
    target_link_libraries(game glfw GL GLEW GLU glut)
endif ()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

