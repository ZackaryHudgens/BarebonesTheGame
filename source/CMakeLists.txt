file(GLOB GAME_SOURCES main.cpp
                       gameObjects/world/*.?pp
                       gameObjects/world/board/*.?pp
                       gameObjects/world/board/players/*.?pp
                       gameObjects/world/board/players/aiPlayer/*.?pp
                       gameObjects/world/board/players/humanPlayer/*.?pp
                       gameObjects/world/board/players/humanPlayer/inputStates/*.?pp
                       gameObjects/world/board/tiles/*.?pp
                       gameObjects/world/board/tiles/defaultTile/*.?pp
                       gameObjects/camera/*.?pp
                       gameObjects/characters/*.?pp
                       gameObjects/characters/enemies/basicHuman/*.?pp
                       gameObjects/characters/skeletons/basicSkeleton/*.?pp
                       gameObjects/gui/*.?pp
                       gameObjects/gui/actions/*.?pp
                       gameObjects/gui/actions/skillAction/*.?pp
                       gameObjects/gui/menus/*.?pp
                       gameObjects/gui/menus/skillMenu/*.?pp
                       gameObjects/util/*.?pp)

add_executable(barebones ${GAME_SOURCES})
target_link_libraries(barebones PUBLIC
                      ${URSINE_LIBRARIES})
target_include_directories(barebones PUBLIC
                           ${URSINE_INCLUDE_DIRS}
                           gameObjects/world
                           gameObjects/world/board
                           gameObjects/world/board/players
                           gameObjects/world/board/players/aiPlayer
                           gameObjects/world/board/players/humanPlayer
                           gameObjects/world/board/players/humanPlayer/inputStates
                           gameObjects/world/board/tiles
                           gameObjects/world/board/tiles/defaultTile
                           gameObjects/camera
                           gameObjects/characters
                           gameObjects/characters/enemies/basicHuman
                           gameObjects/characters/skeletons/basicSkeleton
                           gameObjects/gui
                           gameObjects/gui/actions
                           gameObjects/gui/actions/skillAction
                           gameObjects/gui/menus
                           gameObjects/gui/menus/skillMenu
                           gameObjects/util)

install(TARGETS barebones DESTINATION ${INSTALL_DIR})
install(DIRECTORY resources DESTINATION ${INSTALL_DIR})
