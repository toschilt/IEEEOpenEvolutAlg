cmake_minimum_required(VERSION 2.6)
project(GeneticDecision)

set(SOURCES
    src/CoordR2.cpp
    src/Grafo.cpp
    src/Package.cpp
    src/main.cpp
)

set(HEADERS
    include/CoordR2.h
    include/Grafo.h
    include/Package.h
)

include_directories("include/")

add_executable(Executable ${SOURCES} ${HEADERS})