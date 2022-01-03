file(GLOB GAME_SOURCES main.cpp
                       gameObjects/board/*.?pp
                       gameObjects/board/components/*.?pp
                       gameObjects/board/tiles/*.?pp
                       gameObjects/skeletons/*.?pp
                       gameObjects/skeletons/components/*.?pp)

add_executable(barebones ${GAME_SOURCES})
target_link_libraries(barebones PUBLIC
                      ${URSINE_LIBRARIES})
target_include_directories(barebones PUBLIC
                           ${URSINE_INCLUDE_DIRS}
                           gameObjects/board
                           gameObjects/board/components
                           gameObjects/board/tiles
                           gameObjects/skeletons
                           gameObjects/skeletons/components)

install(TARGETS barebones DESTINATION ${INSTALL_DIR})
install(DIRECTORY resources DESTINATION ${INSTALL_DIR})
