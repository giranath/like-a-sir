SET(ROOT ${PATH_SRC})
SET(EXECUTABLE_NAME "likeasir")

SET(SOURCES
    ${ROOT}/acteur.cpp
    ${ROOT}/baril.cpp
    ${ROOT}/BufferManager.cpp
    ${ROOT}/chargeurNiveau.cpp
    ${ROOT}/clef.cpp
    ${ROOT}/collectionnable.cpp
    ${ROOT}/GestionnaireNiveau.cpp
    ${ROOT}/interaction.cpp
    ${ROOT}/joueur.cpp
    ${ROOT}/levier.cpp
    ${ROOT}/main.cpp
    ${ROOT}/mechant.cpp
    ${ROOT}/menu.cpp
    ${ROOT}/niveau.cpp
    ${ROOT}/personnage.cpp
    ${ROOT}/porte.cpp
    ${ROOT}/TextureManager.cpp
    ${ROOT}/trap.cpp
    ${ROOT}/trapAuto.cpp
)

ADD_EXECUTABLE(${EXECUTABLE_NAME} ${SOURCES})
FIND_PACKAGE(SFML 2 COMPONENTS audio graphics window system REQUIRED)
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
