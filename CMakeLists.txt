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

# foreach (file ${helloworld_SRC})
#     set(MYFILE_DIR)
#     if (file MATCHES ".*.hpp")
#         get_filename_component(MYFILE_DIR ${file} DIRECTORY)
#         include_directories(${MYFILE_DIR})
#     endif()
# endforeach()


include_directories("externalLib/glew-2.1.0/include")
include_directories("externalLib/glfw-3.3.8.bin.WIN64/include")
include_directories("externalLib/glm")
set(SFML_LIB_DIR "./SFML/lib")

IF (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    link_directories(${SFML_LIB_DIR})
ENDIF()
link_directories("externalLib/glew-2.1.0/lib/Release/x64/")
link_directories("externalLib/glew-2.1.0/bin/Release/x64/")
link_directories("externalLib/glfw-3.3.8.bin.WIN64/lib-mingw-w64/")
link_directories("externalLib/glm")

add_executable(game ${helloworld_SRC})

target_link_libraries(game myOpengl)

target_link_libraries(game 
    myOpengl 
    ${SFML_LIBRARIES} 
    glfw3
    glew32
    opengl32 
    glu32 
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

