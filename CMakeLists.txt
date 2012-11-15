cmake_minimum_required(VERSION 2.8)

project(dungen)

file(
    GLOB_RECURSE
    SOURCES
    ./src/*.c
    ./src/*.h
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

IF(UNIX)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} m)
ENDIF(UNIX)
