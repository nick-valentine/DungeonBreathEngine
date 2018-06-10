add_subdirectory (lua)
add_subdirectory (ui)
add_subdirectory (render)
add_subdirectory (scene)

SET (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Strings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Actor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ActorManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DeviceButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Index.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringProvider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/World.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lua.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Script.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Container.cpp
    PARENT_SCOPE
)
