cmake_minimum_required(VERSION 3.27)
project(Task4_3_3)

set(CMAKE_CXX_STANDARD 23)

add_executable(Task4_3_3 main.cpp)

include(DownloadProject.cmake)
download_project(PROJ           znanie-drevnix
        GIT_REPOSITORY https://github.com/KanatnikovMax/znanie-drevnix.git
        GIT_TAG        main
)
