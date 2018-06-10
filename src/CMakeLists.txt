add_subdirectory (lua)
add_subdirectory (ui)
add_subdirectory (render)
add_subdirectory (scene)
add_subdirectory (core)

SET (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Actor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ActorManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/World.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldManager.cpp
    PARENT_SCOPE
)
