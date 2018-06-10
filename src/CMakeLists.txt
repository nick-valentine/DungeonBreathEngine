add_subdirectory (lua)
add_subdirectory (ui)
add_subdirectory (render)

SET (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Strings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Actor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ActorManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DeviceButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OptionsScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TileSetScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TileSetNewScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TileSetEditScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LevelEditNewScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LevelEditScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LevelEditEditScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LevelEditTileScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LevelEditActorSelectScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Index.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainMenuScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KeyboardScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringProvider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/World.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lua.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Script.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container.cpp
    PARENT_SCOPE
)
