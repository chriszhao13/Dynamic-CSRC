cmake_minimum_required(VERSION 2.8)


project(DCSR)

set( project_sources
    dcsr.cpp
    main.cpp
)

set ( HEADERS
    dcsr.h
)

add_executable(${PROJECT_NAME} ${project_sources} ${HEADERS})
