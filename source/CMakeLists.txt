file(GLOB GAME_SOURCES main.cpp
                       gameObjects/board/*.?pp
                       gameObjects/board/tiles/*.?pp
                       gameObjects/board/tiles/defaultTile/*.?pp
                       gameObjects/characters/*.?pp
                       gameObjects/characters/skeletons/basicSkeleton/*.?pp)

add_executable(barebones ${GAME_SOURCES})
target_link_libraries(barebones PUBLIC
                      ${URSINE_LIBRARIES})
target_include_directories(barebones PUBLIC
                           ${URSINE_INCLUDE_DIRS}
                           gameObjects/board
                           gameObjects/board/tiles
                           gameObjects/board/tiles/defaultTile
                           gameObjects/characters
                           gameObjects/characters/skeletons/basicSkeleton)

install(TARGETS barebones DESTINATION ${INSTALL_DIR})
install(DIRECTORY resources DESTINATION ${INSTALL_DIR})
