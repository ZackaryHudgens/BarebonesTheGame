file(GLOB GAME_SOURCES main.cpp
                       gameObjects/board/*.?pp
                       gameObjects/board/inputStates/*.?pp
                       gameObjects/board/tiles/*.?pp
                       gameObjects/board/tiles/defaultTile/*.?pp
                       gameObjects/camera/*.?pp
                       gameObjects/characters/*.?pp
                       gameObjects/characters/enemies/basicHuman/*.?pp
                       gameObjects/characters/skeletons/basicSkeleton/*.?pp
                       gameObjects/gui/*.?pp)

add_executable(barebones ${GAME_SOURCES})
target_link_libraries(barebones PUBLIC
                      ${URSINE_LIBRARIES})
target_include_directories(barebones PUBLIC
                           ${URSINE_INCLUDE_DIRS}
                           gameObjects/board
                           gameObjects/board/inputStates
                           gameObjects/board/tiles
                           gameObjects/board/tiles/defaultTile
                           gameObjects/camera
                           gameObjects/characters
                           gameObjects/characters/enemies/basicHuman
                           gameObjects/characters/skeletons/basicSkeleton
                           gameObjects/gui)

install(TARGETS barebones DESTINATION ${INSTALL_DIR})
install(DIRECTORY resources DESTINATION ${INSTALL_DIR})
