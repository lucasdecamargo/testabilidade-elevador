cmake_minimum_required(VERSION 3.0.0)
project(elevador VERSION 0.1.0)

include(CTest)

add_executable(elevador main.cpp
    src/componentes.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(${CMAKE_CURRENT_LIST_DIR}/lib)


