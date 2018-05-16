add_subdirectory (lua)

SET (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Strings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Actor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Animation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KeyButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DeviceButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FontMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OptionsScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TileSetScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TileSetNewScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TileSetEditScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hero.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainMenuScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KeyboardScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteSet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ButtonGroup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TileSet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringProvider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/World.cpp
    PARENT_SCOPE
)
