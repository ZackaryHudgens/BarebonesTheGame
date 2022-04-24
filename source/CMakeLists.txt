file(GLOB GAME_SOURCES main.cpp
                       gameObjects/camera/*.?pp
                       gameObjects/camera/states/*.?pp
                       gameObjects/characters/*.?pp
                       gameObjects/characters/enemies/*.?pp
                       gameObjects/characters/enemies/basicHuman/*.?pp
                       gameObjects/characters/skeletons/*.?pp
                       gameObjects/characters/skeletons/basicSkeleton/*.?pp
                       gameObjects/gui/*.?pp
                       gameObjects/gui/infoPanel/*.?pp
                       gameObjects/gui/menus/*.?pp
                       gameObjects/gui/menus/actions/*.?pp
                       gameObjects/gui/menus/actions/skillAction/*.?pp
                       gameObjects/gui/menus/skillMenu/*.?pp
                       gameObjects/gui/menus/spellMenu/*.?pp
                       gameObjects/skills/*.?pp
                       gameObjects/skills/clawSkill/*.?pp
                       gameObjects/skills/moveSkill/*.?pp
                       gameObjects/skills/spells/*.?pp
                       gameObjects/skills/spells/desecrateSpell/*.?pp
                       gameObjects/util/*.?pp
                       gameObjects/world/background/*.?pp
                       gameObjects/world/board/*.?pp
                       gameObjects/world/board/players/*.?pp
                       gameObjects/world/board/players/aiPlayer/*.?pp
                       gameObjects/world/board/players/humanPlayer/*.?pp
                       gameObjects/world/board/players/humanPlayer/inputStates/*.?pp
                       gameObjects/world/board/tiles/*.?pp
                       gameObjects/world/board/tiles/defaultTile/*.?pp
                       gameObjects/world/board/tiles/desecratedTile/*.?pp)

add_executable(barebones ${GAME_SOURCES})
target_link_libraries(barebones PUBLIC
                      ${URSINE_LIBRARIES})
target_include_directories(barebones PUBLIC
                           ${URSINE_INCLUDE_DIRS}
                           gameObjects/camera
                           gameObjects/camera/states
                           gameObjects/characters
                           gameObjects/characters/enemies
                           gameObjects/characters/enemies/basicHuman
                           gameObjects/characters/skeletons
                           gameObjects/characters/skeletons/basicSkeleton
                           gameObjects/gui
                           gameObjects/gui/infoPanel
                           gameObjects/gui/menus
                           gameObjects/gui/menus/actions
                           gameObjects/gui/menus/actions/skillAction
                           gameObjects/gui/menus/skillMenu
                           gameObjects/gui/menus/spellMenu
                           gameObjects/skills
                           gameObjects/skills/clawSkill
                           gameObjects/skills/moveSkill
                           gameObjects/skills/spells
                           gameObjects/skills/spells/desecrateSpell
                           gameObjects/util
                           gameObjects/world/background
                           gameObjects/world/board
                           gameObjects/world/board/players
                           gameObjects/world/board/players/aiPlayer
                           gameObjects/world/board/players/humanPlayer
                           gameObjects/world/board/players/humanPlayer/inputStates
                           gameObjects/world/board/tiles
                           gameObjects/world/board/tiles/defaultTile
                           gameObjects/world/board/tiles/desecratedTile)

install(TARGETS barebones DESTINATION ${INSTALL_DIR})
install(DIRECTORY resources DESTINATION ${INSTALL_DIR})
