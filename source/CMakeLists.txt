file(GLOB GAME_SOURCES main.cpp
                       components/board/*.?pp
                       components/board/tiles/*.?pp
                       components/skeletons/*.?pp)

add_executable(barebones ${GAME_SOURCES})
target_link_libraries(barebones PUBLIC
                      ${URSINE_LIBRARIES})
target_include_directories(barebones PUBLIC
                           ${URSINE_INCLUDE_DIRS}
                           components/board
                           components/board/tiles
                           components/skeletons)

install(TARGETS barebones DESTINATION ${INSTALL_DIR})
install(DIRECTORY resources DESTINATION ${INSTALL_DIR})
