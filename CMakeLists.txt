cmake_minimum_required(VERSION 2.6)
project(GeneticDecision)

set(LIBRARIES_SRC
    src/CoordR2.cpp
    src/Grafo.cpp
    src/ProduzGrafico.cpp
    src/pbPlots.cpp
    src/supportLib.cpp
)

set(LIBRARIES_HEADERS
    include/CoordR2.h
    include/Grafo.h
    include/ProduzGrafico.h
    include/pbPlots.hpp
    include/supportLib.hpp
)

set(SOURCES
    src/StatusRobo.cpp
    src/Pacote.cpp
    src/SequenciaPacotes.cpp
    src/SequenciaAcao.cpp
    src/PlanejamentoRobo.cpp
    src/main.cpp
)

set(HEADERS
    include/StatusRobo.h
    include/Pacote.h
    include/SequenciaPacotes.h
    include/SequenciaAcao.h
    include/PlanejamentoRobo.h
    include/Constantes.h   
)

include_directories("include/")
add_executable(Executable ${SOURCES} ${LIBRARIES_SRC} ${HEADERS} ${LIBRARIES_HEADERS})