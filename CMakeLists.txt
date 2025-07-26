cmake_minimum_required(VERSION 3.19)
project(pawn_ts_ms)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(open.mp-sdk)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/pawn/source
    ${CMAKE_CURRENT_SOURCE_DIR}/pawn/source/linux
)

add_definitions(
    -DHAVE_STDINT_H=1
    -DPAWN_CELL_SIZE=32
)

add_library(${PROJECT_NAME} SHARED src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE OMP-SDK)
set_property(TARGET ${PROJECT_NAME} PROPERTY PREFIX "")
